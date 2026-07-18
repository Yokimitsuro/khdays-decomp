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

   MODO ARM/THUMB (arreglado 2026-07-18): la primera version compilaba SIEMPRE en ARM.
   Sobre una funcion THUMB eso da "size N" en las 27 builds -- o sea el barrido entero
   dice "ningun compilador la reproduce" sobre C que hace MATCH perfecto. Verificado con
   func_02020974 (2 B THUMB): 27/27 "size 4". Es el falso negativo mas caro posible,
   porque es justo la evidencia con la que se justifica un park. Hay 994 funciones THUMB
   con C real, no es un caso raro. Ahora el modo se lee de config/arm9/**/symbols.txt
   (kind:function(thumb...)) y, si el simbolo no aparece, se prueban ARM y THUMB.
"""
import os, re, sys, json, glob, subprocess
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


_MODES = None


def mode_of(name):
    """'thumb' / 'arm' / None (desconocido -> el caller prueba los dos).
       symbols.txt es la fuente autoritativa: kind:function(arm|thumb,size=...)."""
    global _MODES
    if _MODES is None:
        _MODES = {}
        for p in glob.glob(os.path.join(ROOT, "config/arm9/**/symbols.txt"), recursive=True):
            with open(p, encoding="utf-8", errors="replace") as fh:
                for ln in fh:
                    m = re.match(r"\s*(\S+)\s", ln)
                    if not m:
                        continue
                    if "function(thumb" in ln:
                        _MODES[m.group(1)] = "thumb"
                    elif "function(arm" in ln:
                        _MODES[m.group(1)] = "arm"
    return _MODES.get(name)


def builds():
    out = []
    for p in glob.glob(os.path.join(ROOT, "tools/mwccarm/**/mwccarm.exe"), recursive=True):
        out.append(p.replace(chr(92), "/"))
    return sorted(out)


def compare(exe, cpath, name, tmp, thumb=False):
    o = os.path.join(tmp, name + ".o")
    env = dict(os.environ, LM_LICENSE_FILE=LIC)
    flags = FLAGS + (["-thumb"] if thumb else [])
    r = subprocess.run([exe, "-c", *flags, "-o", o, cpath],
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


def compare_auto(exe, cpath, name, tmp, mode):
    """Modo conocido -> una compilacion. Desconocido -> ARM y luego THUMB, y se queda
       con el mejor: un fallo solo-ARM sobre una funcion THUMB es indistinguible de C
       rota (ver la nota de modo en el docstring)."""
    if mode:
        return compare(exe, cpath, name, tmp, mode == "thumb")
    a = compare(exe, cpath, name, tmp, False)
    if a == "MATCH":
        return a
    t = compare(exe, cpath, name, tmp, True)
    return t + " (t)" if t == "MATCH" else a


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
        cases.append((nm, cp, mode_of(nm)))
    tmp = os.path.join(ROOT, "build", "sweep")
    os.makedirs(tmp, exist_ok=True)
    for nm, _cp, md in cases:
        print("# %s: %s" % (nm, md or "modo desconocido -> se prueban ARM y THUMB"))
    hdr = "%-26s | %s" % ("build", " | ".join("%-13s" % n[-8:] for n, _, _ in cases))
    print(hdr)
    print("-" * len(hdr))
    for exe in builds():
        row = [compare_auto(exe, cp, nm, tmp, md) for nm, cp, md in cases]
        tag = exe.replace(ROOT.replace(chr(92), "/") + "/", "").replace("tools/mwccarm/", "").replace("/mwccarm.exe", "")
        star = "  *** MATCH" if any(x == "MATCH" for x in row) else ""
        print("%-26s | %s%s" % (tag, " | ".join("%-13s" % x for x in row), star))


if __name__ == "__main__":
    main()
