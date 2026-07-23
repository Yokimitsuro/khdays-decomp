#!/usr/bin/env python3
"""Thin wrapper: set LM_LICENSE_FILE and run mwccarm.

ninja can't reliably use `cmd /c set X=Y && ...` on Windows when paths
contain spaces, so we do the env-setting in Python.

Usage: _run_mwcc.py <out.o> <in.c>
"""
import json
import os
import subprocess
import time
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MWCCARM = ROOT / "tools" / "mwccarm" / "3.0_patch4" / "mwccarm.exe"
LICENSE = ROOT / "tools" / "mwccarm" / "license.dat"
FLAGS = [
    "-c", "-O4,p", "-proc", "arm946e", "-interworking",
    "-lang", "c99", "-enum", "int", "-char", "signed",
    "-inline", "on,noauto", "-Cpp_exceptions", "off", "-gccext,on",
]

# Path of this source file relative to the repo root — used for both the
# thumb/arm mode map and the per-file compiler override map.
out_path = Path(sys.argv[1])
src_path = Path(sys.argv[2])
rel = src_path.resolve().relative_to(ROOT).as_posix()

# Look up thumb/arm mode per-source-file from the sidecar map that
# gen_delinks.py produces.
modes_path = ROOT / "build" / "file_modes.json"
extra = []
if modes_path.exists():
    modes = json.loads(modes_path.read_text(encoding="utf-8"))
    if modes.get(rel) == "thumb":
        extra.append("-thumb")

# Per-file compiler override: a few translation units are precompiled middleware
# built with an older CodeWarrior (e.g. the ov028 anti-tamper crypto core, which
# only byte-matches under mwcc 1.2 sp4). configure.py writes build/file_compilers.json
# mapping such source files to a tools/mwccarm/<ver> directory.
mwcc_bin = MWCCARM
comp_path = ROOT / "build" / "file_compilers.json"
if comp_path.exists():
    cmap = json.loads(comp_path.read_text(encoding="utf-8"))
    ver = cmap.get(rel)
    if ver:
        mwcc_bin = ROOT / "tools" / "mwccarm" / ver / "mwccarm.exe"

env = dict(os.environ, LM_LICENSE_FILE=str(LICENSE))
cmd = [str(mwcc_bin), *FLAGS, *extra, "-o", str(out_path), str(src_path)]

# The FLEXlm license check fails intermittently under a parallel ninja build: a
# different, arbitrary translation unit dies on every full-tree run, and the exact
# same command succeeds when re-run on its own. Retry before believing a failure --
# a real diagnostic fails all four attempts and is then reported as usual.
for attempt in range(8):
    r = subprocess.run(cmd, env=env, capture_output=True, text=True)
    if r.returncode == 0:
        sys.stdout.write(r.stdout)
        sys.stderr.write(r.stderr)
        sys.exit(0)
    time.sleep(0.25 * (attempt + 1))

sys.stdout.write(r.stdout)
sys.stderr.write(r.stderr)
sys.exit(r.returncode)
