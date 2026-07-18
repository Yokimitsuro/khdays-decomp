#!/usr/bin/env python3
"""Genera los .c de la familia de constructores func_0203d15c a partir del desensamblado.

    python tools/gen_d15c_ctor.py            # informe: que casa y que no
    python tools/gen_d15c_ctor.py --write    # escribe los que casan en calls/

La forma (35 instrucciones, ver tools/nearfam.py) es identica en ~70 overlays y solo cambian
CINCO cosas, todas legibles del desensamblado + los relocs:

  - el tamaño del objeto           (`mov r0, #SIZE` antes del `bl func_0203d15c`)
  - un byte de tipo                (`mov r2, #N`, que ademas es el 3er argumento de OS_SPrintf)
  - los tres offsets del objeto    (strb #A, str #B tras la llamada al hash, str #C)
  - los dos simbolos               (la cadena de formato y el callback), que vienen de los relocs

NO asumas ninguno de los cinco: dos overlays de la misma forma difieren en el tamaño Y en el
byte de tipo, y algunos tambien en los offsets. Todo se extrae, nada se hereda.

Cada fichero se verifica con verify_idx antes de escribirse; los que no casan se reportan y
NO se escriben (regla dura del proyecto: nada que no case en calls/).
"""
import json
import os
import re
import subprocess
import sys

from capstone import CS_ARCH_ARM, CS_MODE_ARM, Cs

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
MD = Cs(CS_ARCH_ARM, CS_MODE_ARM)

TEMPLATE = """extern int func_0203d15c(int a);
extern void OS_SPrintf(char *buf, const char *fmt, int a);
extern int func_ov107_020c9c24(char *buf);
extern void func_ov107_020c6624(int a, int b);
extern const char {fmt}[];
extern void {cb}(int);

int {name}(int param_1) {{
    char buf[{buflen:#x}] = {{0}};
    int obj = func_0203d15c({size:#x});
    *(signed char *)(obj + {off_type:#x}) = {typeval};
    OS_SPrintf(buf, {fmt}, {typeval});
    *(int *)(obj + {off_hash:#x}) = func_ov107_020c9c24(buf);
    *(int *)(obj + {off_cb:#x}) = (int){cb};
    func_ov107_020c6624(obj, param_1);
    return obj;
}}
"""


def parse(name):
    e = IDX[name]
    ins = list(MD.disasm(bytes.fromhex(e["hex"]), int(name[-8:], 16)))
    mn = [i.mnemonic for i in ins]
    ops = [i.op_str for i in ins]
    rel = dict(e["relocs"])

    def imm(s):
        m = re.search(r"#(-?(?:0x)?[0-9a-fA-F]+)", s)
        return int(m.group(1), 0) if m else None

    d = {"name": name}
    # tamaño: el mov r0, #X que precede al primer bl
    first_bl = mn.index("bl")
    for k in range(first_bl - 1, -1, -1):
        if mn[k] == "mov" and ops[k].startswith("r0,"):
            d["size"] = imm(ops[k]); break
    # longitud del buffer: N iteraciones de 4 bytes + 1 (el strb final)
    for k in range(first_bl):
        if mn[k] == "mov" and ops[k].startswith("r0,") and k < 6:
            d["buflen"] = imm(ops[k]) * 4 + 1; break
    # byte de tipo y su offset
    for k, (m, o) in enumerate(zip(mn, ops)):
        if m == "strb" and "r4" in o and k > first_bl:
            d["off_type"] = imm(o)
            for j in range(k - 1, first_bl, -1):
                if mn[j] == "mov" and ops[j].startswith("r2,"):
                    d["typeval"] = imm(ops[j]); break
            break
    # offsets de los dos str a r4 despues del hash
    strs = [imm(o) for m, o in zip(mn, ops) if m == "str" and "[r4," in o]
    if len(strs) >= 2:
        d["off_hash"], d["off_cb"] = strs[0], strs[1]
    # simbolos: la cadena de formato y el callback salen de los dos relocs de datos/funcion
    tail = [v for k, v in sorted(rel.items()) if k >= len(ins) * 4 - 12]
    for v in tail:
        if v.startswith("data_"):
            d["fmt"] = v
        elif v.startswith("func_"):
            d["cb"] = v
    return d


def main():
    write = "--write" in sys.argv
    tpl_shape = None
    ins0 = list(MD.disasm(bytes.fromhex(IDX["func_ov114_020cbf38"]["hex"]), 0x020cbf38))
    tpl_shape = " ".join(i.mnemonic for i in ins0)

    todo = []
    for name, e in IDX.items():
        if not name.startswith("func_ov") or e["size"] != len(ins0) * 4:
            continue
        try:
            ins = list(MD.disasm(bytes.fromhex(e["hex"]), int(name[-8:], 16)))
        except ValueError:
            continue
        if " ".join(i.mnemonic for i in ins) == tpl_shape:
            todo.append(name)

    ok, bad = [], []
    outdir = os.path.join(ROOT, "build", "try", "d15c")
    os.makedirs(outdir, exist_ok=True)
    for name in sorted(todo):
        d = parse(name)
        missing = [k for k in ("size", "buflen", "off_type", "typeval",
                               "off_hash", "off_cb", "fmt", "cb") if k not in d]
        if missing:
            bad.append((name, "no extraido: " + ",".join(missing))); continue
        p = os.path.join(outdir, name + ".c")
        open(p, "w", newline="\n").write(TEMPLATE.format(**d))
        r = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "verify_idx.py"), p, name],
                           capture_output=True, text=True, cwd=ROOT)
        if "MATCH" in r.stdout:
            ok.append((name, p))
        else:
            bad.append((name, r.stdout.strip().splitlines()[-1] if r.stdout.strip() else "?"))

    print("candidatas con esta forma: %d   MATCH: %d   no casan: %d"
          % (len(todo), len(ok), len(bad)))
    for name, why in bad:
        print("  NO  %-28s %s" % (name, why))

    if write:
        import shutil
        n = 0
        for name, p in ok:
            ov = re.match(r"func_(ov\d+)_", name).group(1)
            dst = os.path.join(ROOT, "src", "overlays", ov, "calls", name + ".c")
            if os.path.exists(dst):
                continue
            os.makedirs(os.path.dirname(dst), exist_ok=True)
            shutil.copy(p, dst)
            n += 1
        print("escritos %d ficheros nuevos en calls/" % n)


if __name__ == "__main__":
    main()
