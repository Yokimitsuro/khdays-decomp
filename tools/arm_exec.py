#!/usr/bin/env python3
"""A small ARMv5TE (ARM state) interpreter for replaying original payload code.

Hand-written middleware routines that live in DATA (the MobiClip decoder's
in-place kernels in ov024) cannot be compared with a C build, so their semantic
reimplementations are checked by running the ROM's own instructions on the same
inputs. This interpreter covers the ARM-state integer instruction set those
routines use: data processing with every shifter form, MUL/MLA and the long and
DSP multiplies, CLZ, single/halfword/doubleword transfers with every addressing
mode, LDM/STM, B/BL/BX/BLX. It refuses anything else (coprocessor, SWI, mode
changes, THUMB) instead of guessing.

    cpu = Cpu(Memory())
    cpu.mem.map(0x02092e60, code_bytes)
    cpu.call(0x02092e60, [r0, r1, r2, r3])
"""

from __future__ import annotations

MASK = 0xFFFFFFFF
RETURN_SENTINEL = 0xFFFFFFF0


class ArmFault(Exception):
    pass


class Memory:
    """Flat little-endian memory made of mapped regions."""

    def __init__(self):
        self.regions = []                       # [start, end, bytearray]

    def map(self, start: int, data=None, size: int | None = None) -> bytearray:
        buf = bytearray(data if data is not None else bytes(size or 0))
        for lo, hi, _ in self.regions:
            if start < hi and lo < start + len(buf):
                raise ArmFault("region 0x%08x overlaps an existing mapping" % start)
        self.regions.append([start, start + len(buf), buf])
        return buf

    def _find(self, address: int, size: int):
        for lo, hi, buf in self.regions:
            if lo <= address and address + size <= hi:
                return buf, address - lo
        raise ArmFault("unmapped access of %d bytes at 0x%08x" % (size, address))

    def read(self, address: int, size: int) -> int:
        buf, off = self._find(address, size)
        return int.from_bytes(buf[off:off + size], "little")

    def write(self, address: int, size: int, value: int) -> None:
        buf, off = self._find(address, size)
        buf[off:off + size] = (value & ((1 << (8 * size)) - 1)).to_bytes(size, "little")

    def bytes(self, address: int, size: int) -> bytes:
        buf, off = self._find(address, size)
        return bytes(buf[off:off + size])


def _sx(value: int, bits: int) -> int:
    value &= (1 << bits) - 1
    return value - (1 << bits) if value >> (bits - 1) else value


def _s32(value: int) -> int:
    return _sx(value, 32)


