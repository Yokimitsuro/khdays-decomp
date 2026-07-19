#!/usr/bin/env python3
"""Genera el contenido de un scratch de decomp.me para cualquier funcion del ROM.

    python tools/decompme.py func_ovNNN_ADDR [--out DIR]

Lee build/func_index.json (la verdad de base: hex + relocs + mode), desensambla en
el modo correcto, resuelve el pool literal contra los relocs y emite ensamblador
GAS con etiquetas -- que es lo que decomp.me sabe montar.

Notas de fidelidad, importantes al leer el diff en decomp.me:
  - Las llamadas THUMB->ARM salen del ROM como `blx`, pero mwcc emite `bl` y el
    proyecto arregla el interworking DESPUES del enlace (tools/fix_interwork.py).
    Aqui se emite `bl` para que esa diferencia conocida no ensucie el diff.
  - Las palabras del pool que llevan reloc se emiten como `.word <simbolo>`; sus
    bytes estan enmascarados en nuestra verificacion, asi que su valor no importa.
"""
import json, os, sys
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FLAGS = ("-O4,p -proc arm946e -interworking -lang c99 -enum int -char signed "
         "-inline on,noauto -Cpp_exceptions off -gccext,on")

AS_CANDIDATES = [
    "arm-none-eabi-as",
    "/c/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/12.2 mpacbti-rel1/bin/arm-none-eabi-as",
    r"C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\12.2 mpacbti-rel1\bin\arm-none-eabi-as",
]

def verify(out, where, insns, base, data, relocs, thumb, name):
    """Ensambla el .s con GAS y compara con los bytes del ROM (enmascarando relocs).

    GAS no siempre elige la MISMA codificacion que el compilador original cuando
    dos son legales -- el caso conocido es THUMB `subs rd, rd, #imm`, donde GAS
    prefiere la forma T2 (0x38xx) y mwcc/el ROM emiten la T1 (0x1exx), y no hay
    sintaxis para forzarla. Las instrucciones que no cuadran se reescriben con
    `.inst.n` / `.inst`, que fija la codificacion exacta.

    ⚠ NO usar `.short`/`.word` para esto: emiten los mismos bytes, pero GAS los
    marca como DATOS (simbolo de mapeo $d) y entonces objdump los imprime como
    `.word 0x1f091f00` en vez de desensamblarlos. En decomp.me eso sale como un
    diff falso permanente contra el C compilado, que si trae instrucciones.
    `.inst.n` mantiene el mapeo $t y objdump las vuelve a mostrar legibles.
    """
    import shutil, subprocess, tempfile
    asm_exe = next((c for c in AS_CANDIDATES if shutil.which(c) or os.path.exists(c)), None)
    if not asm_exe:
        print("[verify] no encuentro arm-none-eabi-as; me salto la comprobacion")
        return
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    from match import text_relocs

    by_off = {i.address - base: i for i in insns}
    tmp = tempfile.mkdtemp()
    for _ in range(len(where) + 1):
        s, o = os.path.join(tmp, "t.s"), os.path.join(tmp, "t.o")
        open(s, "w").write("\n".join(out) + "\n")
        r = subprocess.run([asm_exe, "-mcpu=arm946e-s", "-mthumb-interwork", "-o", o, s],
                           capture_output=True, text=True)
        if r.returncode != 0:
            print("[verify] GAS fallo:\n" + r.stderr); return
        mine, mrel = text_relocs(o)
        mrel = {k: v[0] for k, v in mrel.items()}
        if mrel != relocs:
            print("[verify] ⚠ los relocs no coinciden\n  mios=%s\n  ROM =%s" % (mrel, relocs))
        a, b = bytearray(mine), bytearray(data)
        if len(a) != len(b):
            print("[verify] ⚠ tamano %d != %d" % (len(a), len(b))); return
        for off in set(mrel) | set(relocs):
            for k in range(4):
                if off + k < len(b):
                    a[off + k] = 0; b[off + k] = 0
        bad = [i for i in range(len(b)) if a[i] != b[i]]
        if not bad:
            print("[verify] OK: %d bytes identicos al ROM (relocs enmascarados)" % len(b))
            return
        # Reescribir la instruccion que cubre el primer byte discrepante.
        ins = max((i for i in by_off.values() if i.address - base <= bad[0]),
                  key=lambda i: i.address)
        off = ins.address - base
        raw = data[off:off + ins.size]
        if len(raw) == 2:
            directive = ".inst.n 0x%04X" % int.from_bytes(raw, "little")
        else:
            directive = ".inst 0x%08X" % int.from_bytes(raw, "little")
        out[where[off]] = "\t%s  @ %s %s" % (directive, ins.mnemonic, ins.op_str)
        print("[verify] codificacion distinta en +0x%02X -> emitida cruda (%s %s)"
              % (off, ins.mnemonic, ins.op_str))
    print("[verify] ⚠ no converge; revisa a mano")

