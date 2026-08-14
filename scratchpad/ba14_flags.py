"""Diagnostic sweep of compiler flags. The project already models per-file
compiler overrides, so a per-file flag difference is a plausible hypothesis."""
import sys
import os
import re
import json
import itertools
import subprocess

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

NAME = "func_ov002_02069b14"
idx = json.load(open("build/func_index.json"))
e = idx[NAME]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
OM = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(orig), 0)]

MWCC = os.path.join("tools", "mwccarm", "3.0_patch4", "mwccarm.exe")
LIC = os.path.join(os.getcwd(), "tools", "mwccarm", "license.dat")
SRC = "build/try/func_ov002_02069b14.c"

BASE = ["-proc", "arm946e", "-interworking", "-lang", "c99",
        "-Cpp_exceptions", "off", "-gccext,on", "-thumb"]

OPT = ["-O4,p", "-O4,s", "-O4", "-O3,p", "-O3,s", "-O2,p", "-O2,s",
       "-O1,p", "-O0"]
INLINE = [["-inline", "on,noauto"], ["-inline", "on"], ["-inline", "off"],
          ["-inline", "auto"], ["-inline", "all"]]
ENUMF = [["-enum", "int"], ["-enum", "min"]]
CHARF = [["-char", "signed"], ["-char", "unsigned"]]


def prosig(txt):
    save = pool = None
    for k, t in enumerate(txt[:8]):
        if save is None and re.match(r"^adds r\d, r0, #0$", t):
            save = k
        m = re.match(r"^ldr (r\d), \[pc", t)
        if pool is None and m:
            pool = (k, m.group(1))
    return save, pool


def main():
    out = "build/try/ba14_flags.o"
    env = dict(os.environ, LM_LICENSE_FILE=LIC)
    sigs = {}
    best = (99, None)
    n = 0
    for opt in OPT:
        for inl in INLINE:
            for en in ENUMF:
                for ch in CHARF:
                    flags = [opt] + BASE + inl + en + ch
                    r = subprocess.run([MWCC, "-c"] + flags + ["-o", out, SRC],
                                       capture_output=True, text=True, env=env)
                    if r.returncode != 0:
                        continue
                    try:
                        mine, mrel = text_relocs(out)
                    except Exception:
                        continue
                    n += 1
                    if len(mine) != len(orig):
                        continue
                    a = bytearray(orig)
                    b = bytearray(mine)
                    for off in set(orel) | set(mrel):
                        for k in range(4):
                            if off + k < len(a):
                                a[off + k] = 0
                                b[off + k] = 0
                    nd = sum(1 for i in range(len(a)) if a[i] != b[i])
                    mm = [i.mnemonic + " " + i.op_str
                          for i in md.disasm(bytes(mine), 0)]
                    sig = prosig(mm)
                    key = " ".join([opt] + inl + en + ch)
                    if sig not in sigs or nd < sigs[sig][0]:
                        sigs[sig] = (nd, key)
                    if nd < best[0]:
                        best = (nd, key)
                    if nd == 0:
                        print("MATCH with flags: %s" % key)
                        return
    print("compiled %d flag combinations at the right size" % n)
    print("ROM signature: %s" % (prosig(OM),))
    for sig, (nd, key) in sorted(sigs.items(), key=lambda x: x[1][0]):
        print("   sig=%-18s best bytes=%-3d via %s" % (str(sig), nd, key))
    print("best bytes=%d via %s" % (best[0], best[1]))


main()
