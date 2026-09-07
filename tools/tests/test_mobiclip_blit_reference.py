"""Pin the MobiClip blitter's reference implementation against the ROM itself.

The routine at ov024:02086004 is hand-written ARM and is checked in as a
mnemonic stub, so the only thing the PC port can actually build from is the
reference implementation in that stub's header. That reference was derived by
reading the disassembly, which is exactly the situation where a red/green swap
or a dither on the wrong diagonal survives review: the code stays
self-consistent and simply produces the wrong picture.

So run the ROM's own instructions. The function uses thirteen mnemonics over
flat memory and no relocations, which is small enough to interpret directly.
Both implementations read the same synthetic buffers and their destination
words are compared byte for byte.

The lookup block is filled with random values rather than a monotone ramp so
that two colour windows cannot compare equal by accident, and the test asserts
its own sensitivity: four mutations of the reference, one per claim the header
makes, must each be detected.
"""
import json
import random
import re
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TOOLS = ROOT / "tools"
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

FUNCTION = "func_ov024_02086004"
INDEX = ROOT / "build" / "func_index.json"

try:
    from capstone import CS_ARCH_ARM, CS_MODE_ARM, Cs
    HAVE_CAPSTONE = True
except ImportError:  # pragma: no cover - environment without capstone
    HAVE_CAPSTONE = False

# Layout of the synthetic address space. Luma rows are 256 bytes and a chroma
# row is 256 bytes holding 128 of Co followed by 128 of Cg.
LUMA, CHROMA, TABLE, DEST, VIEW, STACK = (
    0x10000, 0x30000, 0x50000, 0x70000, 0x90000, 0x1F0000)
WIDTH, HEIGHT, STRIDE = 16, 4, 512

NAMED = {"sb": 9, "sl": 10, "fp": 11, "ip": 12, "sp": 13, "lr": 14, "pc": 15}
IMMEDIATE = re.compile(r"^#(-?)(0x[0-9a-f]+|\d+)$")
POST = re.compile(r"^\[(\w+)\],\s*(.+)$")
PRE = re.compile(r"^\[(\w+),\s*([^\]]+)\]!$")
PLAIN = re.compile(r"^\[(\w+)(?:,\s*([^\]]+))?\]$")


def register(token):
    token = token.strip()
    return NAMED[token] if token in NAMED else int(token[1:])


def immediate(token):
    match = IMMEDIATE.match(token.strip())
    value = int(match.group(2), 0)
    return -value if match.group(1) else value


class Machine:
    """Just enough ARM to run this one function: no flags beyond Z and N, no
    conditional execution, and only the addressing modes it actually uses."""

    def __init__(self, memory):
        self.mem = memory
        self.regs = [0] * 16
        self.zero = False
        self.negative = False

    def word(self, address):
        return int.from_bytes(self.mem[address:address + 4], "little")

    def store(self, address, value):
        self.mem[address:address + 4] = (value & 0xFFFFFFFF).to_bytes(4, "little")

    def source(self, tokens):
        head = tokens[0].strip()
        if head.startswith("#"):
            return immediate(head)
        value = self.regs[register(head)]
        if len(tokens) > 1:
            kind, amount = tokens[1].strip().split()
            amount = immediate(amount)
            if kind == "lsl":
                value = (value << amount) & 0xFFFFFFFF
            elif kind == "lsr":
                value = (value & 0xFFFFFFFF) >> amount
            else:
                raise AssertionError("unhandled shift: " + kind)
        return value

    def address_of(self, rest):
        post, pre, plain = POST.match(rest), PRE.match(rest), PLAIN.match(rest)
        if post:
            base = register(post.group(1))
            address = self.regs[base]
            self.regs[base] = (address + self.source(post.group(2).split(","))) & 0xFFFFFFFF
            return address
        if pre:
            base = register(pre.group(1))
            self.regs[base] = (self.regs[base] + self.source(pre.group(2).split(","))) & 0xFFFFFFFF
            return self.regs[base]
        base = register(plain.group(1))
        extra = plain.group(2)
        offset = self.source(extra.split(",")) if extra else 0
        return (self.regs[base] + offset) & 0xFFFFFFFF

    def run(self, decoded, length):
        pc = 0
        while pc < length:
            instruction = decoded[pc]
            mnemonic, operands = instruction.mnemonic, instruction.op_str
            following = pc + 4

            if mnemonic in ("push", "pop"):
                listed = [register(x) for x in operands.strip("{}").split(",")]
                if mnemonic == "push":
                    for reg in sorted(listed, reverse=True):
                        self.regs[13] -= 4
                        self.store(self.regs[13], self.regs[reg])
                else:
                    returning = False
                    for reg in sorted(listed):
                        value = self.word(self.regs[13])
                        self.regs[13] += 4
                        if reg == 15:
                            returning = True
                        else:
                            self.regs[reg] = value
                    if returning:
                        return
            elif mnemonic in ("ldr", "ldrb", "str"):
                destination, rest = operands.split(",", 1)
                destination = register(destination)
                address = self.address_of(rest.strip())
                if mnemonic == "str":
                    self.store(address, self.regs[destination])
                elif mnemonic == "ldrb":
                    self.regs[destination] = self.mem[address]
                else:
                    self.regs[destination] = self.word(address)
            elif mnemonic in ("add", "sub", "subs", "rsb", "orr"):
                tokens = operands.split(",")
                left = self.regs[register(tokens[1])]
                right = self.source(tokens[2:])
                if mnemonic == "add":
                    value = left + right
                elif mnemonic in ("sub", "subs"):
                    value = left - right
                elif mnemonic == "rsb":
                    value = right - left
                else:
                    value = left | right
                value &= 0xFFFFFFFF
                self.regs[register(tokens[0])] = value
                if mnemonic == "subs":
                    self.zero = value == 0
                    self.negative = bool(value & 0x80000000)
            elif mnemonic == "mov":
                tokens = operands.split(",")
                self.regs[register(tokens[0])] = self.source(tokens[1:]) & 0xFFFFFFFF
            elif mnemonic == "lsl":
                tokens = operands.split(",")
                self.regs[register(tokens[0])] = (
                    self.regs[register(tokens[1])] << immediate(tokens[2])) & 0xFFFFFFFF
            elif mnemonic == "bgt":
                if not self.zero and not self.negative:
                    following = int(operands[1:], 0)
            else:
                raise AssertionError("unhandled mnemonic: %s %s" % (mnemonic, operands))
            pc = following


