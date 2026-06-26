#!/usr/bin/env python3
"""Para cada funcion ya decompilada, genera el .c de sus DUPLICADAS idenitcas
   (mismo codigo+relocs, otro nombre) y lo verifica byte-exacto. Aceleracion gratis."""
import json, os, glob, re, subprocess
from collections import defaultdict
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))

# grupos de identicas
groups = defaultdict(list)
for name, d in idx.items():
    key = d["hex"] + "|" + "|".join("%d:%s" % tuple(r) for r in d["relocs"])
    groups[key].append(name)
name2key = {n: (d["hex"] + "|" + "|".join("%d:%s" % tuple(r) for r in d["relocs"]))
            for n, d in idx.items()}

def done_set():
    s = {}
    for cf in glob.glob(os.path.join(ROOT, "src", "auto", "*.c")): s[os.path.splitext(os.path.basename(cf))[0]] = ("auto", cf)
    for cf in glob.glob(os.path.join(ROOT, "src", "calls", "*.c")): s[os.path.splitext(os.path.basename(cf))[0]] = ("calls", cf)
    return s

def verify(name, cf, kind):
    d = idx[name]
    if d["relocs"]:
        delink = os.path.join(ROOT, "build", "delinks", d["module"] + ".o")
        a = ["python", os.path.join(ROOT, "tools", "match.py"), cf, "--obj", delink, "--func", name]
    else:
        a = ["python", os.path.join(ROOT, "tools", "match.py"), cf, d["hex"]]
    return ">>> MATCH <<<" in subprocess.run(a, capture_output=True, text=True).stdout

done = done_set()
created = 0
for rep, (kind, cf) in list(done.items()):
    if rep not in name2key: continue
    src = open(cf).read()
    for dup in groups[name2key[rep]]:
        if dup == rep or dup in done: continue
        # copiar el .c del rep renombrando la funcion
        newsrc = re.sub(r"\b" + re.escape(rep) + r"\b", dup, src)
        outdir = os.path.join(ROOT, "src", kind)
        ncf = os.path.join(outdir, dup + ".c")
        open(ncf, "w").write(newsrc)
        if verify(dup, ncf, kind):
            created += 1; done[dup] = (kind, ncf)
        else:
            os.remove(ncf)
print("nuevas funciones por DEDUP (verificadas byte-exactas): %d" % created)
print("total decompilado ahora: %d" % (len(glob.glob(os.path.join(ROOT,'src','auto','*.c'))) +
                                        len(glob.glob(os.path.join(ROOT,'src','calls','*.c')))))
