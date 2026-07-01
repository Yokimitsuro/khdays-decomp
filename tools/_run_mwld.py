#!/usr/bin/env python3
"""Thin wrapper: set LM_LICENSE_FILE and run mwldarm.

Usage: _run_mwld.py <out.elf> <lcf> <rspfile>
The rspfile contains the newline- or space-separated list of .o inputs.
"""
import os
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MWLDARM = ROOT / "tools" / "mwccarm" / "2.0" / "sp2p4" / "mwldarm.exe"
LICENSE = ROOT / "tools" / "mwccarm" / "license.dat"

out_elf = sys.argv[1]
lcf = sys.argv[2]
rsp = sys.argv[3]

# dsd's canonical objects list (produced by `dsd json delinks` -> written to
# build/objects.txt) picks the right file per address: build/src/*.o for our
# compiled matched functions, build/delinks/*.o for the gaps. Using it here
# instead of a glob avoids double-defining symbols.
canonical = ROOT / "build" / "objects.txt"
if canonical.exists():
    raw = [ln.strip() for ln in canonical.read_text().splitlines() if ln.strip()]
else:
    raw = Path(rsp).read_text().split()

# The @rsp path splitter in mwldarm breaks on spaces even inside quoted paths,
# and the project lives under a directory that contains a space
# ("E:\KH 3582\decomp"). Rewrite absolute paths to be relative to ROOT and
# rewrite the rsp file. From ROOT (cwd when ninja invokes us) the relative
# paths themselves contain no spaces.
objs_rel = []
for p in raw:
    pp = Path(p)
    try:
        objs_rel.append(pp.resolve().relative_to(ROOT).as_posix())
    except ValueError:
        objs_rel.append(p)
Path(rsp).write_text("\n".join(objs_rel) + "\n", encoding="utf-8", newline="\n")

# Patch the LCF: mwld's `ALIGNALL(4)` inside every SECTIONS block forces
# each input .o's .text to a 4-byte boundary. That aligns THUMB functions
# at 2-aligned offsets to 4, inserting 2 bytes of padding at every such
# boundary and cascading pointer/BL offsets throughout the module. Reduce
# to `ALIGNALL(2)` — THUMB minimum — which preserves the original layout
# byte-for-byte.
lcf_text = Path(lcf).read_text(encoding="utf-8")
if "ALIGNALL(4);" in lcf_text:
    Path(lcf).write_text(
        lcf_text.replace("ALIGNALL(4);", "ALIGNALL(2);"),
        encoding="utf-8",
        newline="\n",
    )

# Belt-and-suspenders: also lower per-.o sh_addralign so a future mwld
# refactor that consults the input alignment doesn't reintroduce the drift.
patch_script = ROOT / "tools" / "patch_align.py"
subprocess.run([sys.executable, str(patch_script)], check=True)

env = dict(os.environ, LM_LICENSE_FILE=str(LICENSE))
# Flags mirrored from Yotona/twewy/tools/configure.py — the only DS decomp
# using dsd that actually links a full ROM. -nodead disables dead-code
# elimination (would clobber overlay code with no incoming refs);
# -nostdlib avoids MSL / library pull-in that we don't have set up.
cmd = [
    str(MWLDARM),
    "-proc", "arm946e",
    "-interworking",
    "-map", "closure,unused",
    "-msgstyle", "gcc",
    "-nodead",
    "-nostdlib",
    "-m", "Entry",
    "-o", out_elf,
    lcf,
    f"@{rsp}",
]
sys.exit(subprocess.run(cmd, env=env, cwd=str(ROOT)).returncode)