def synthetic_memory():
    memory = bytearray(1 << 21)
    source = random.Random(20260907)
    for start, size in ((LUMA, 0x2000), (CHROMA, 0x800)):
        for address in range(start, start + size):
            memory[address] = source.randrange(256)
    for address in range(TABLE, TABLE + 0x1000):
        memory[address] = source.randrange(32)
    for offset, value in ((0x00, LUMA), (0x04, CHROMA), (0x08, DEST),
                          (0x0C, STRIDE), (0x10, WIDTH), (0x14, HEIGHT),
                          (0x18, TABLE)):
        memory[VIEW + offset:VIEW + offset + 4] = value.to_bytes(4, "little")
    return memory


def reference(memory, swap_red_green=False, dither=(False, True, True, False),
              chroma_plane=0x80):
    """The implementation in the stub's header. The keyword arguments exist so
    the test can mutate one claim at a time and prove the comparison sees it."""
    out = bytearray(memory)
    luma, chroma, table = LUMA, CHROMA, TABLE + 0x100
    row0, row1 = DEST, DEST + STRIDE
    luma_gap = 0x200 - WIDTH
    chroma_gap = 0x100 - (WIDTH >> 1)
    dest_gap = (STRIDE - WIDTH) * 2

    remaining_rows = HEIGHT
    while remaining_rows > 0:
        remaining_columns = WIDTH
        while remaining_columns > 0:
            co = memory[chroma] - 0x80
            cg = memory[chroma + chroma_plane] - 0x80
            chroma += 1
            green = table + cg
            red = table + co - cg
            blue = red - co * 2
            if swap_red_green:
                red, green = green, red

            quad = [memory[luma], memory[luma + 1],
                    memory[luma + 0x100], memory[luma + 0x101]]
            luma += 2
            quad = [value - 4 if drop else value for value, drop in zip(quad, dither)]

            for value, at in zip(quad, (row0, row0 + 2, row1, row1 + 2)):
                pixel = (0x8000 | memory[red + value]
                         | (memory[green + value] << 5)
                         | (memory[blue + value] << 10))
                out[at:at + 2] = pixel.to_bytes(2, "little")
            row0 += 4
            row1 += 4
            remaining_columns -= 2

        luma += luma_gap
        chroma += chroma_gap
        row0 += dest_gap
        row1 += dest_gap
        remaining_rows -= 2
    return bytes(out[DEST:DEST + STRIDE * HEIGHT])


@unittest.skipUnless(HAVE_CAPSTONE, "capstone is not installed")
@unittest.skipUnless(INDEX.is_file(), "build/func_index.json has not been generated")
class MobiClipBlitReferenceTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        entry = json.loads(INDEX.read_text(encoding="utf-8"))[FUNCTION]
        rom = bytes.fromhex(entry["hex"])
        engine = Cs(CS_ARCH_ARM, CS_MODE_ARM)
        cls.decoded = {i.address: i for i in engine.disasm(rom, 0)}
        cls.length = len(rom)
        assert len(cls.decoded) * 4 == cls.length, "function did not decode cleanly"

        memory = synthetic_memory()
        machine = Machine(memory)
        machine.regs[0] = VIEW
        machine.regs[13] = STACK
        machine.run(cls.decoded, cls.length)
        cls.rom_output = bytes(memory[DEST:DEST + STRIDE * HEIGHT])
        cls.memory = synthetic_memory()

    def test_reference_reproduces_the_rom_output(self):
        self.assertEqual(reference(self.memory), self.rom_output)

    def test_red_and_green_windows_are_not_interchangeable(self):
        self.assertNotEqual(reference(self.memory, swap_red_green=True), self.rom_output)

    def test_the_dither_exists(self):
        self.assertNotEqual(
            reference(self.memory, dither=(False, False, False, False)), self.rom_output)

    def test_the_dither_is_only_on_the_anti_diagonal(self):
        self.assertNotEqual(
            reference(self.memory, dither=(True, True, True, True)), self.rom_output)

    def test_the_chroma_planes_are_128_bytes_apart(self):
        self.assertNotEqual(reference(self.memory, chroma_plane=1), self.rom_output)


if __name__ == "__main__":
    unittest.main()
