#!/usr/bin/env python3
"""Compila una o varias funciones C con TODAS las builds de mwccarm disponibles y
   compara byte-exacto (reloc-aware) contra build/func_index.json.

       python tools/build_sweep.py <func_name> [<func_name> ...]
       python tools/build_sweep.py --file <a.c>:<func> [...]

   Para que sirva de algo, dale SOLO fuentes ya probadas correctas (mismo tamano y
   mismo stream de instrucciones que la ROM). Barrer C dudoso no dice nada: fue
   exactamente el error de la bateria de ties original, que se corrio contra fuentes
   que resultaron tener bugs ordinarios.

   Resultado 2026-07-17 sobre los 4 casos "stream identico, una ranura caller-saved":
   las 12 builds de 2.0/* + 3.0_136_patched + 3.0_patch4 dan salida IDENTICA entre si;
   1.2/* y dsi/* son de otra epoca (tamanos muy distintos). O sea: dentro del set que
   tenemos, la pregunta "que point release" no tiene traccion.
"""
import os, sys, json, glob, subprocess
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from match import text_relocs, FLAGS

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LIC = os.path.join(ROOT, "tools", "mwccarm", "license.dat")
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))


def find_source(name):
    """OJO: excluir asm_stubs/. El glob src/**/calls/ tambien casa
       src/overlays/ovNNN/asm_stubs/calls/, y un stub de asm reproduce la ROM con
       CUALQUIER compilador -> el barrido entero sale MATCH y no significa nada.
       (Pisado en la primera ejecucion del tool, 2026-07-17.)"""
    for sub in ("auto", "calls", "nonmatching"):
        for pat in ("src/**/%s/%s.c" % (sub, name), "libs/**/%s/%s.c" % (sub, name)):
            for h in glob.glob(os.path.join(ROOT, pat), recursive=True):
                h = h.replace(chr(92), "/")
                if "/asm_stubs/" in h:
                    continue
                return h
    return None


def builds():
    out = []
    for p in glob.glob(os.path.join(ROOT, "tools/mwccarm/**/mwccarm.exe"), recursive=True):
        out.append(p.replace(chr(92), "/"))
    return sorted(out)


def compare(exe, cpath, name, tmp):
    o = os.path.join(tmp, name + ".o")
    env = dict(os.environ, LM_LICENSE_FILE=LIC)
    r = subprocess.run([exe, "-c", *FLAGS, "-o", o, cpath],
                       capture_output=True, text=True, env=env)
    if r.returncode != 0:
        return "compile-fail"
    try:
        mine, mr = text_relocs(o)
    except Exception:
        return "obj-fail"
    e = IDX[name]
    orig = bytearray.fromhex(e["hex"])
    if len(mine) != len(orig):
        return "size %d" % len(mine)
    orel = {off: s for off, s in e["relocs"]}
    mrel = {off: n for off, (n, _t) in mr.items()}
    m, ob = bytearray(mine), bytearray(orig)
    for off in set(mrel) | set(orel):
        for k in range(4):
            if off + k < len(ob):
                m[off + k] = 0
                ob[off + k] = 0
    nd = sum(1 for a, b in zip(m, ob) if a != b)
    if nd == 0 and mrel == orel:
        return "MATCH"
    return "%d off" % nd


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("-")]
    if not args:
        raise SystemExit(__doc__)
    cases = []
    for a in args:
        if ":" in a:
            cp, nm = a.rsplit(":", 1)
        else:
            nm, cp = a, find_source(a)
        if not cp or not os.path.exists(cp):
            raise SystemExit("no source for " + nm)
        if nm not in IDX:
            raise SystemExit("not in func_index: " + nm)
        cases.append((nm, cp))
    tmp = os.path.join(ROOT, "build", "sweep")
    os.makedirs(tmp, exist_ok=True)
    hdr = "%-26s | %s" % ("build", " | ".join("%-13s" % n[-8:] for n, _ in cases))
    print(hdr)
    print("-" * len(hdr))
    for exe in builds():
        row = [compare(exe, cp, nm, tmp) for nm, cp in cases]
        tag = exe.replace(ROOT.replace(chr(92), "/") + "/", "").replace("tools/mwccarm/", "").replace("/mwccarm.exe", "")
        star = "  *** MATCH" if any(x == "MATCH" for x in row) else ""
        print("%-26s | %s%s" % (tag, " | ".join("%-13s" % x for x in row), star))


if __name__ == "__main__":
    main()