def main():
    name = sys.argv[1]
    idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
    if name not in idx:
        raise SystemExit("no esta en func_index.json: " + name)
    e = idx[name]
    data = bytes.fromhex(e["hex"])
    thumb = e["mode"] == "thumb"
    size = len(data)
    relocs = {off: sym for off, sym in e["relocs"]}
    # La direccion real solo importa para el calculo del pool; sale del nombre.
    base = int(name.rsplit("_", 1)[-1], 16)
    step = 2 if thumb else 4

    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)
    insns = list(md.disasm(data, base))

    # El pool se deriva de los destinos de las cargas pc-relativas: es exacto y no
    # depende de adivinar donde deja de haber codigo (las palabras del pool se
    # desensamblan como instrucciones perfectamente validas y enganan a cualquier
    # heuristica basada en "esto ya no parece codigo").
    def pcrel_target(i):
        imm = int(i.op_str.split("#")[1].rstrip("]"), 16)
        return (((i.address + 4) & ~3) if thumb else i.address + 8) + imm - base

    # Una sola pasada hacia delante: en cuanto una carga apunta a X, el codigo no
    # puede pasar de X, y las "instrucciones" de mas alla ya no se miran.
    code_end, pool = size, set()
    for i in insns:
        if i.address - base >= code_end:
            break
        if "[pc," in i.op_str:
            t = pcrel_target(i)
            pool.add(t)
            code_end = min(code_end, t)
    pool = [o for o in sorted(pool) if o + 4 <= size]

    targets = set()
    for i in insns:
        if i.address - base >= code_end:
            continue
        if i.mnemonic.startswith("b") and i.op_str.startswith("#"):
            targets.add(int(i.op_str[1:], 16))

    def lbl(addr):
        return "_%08X" % addr

    out = []
    where = {}   # offset de la instruccion -> indice de su linea en out
    out.append("\t.text")
    # capstone emite sintaxis UAL (lsls/adds/movs); GAS la rechaza en .thumb sin esto.
    out.append("\t.syntax unified")
    out.append("\t.thumb" if thumb else "\t.arm")
    out.append("\t.global %s" % name)
    if thumb:
        out.append("\t.thumb_func")
    out.append("%s:" % name)
    for i in insns:
        off = i.address - base
        if off >= code_end:
            break
        if i.address in targets:
            out.append("%s:" % lbl(i.address))
        where[off] = len(out)
        mn, ops = i.mnemonic, i.op_str
        if mn in ("bl", "blx") and ops.startswith("#"):
            # ver nota de interworking en la cabecera
            out.append("\tbl %s" % relocs.get(off, ops))
        elif mn.startswith("b") and ops.startswith("#"):
            out.append("\t%s %s" % (mn, lbl(int(ops[1:], 16))))
        elif "[pc," in ops:
            # carga del pool: sustituir por la etiqueta destino
            pcrel = int(ops.split("#")[1].rstrip("]"), 16)
            src = (i.address + 4) & ~3 if thumb else i.address + 8
            out.append("\t%s %s, %s" % (mn, ops.split(",")[0], lbl(src + pcrel)))
        else:
            out.append("\t%s %s" % (mn, ops))
    out.append("\t.align 2, 0")
    for o in pool:
        val = relocs.get(o)
        if val is None:  # constante literal, sin reloc: va tal cual
            val = "0x%08X" % int.from_bytes(data[o:o + 4], "little")
        out.append("%s: .word %s" % (lbl(base + o), val))

    if "--verify" in sys.argv:
        verify(out, where, insns, base, data, relocs, thumb, name)
    asm = "\n".join(out)

    ctx = ["typedef signed char s8;    typedef unsigned char u8;",
           "typedef signed short s16;  typedef unsigned short u16;",
           "typedef signed int s32;    typedef unsigned int u32;",
           "typedef signed long long s64; typedef unsigned long long u64;"]
    for o in pool:
        sym = relocs[o]
        ctx.append("extern %s;" % ("void %s()" % sym if sym.startswith("func_")
                                   else "char %s[]" % sym))
    for o, sym in relocs.items():
        if o < code_end and sym.startswith("func_"):
            ctx.append("extern void %s();" % sym)
    context = "\n".join(dict.fromkeys(ctx))

    print("=" * 70)
    print("DECOMP.ME SCRATCH para %s  (%d B, %s)" % (name, size, e["mode"]))
    print("=" * 70)
    print("\n[Platform]  Nintendo DS")
    print("[Preset]    Custom")
    print("[Compiler]  3.0 build 139 (MW 2.0sp2p4)")
    print("\n[Compiler flags]")
    print(FLAGS + (" -thumb" if thumb else ""))
    print("\n[Diff label]")
    print(name)
    print("\n[Target assembly]")
    print(asm)
    print("\n[Context]")
    print(context)
    print("\n" + "=" * 70)

    if "--out" in sys.argv:
        d = sys.argv[sys.argv.index("--out") + 1]
        os.makedirs(d, exist_ok=True)
        open(os.path.join(d, name + ".s"), "w").write(asm + "\n")
        open(os.path.join(d, name + ".ctx.c"), "w").write(context + "\n")
        print("escrito en", d)

if __name__ == "__main__":
    main()
