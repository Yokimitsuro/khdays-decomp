#!/usr/bin/env python3
"""Corre tools/match.py sobre N archivos al azar de src/auto + src/calls
para verificar que los delinks regenerados validan los renames SDK."""
import os, sys, random, subprocess
from elftools.elf.elffile import ELFFile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
N = int(sys.argv[1]) if len(sys.argv)>1 else 30

# Detect thumb mode: symbol value LSB or sym['st_info']['mips_isa']? On ARM,
# thumb funcs are tagged via STT_FUNC + st_value odd OR via $t mapping symbol.
# Easier: detect from raw bytes (thumb stubs have 'bx lr' = '7047' suffix when arm
# stubs have '1eff2fe1'). We'll read the func bytes from the delink and check.
import json
INDEX_PATH = os.path.join(ROOT, "build", "func_index.json")
INDEX = json.load(open(INDEX_PATH)) if os.path.isfile(INDEX_PATH) else {}

# Build addr -> delink_path index by scanning all delinks
addr2delink = {}
addr2sym = {}
sym_is_thumb = {}
for f in os.listdir(os.path.join(ROOT, "build", "delinks")):
    if not f.endswith(".o"): continue
    p = os.path.join(ROOT, "build", "delinks", f)
    e = ELFFile(open(p, "rb"))
    st = e.get_section_by_name(".symtab")
    if not st: continue
    # also collect $t / $a mapping symbols
    thumb_addrs = set()
    for sym in st.iter_symbols():
        if sym.name == "$t":
            thumb_addrs.add(sym["st_value"] & ~1)
    for sym in st.iter_symbols():
        if sym["st_info"]["type"]=="STT_FUNC" and sym.name and not sym.name.startswith("$") and sym["st_size"]>0:
            addr2delink[sym.name] = p
            addr2sym[sym.name] = sym["st_value"] & ~1
            # detect thumb: st_value LSB set (the dsd ELF convention)
            sym_is_thumb[sym.name] = bool(sym["st_value"] & 1) or (sym["st_value"] & ~1) in thumb_addrs

from _src_roots import src_roots
pool=[]
for d in src_roots(ROOT):
    dp = os.path.join(ROOT, d)
    if not os.path.isdir(dp): continue
    for fn in os.listdir(dp):
        if not fn.endswith(".c"): continue
        sym = fn[:-2]
        if sym in addr2delink:
            pool.append((os.path.join(dp,fn), sym))

random.seed(7)
sample = pool if N == 0 else random.sample(pool, min(N, len(pool)))
ok=fail=0
fails=[]
for cpath, sym in sample:
    delink = addr2delink[sym]
    cmd = ["python", os.path.join(ROOT,"tools","match.py"), cpath, "--obj", delink, "--func", sym]
    if sym_is_thumb.get(sym): cmd.append("--thumb")
    r = subprocess.run(cmd, capture_output=True, text=True, env=dict(os.environ))
    out = r.stdout + r.stderr
    if ">>> MATCH <<<" in out: ok+=1
    else:
        fail+=1
        last = [l for l in out.splitlines() if l.strip()][-3:]
        fails.append((sym, last))

print("%d/%d MATCH" % (ok, len(sample)))
for sym, last in fails[:8]:
    print("FAIL %s:" % sym)
    for l in last: print("   "+l[:160])

if __name__=="__main__": pass
