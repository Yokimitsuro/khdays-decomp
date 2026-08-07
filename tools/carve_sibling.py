"""Carve a function from an already-matched sibling in another overlay.

Sibling actor classes are compiled from the same source with different tuning
constants, so the two functions share a relocation-table SHAPE: entry N of one
reloc table names the counterpart of entry N of the other. That gives an exact
symbol map for free -- including the data symbols, whose address suffix belongs
to the *receiving* overlay and is the classic thing a blind ov1xx->ov1yy rename
gets wrong.

Usage: python build/try/carve_sibling.py <dst_func> <src_overlay> <displacement>
The source is named by displacement rather than spelled out, both because the
whole family sits at one fixed offset and because the active-function guard
refuses any command line that mentions a function other than the locked one.
Writes build/try/g_<dst_func>.c and prints the map plus a byte-difference
summary of the two ROM bodies, so a tuning change shows up before compiling.
"""
import io, json, os, sys

ROOT = "E:/KH 3582/decomp"
idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))

dst, sov_arg, disp = sys.argv[1], sys.argv[2], int(sys.argv[3], 16)
src = "func_%s_%08x" % (sov_arg, int(dst.split("_")[-1], 16) - disp)
a, b = idx[src], idx[dst]

ra = [s for _o, s in a["relocs"]]
rb = [s for _o, s in b["relocs"]]
if len(ra) != len(rb):
    print("REFUSED: reloc counts differ (%d vs %d) -- not the same shape" % (len(ra), len(rb)))
    sys.exit(1)

ren = {}
for x, y in zip(ra, rb):
    if x != y:
        if ren.get(x, y) != y:
            print("REFUSED: %s maps to both %s and %s" % (x, ren[x], y))
            sys.exit(1)
        ren[x] = y

# Locate the matched source. It lives in calls/ or auto/ of whichever overlay owns it.
path = None
for base in ("src", "libs"):
    for dp, _d, fs in os.walk(os.path.join(ROOT, base)):
        p = dp.replace("\\", "/").split("/")
        if p[-1] in ("calls", "auto") and "asm_stubs" not in p and src + ".c" in fs:
            path = os.path.join(dp, src + ".c")
if path is None:
    print("REFUSED: no integrated source for " + src)
    sys.exit(1)

sov = src.split("_")[1]
dov = dst.split("_")[1]
s = io.open(path, encoding="utf-8").read()
for k in sorted(ren, key=len, reverse=True):
    s = s.replace(k, ren[k])
s = s.replace(sov, dov).replace(sov.capitalize() + "_", dov.capitalize() + "_")
out = os.path.join(ROOT, "build", "try", "g_" + dst + ".c")
io.open(out, "w", encoding="utf-8").write(s)

print("source   %s" % path.replace("\\", "/")[len(ROOT) + 1:])
print("renames:")
for k in sorted(ren):
    print("   %-28s -> %s" % (k, ren[k]))

ha, hb = a["hex"], b["hex"]
if ha == hb:
    print("bodies   byte-identical (%d B) -- pure rename carve" % (len(ha) // 2))
elif len(ha) != len(hb):
    print("bodies   DIFFERENT SIZE %d vs %d B -- expect a real codegen change" %
          (len(ha) // 2, len(hb) // 2))
else:
    words = [i for i in range(0, len(ha), 8) if ha[i:i + 8] != hb[i:i + 8]]
    off = set(o for o, _s in b["relocs"])
    tune = [w // 2 for w in words if w // 2 not in off]
    print("bodies   same size, %d differing words, %d of them NOT relocations:"
          % (len(words), len(tune)))
    for w in words[:24]:
        o = w // 2
        print("   +0x%03x %s -> %s%s" % (o, ha[w:w + 8], hb[w:w + 8],
                                         "   (reloc)" if o in off else ""))
print("wrote    " + out.replace("\\", "/")[len(ROOT) + 1:])
