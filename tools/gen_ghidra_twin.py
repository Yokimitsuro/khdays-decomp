"""Generate an overlay's Ghidra pass scripts from an already-done twin's.

These overlays are byte-identical instances of one panel class, so the semantic
pass is the same work with a different address space and address. Deriving the
scripts keeps the plate comments and type decisions identical instead of letting
them drift between copies, which is the whole point of calling them one class.

Usage: python build/try/genghidra.py <srcOv> <dstOv> <displacement>
"""
import io, os, re, sys

HOME = os.path.expanduser("~")
SCRIPTS = os.path.join(HOME, "ghidra_scripts")
src_ov, dst_ov, disp = sys.argv[1], sys.argv[2], int(sys.argv[3], 16)

Src = src_ov.capitalize()   # ov066 -> Ov066
Dst = dst_ov.capitalize()

made = []
for f in sorted(os.listdir(SCRIPTS)):
    if not f.startswith("Khdays" + Src) or not f.endswith(".py"):
        continue
    s = io.open(os.path.join(SCRIPTS, f), encoding="utf-8").read()
    m = re.search(r"^ADDR = (0x[0-9a-fA-F]+)", s, re.M)
    if not m:
        continue
    new_addr = int(m.group(1), 16) + disp
    s = s.replace('SPACE = "arm9_%s"' % src_ov, 'SPACE = "arm9_%s"' % dst_ov)
    s = re.sub(r"^ADDR = 0x[0-9a-fA-F]+", "ADDR = 0x%08x" % new_addr, s, flags=re.M)
    s = s.replace(Src + "_", Dst + "_").replace(Src.lower(), dst_ov)
    s = s.replace("Second instance", "Another instance")
    out = f.replace("Khdays" + Src, "Khdays" + Dst)
    io.open(os.path.join(SCRIPTS, out), "w", encoding="utf-8").write(s)
    made.append((out, "0x%08x" % new_addr))

print("generated %d scripts for %s" % (len(made), dst_ov))
for name, a in made:
    print("   %-40s %s" % (name, a))
