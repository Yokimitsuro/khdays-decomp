"""Diagnostic: the project supports per-file compiler-version overrides and one
file already uses one. Compile the candidate with every mwccarm in the tree and
report the prologue signature and the masked byte difference."""
import sys
import os
import re
import json
import glob
import subprocess

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

NAME = "func_ov002_02069b14"
idx = json.load(open("build/func_index.json"))
e = idx[NAME]
orig = bytearray.fromhex(e["hex"])
orel = {off: sym for off, sym in e["relocs"]}
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
OM = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(orig), 0)]

FLAGS = ["-O4,p", "-proc", "arm946e", "-interworking", "-lang", "c99",
         "-enum", "int", "-char", "signed", "-inline", "on,noauto",
         "-Cpp_exceptions", "off", "-gccext,on", "-thumb"]
LIC = os.path.join(os.getcwd(), "tools", "mwccarm", "license.dat")
SRC = "build/try/func_ov002_02069b14.c"


def prosig(txt):
    save = pool = None
    for k, t in enumerate(txt[:8]):
        if save is None and re.match(r"^adds r\d, r0, #0$", t):
            save = k
        m = re.match(r"^ldr (r\d), \[pc", t)
        if pool is None and m:
            pool = (k, m.group(1))
    return save, pool


print("%-34s %s" % ("ROM", prosig(OM)))
exes = sorted(glob.glob("tools/mwccarm/**/mwccarm.exe", recursive=True))
for exe in exes:
    out = "build/try/ba14_cc.o"
    env = dict(os.environ, LM_LICENSE_FILE=LIC)
    r = subprocess.run([exe, "-c"] + FLAGS + ["-o", out, SRC],
                       capture_output=True, text=True, env=env)
    tag = exe.replace("tools/mwccarm/", "").replace("/mwccarm.exe", "")
    if r.returncode != 0:
        msg = (r.stdout + r.stderr).strip().split("\n")
        msg = [m for m in msg if m.strip()]
        print("%-34s FAIL %s" % (tag, msg[-1][:50] if msg else "?"))
        continue
    try:
        mine, mrel = text_relocs(out)
    except Exception as ex:
        print("%-34s READFAIL" % tag)
        continue
    if len(mine) != len(orig):
        print("%-34s SIZE %d" % (tag, len(mine)))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    nd = sum(1 for i in range(len(a)) if a[i] != b[i])
    mm = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(mine), 0)]
    star = "   <<< MATCH" if nd == 0 else ""
    print("%-34s bytes=%-3d sig=%s%s" % (tag, nd, prosig(mm), star))
