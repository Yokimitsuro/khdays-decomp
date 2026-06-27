#!/usr/bin/env python3
"""Find src/auto/<X>.c files that are 'void f(){}' stubs whose original is
larger than 4 bytes (so the stub is a false-positive that should be deleted)."""
import os, re, sys, json

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INDEX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))

# Build a reverse map: every src/ basename -> original func_X (post-rename
# the names.json mapping changes some, but for stubs we mostly care about
# files still named func_X). For renamed files we'd need the full apply_names
# logic; let's just handle func_XXXXX-named files for safety.

bad = []
for d in ("src/auto", "src/calls"):
    dp = os.path.join(ROOT, d)
    if not os.path.isdir(dp): continue
    for f in os.listdir(dp):
        if not f.endswith(".c"): continue
        full = os.path.join(dp, f)
        txt = open(full).read().strip()
        # detect "void NAME(...) {}" with empty body, no body content, short file
        m = re.search(r"\bvoid\s+(\w+)\s*\([^)]*\)\s*\{\s*\}", txt)
        if not m: continue
        if "extern" in txt or "return" in txt: continue
        if len(txt) > 100: continue
        # name we'll use to look up in INDEX
        base = f[:-2]
        # if it's a func_X name, look directly
        info = INDEX.get(base)
        if info is None:
            # try strip _0xADDR suffix and look up by addr
            m2 = re.match(r"^(.+)_0x([0-9a-f]{8})$", base)
            if m2:
                addr = int(m2.group(2), 16)
                # find the entry with this addr in main
                for k,v in INDEX.items():
                    if k.endswith("%08x" % addr) and v["size"]:
                        info = v; break
            if info is None: continue
        # bad if original is > 4 bytes (real body)
        if info["size"] > 4:
            bad.append((full, base, info["size"]))

print("BAD stubs (empty void() but original is non-trivial):", len(bad))
for full, name, size in bad[:30]:
    print(" %s (%s, orig %d bytes)" % (os.path.relpath(full, ROOT), name, size))
if "--apply" in sys.argv:
    for full, _, _ in bad:
        os.remove(full)
    print("DELETED", len(bad), "files")