class Cpu:
    def __init__(self, mem: Memory):
        self.mem = mem
        self.r = [0] * 16
        self.n = self.z = self.c = self.v = 0
        self.steps = 0

    # -- helpers -----------------------------------------------------------------
    def _reg(self, index: int, pc_offset: int = 8) -> int:
        if index == 15:
            return (self.pc + pc_offset) & MASK
        return self.r[index]

    def _cond(self, cond: int) -> bool:
        n, z, c, v = self.n, self.z, self.c, self.v
        return [
            z, not z, c, not c, n, not n, v, not v,
            c and not z, (not c) or z, n == v, n != v,
            (not z) and n == v, z or n != v, True,
        ][cond] if cond < 15 else False

    def _shift(self, value: int, kind: int, amount: int, by_register: bool):
        """Barrel shifter: returns (result, carry_out)."""
        c = self.c
        if kind == 0:                                   # LSL
            if amount == 0:
                return value, c
            if amount < 32:
                return (value << amount) & MASK, (value >> (32 - amount)) & 1
            if amount == 32:
                return 0, value & 1
            return 0, 0
        if kind == 1:                                   # LSR
            if amount == 0:
                if by_register:
                    return value, c
                amount = 32
            if amount < 32:
                return value >> amount, (value >> (amount - 1)) & 1
            if amount == 32:
                return 0, value >> 31
            return 0, 0
        if kind == 2:                                   # ASR
            if amount == 0:
                if by_register:
                    return value, c
                amount = 32
            if amount < 32:
                return (_s32(value) >> amount) & MASK, (value >> (amount - 1)) & 1
            bit = value >> 31
            return (MASK if bit else 0), bit
        # ROR / RRX
        if amount == 0:
            if by_register:
                return value, c
            return ((c << 31) | (value >> 1)) & MASK, value & 1
        amount &= 31
        if amount == 0:
            return value, value >> 31
        result = ((value >> amount) | (value << (32 - amount))) & MASK
        return result, result >> 31

    def _operand2(self, ins: int):
        if ins & (1 << 25):
            imm = ins & 0xFF
            rot = ((ins >> 8) & 0xF) * 2
            value = ((imm >> rot) | (imm << (32 - rot))) & MASK if rot else imm
            return value, (value >> 31 if rot else self.c)
        rm = ins & 0xF
        kind = (ins >> 5) & 3
        if ins & 0x10:
            amount = self._reg((ins >> 8) & 0xF) & 0xFF
            return self._shift(self._reg(rm, 12), kind, amount, True)
        return self._shift(self._reg(rm), kind, (ins >> 7) & 0x1F, False)

    def _set_nz(self, value: int) -> None:
        self.n = value >> 31
        self.z = int(value == 0)

    def _write_reg(self, index: int, value: int) -> None:
        value &= MASK
        if index == 15:
            if value & 1:
                raise ArmFault("switch to THUMB state at 0x%08x" % self.pc)
            self.next_pc = value & ~3
        else:
            self.r[index] = value

    # -- instruction classes -----------------------------------------------------
    def _data_processing(self, ins: int) -> None:
        opcode = (ins >> 21) & 0xF
        s = (ins >> 20) & 1
        rn = (ins >> 16) & 0xF
        rd = (ins >> 12) & 0xF
        op2, shifter_carry = self._operand2(ins)
        a = self._reg(rn, 12 if (not ins & (1 << 25) and ins & 0x10) else 8)
        c_in = self.c
        logical = opcode in (0, 1, 8, 9, 12, 13, 14, 15)
        if opcode in (0, 8):
            result = a & op2
        elif opcode in (1, 9):
            result = a ^ op2
        elif opcode in (2, 10):
            result, carry, overflow = self._add(a, (~op2) & MASK, 1)
        elif opcode == 3:
            result, carry, overflow = self._add(op2, (~a) & MASK, 1)
        elif opcode in (4, 11):
            result, carry, overflow = self._add(a, op2, 0)
        elif opcode == 5:
            result, carry, overflow = self._add(a, op2, c_in)
        elif opcode == 6:
            result, carry, overflow = self._add(a, (~op2) & MASK, c_in)
        elif opcode == 7:
            result, carry, overflow = self._add(op2, (~a) & MASK, c_in)
        elif opcode == 12:
            result = a | op2
        elif opcode == 13:
            result = op2
        elif opcode == 14:
            result = a & ~op2 & MASK
        else:
            result = (~op2) & MASK
        if 8 <= opcode <= 11:
            if not s:
                raise ArmFault("unsupported status-register instruction 0x%08x" % ins)
        else:
            if s and rd == 15:
                raise ArmFault("mode-changing data processing at 0x%08x" % self.pc)
            self._write_reg(rd, result)
        if s:
            self._set_nz(result)
            if logical:
                self.c = shifter_carry
            else:
                self.c, self.v = carry, overflow

    @staticmethod
    def _add(a: int, b: int, carry_in: int):
        total = a + b + carry_in
        result = total & MASK
        carry = int(total > MASK)
        overflow = int(((a ^ result) & (b ^ result)) >> 31 & 1)
        return result, carry, overflow

    def _multiply(self, ins: int) -> None:
        rd = (ins >> 16) & 0xF
        rn = (ins >> 12) & 0xF
        rs = (ins >> 8) & 0xF
        rm = ins & 0xF
        result = (self.r[rm] * self.r[rs]) & MASK
        if ins & (1 << 21):
            result = (result + self.r[rn]) & MASK
        self._write_reg(rd, result)
        if ins & (1 << 20):
            self._set_nz(result)

    def _multiply_long(self, ins: int) -> None:
        hi = (ins >> 16) & 0xF
        lo = (ins >> 12) & 0xF
        rs = (ins >> 8) & 0xF
        rm = ins & 0xF
        signed = ins & (1 << 22)
        a = _s32(self.r[rm]) if signed else self.r[rm]
        b = _s32(self.r[rs]) if signed else self.r[rs]
        product = a * b
        if ins & (1 << 21):
            product += (self.r[hi] << 32) | self.r[lo]
        product &= (1 << 64) - 1
        self.r[lo] = product & MASK
        self.r[hi] = product >> 32
        if ins & (1 << 20):
            self.n = product >> 63
            self.z = int(product == 0)

    def _dsp_multiply(self, ins: int) -> None:
        op = (ins >> 21) & 3
        rd = (ins >> 16) & 0xF
        rn = (ins >> 12) & 0xF
        rs = (ins >> 8) & 0xF
        rm = ins & 0xF
        x = (ins >> 5) & 1
        y = (ins >> 6) & 1
        m = _sx(self.r[rm] >> (16 * x), 16)
        s = _sx(self.r[rs] >> (16 * y), 16)
        if op == 0:                                     # SMLAxy
            product = m * s
            total = product + _s32(self.r[rn])
            self._write_reg(rd, total)
        elif op == 1:                                   # SMLAWy / SMULWy
            product = (_s32(self.r[rm]) * s) >> 16
            if x:
                self._write_reg(rd, product)
            else:
                self._write_reg(rd, product + _s32(self.r[rn]))
        elif op == 2:                                   # SMLALxy
            acc = ((self.r[rd] << 32) | self.r[rn]) + m * s
            acc &= (1 << 64) - 1
            self.r[rn] = acc & MASK
            self.r[rd] = acc >> 32
        else:                                           # SMULxy
            self._write_reg(rd, m * s)

    def _address(self, base: int, offset: int, pre: bool, up: bool):
        target = (base + offset if up else base - offset) & MASK
        return (target if pre else base), target

    def _single_transfer(self, ins: int) -> None:
        pre = (ins >> 24) & 1
        up = (ins >> 23) & 1
        byte = (ins >> 22) & 1
        wb = (ins >> 21) & 1
        load = (ins >> 20) & 1
        rn = (ins >> 16) & 0xF
        rd = (ins >> 12) & 0xF
        if ins & (1 << 25):
            if ins & 0x10:
                raise ArmFault("register-shifted transfer offset at 0x%08x" % self.pc)
            offset, _ = self._shift(self._reg(ins & 0xF), (ins >> 5) & 3, (ins >> 7) & 0x1F, False)
        else:
            offset = ins & 0xFFF
        base = self._reg(rn)
        address, updated = self._address(base, offset, pre, up)
        if load:
            if byte:
                value = self.mem.read(address, 1)
            else:
                word = self.mem.read(address & ~3, 4)
                rot = (address & 3) * 8
                value = ((word >> rot) | (word << (32 - rot))) & MASK if rot else word
        else:
            value = self._reg(rd, 12)
            if byte:
                self.mem.write(address, 1, value)
            else:
                self.mem.write(address & ~3, 4, value)
        if (not pre or wb) and not (load and rn == rd):
            self._write_reg(rn, updated)
        if load:
            self._write_reg(rd, value)

    def _halfword_transfer(self, ins: int) -> None:
        pre = (ins >> 24) & 1
        up = (ins >> 23) & 1
        wb = (ins >> 21) & 1
        load = (ins >> 20) & 1
        rn = (ins >> 16) & 0xF
        rd = (ins >> 12) & 0xF
        sh = (ins >> 5) & 3
        if ins & (1 << 22):
            offset = ((ins >> 4) & 0xF0) | (ins & 0xF)
        else:
            offset = self._reg(ins & 0xF)
        base = self._reg(rn)
        address, updated = self._address(base, offset, pre, up)
        writes_base = (not pre or wb)
        if load:
            if sh == 1:
                value = self.mem.read(address, 2)
            elif sh == 2:
                value = _sx(self.mem.read(address, 1), 8) & MASK
            else:
                value = _sx(self.mem.read(address, 2), 16) & MASK
            if writes_base and rn != rd:
                self._write_reg(rn, updated)
            self._write_reg(rd, value)
            return
        if sh == 1:                                     # STRH
            self.mem.write(address, 2, self._reg(rd, 12))
        elif sh == 2:                                   # LDRD
            if rd & 1 or rd == 14:
                raise ArmFault("LDRD with an odd register at 0x%08x" % self.pc)
            lo = self.mem.read(address, 4)
            hi = self.mem.read(address + 4, 4)
            if writes_base:
                self._write_reg(rn, updated)
            self._write_reg(rd, lo)
            self._write_reg(rd + 1, hi)
            return
        else:                                           # STRD
            if rd & 1 or rd == 14:
                raise ArmFault("STRD with an odd register at 0x%08x" % self.pc)
            self.mem.write(address, 4, self._reg(rd, 12))
            self.mem.write(address + 4, 4, self._reg(rd + 1, 12))
        if writes_base:
            self._write_reg(rn, updated)

    def _block_transfer(self, ins: int) -> None:
        pre = (ins >> 24) & 1
        up = (ins >> 23) & 1
        if ins & (1 << 22):
            raise ArmFault("user-bank LDM/STM at 0x%08x" % self.pc)
        wb = (ins >> 21) & 1
        load = (ins >> 20) & 1
        rn = (ins >> 16) & 0xF
        regs = [i for i in range(16) if ins & (1 << i)]
        if not regs:
            raise ArmFault("empty register list at 0x%08x" % self.pc)
        base = self.r[rn]
        count = len(regs)
        if up:
            start = base + 4 if pre else base
            final = base + 4 * count
        else:
            start = base - 4 * count if pre else base - 4 * count + 4
            final = base - 4 * count
        start &= MASK
        address = start
        values = {}
        for reg in regs:
            if load:
                values[reg] = self.mem.read(address, 4)
            else:
                self.mem.write(address, 4, self._reg(reg, 12))
            address += 4
        if wb and not (load and rn in regs):
            self.r[rn] = final & MASK
        for reg in regs:
            if reg in values:
                self._write_reg(reg, values[reg])

    # -- execution ---------------------------------------------------------------
    def step(self) -> None:
        self.pc = self.r[15]
        ins = self.mem.read(self.pc, 4)
        self.next_pc = (self.pc + 4) & MASK
        cond = ins >> 28
        self.steps += 1
        if cond == 0xF:
            if (ins & 0x0E000000) == 0x0A000000:        # BLX immediate
                raise ArmFault("BLX to THUMB at 0x%08x" % self.pc)
            raise ArmFault("unconditional-space instruction 0x%08x at 0x%08x" % (ins, self.pc))
        if self._cond(cond):
            self._execute(ins)
        self.r[15] = self.next_pc

    def _execute(self, ins: int) -> None:
        if (ins & 0x0FFFFFF0) == 0x012FFF10:            # BX
            target = self.r[ins & 0xF]
            if target & 1:
                raise ArmFault("BX to THUMB at 0x%08x" % self.pc)
            self.next_pc = target & ~3
        elif (ins & 0x0FFFFFF0) == 0x012FFF30:          # BLX register
            target = self.r[ins & 0xF]
            if target & 1:
                raise ArmFault("BLX to THUMB at 0x%08x" % self.pc)
            self.r[14] = (self.pc + 4) & MASK
            self.next_pc = target & ~3
        elif (ins & 0x0FFF0FF0) == 0x016F0F10:          # CLZ
            value = self.r[ins & 0xF]
            self._write_reg((ins >> 12) & 0xF, 32 - value.bit_length())
        elif (ins & 0x0FC000F0) == 0x00000090:
            self._multiply(ins)
        elif (ins & 0x0F8000F0) == 0x00800090:
            self._multiply_long(ins)
        elif (ins & 0x0F900090) == 0x01000080:
            self._dsp_multiply(ins)
        elif (ins & 0x0E000090) == 0x00000090 and (ins & 0x60):
            self._halfword_transfer(ins)
        elif (ins & 0x0F900FF0) == 0x01000050 or (ins & 0x0FB00FF0) == 0x01000090:
            raise ArmFault("saturating/swap instruction 0x%08x at 0x%08x" % (ins, self.pc))
        elif (ins & 0x0C000000) == 0x00000000:
            if (ins & 0x01900000) == 0x01000000:
                raise ArmFault("status-register access 0x%08x at 0x%08x" % (ins, self.pc))
            self._data_processing(ins)
        elif (ins & 0x0C000000) == 0x04000000:
            if (ins & 0x02000010) == 0x02000010:
                raise ArmFault("undefined instruction 0x%08x at 0x%08x" % (ins, self.pc))
            self._single_transfer(ins)
        elif (ins & 0x0E000000) == 0x08000000:
            self._block_transfer(ins)
        elif (ins & 0x0E000000) == 0x0A000000:
            if ins & (1 << 24):
                self.r[14] = (self.pc + 4) & MASK
            self.next_pc = (self.pc + 8 + (_sx(ins & 0xFFFFFF, 24) << 2)) & MASK
        else:
            raise ArmFault("unsupported instruction 0x%08x at 0x%08x" % (ins, self.pc))

    def call(self, entry: int, args=(), sp: int | None = None, limit: int = 50_000_000) -> int:
        """Run a function until it returns to the sentinel; returns r0."""
        for i, value in enumerate(args):
            self.r[i] = value & MASK
        if sp is not None:
            self.r[13] = sp
        self.r[14] = RETURN_SENTINEL
        self.r[15] = entry
        start = self.steps
        while self.r[15] != RETURN_SENTINEL:
            if self.steps - start > limit:
                raise ArmFault("step limit reached at 0x%08x" % self.r[15])
            self.step()
        return self.r[0]
