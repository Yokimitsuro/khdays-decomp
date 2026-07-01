#!/usr/bin/env python3
"""Thin wrapper: set LM_LICENSE_FILE and run mwccarm.

ninja can't reliably use `cmd /c set X=Y && ...` on Windows when paths
contain spaces, so we do the env-setting in Python.

Usage: _run_mwcc.py <out.o> <in.c>
"""
import json
import os
import subprocess
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

# Look up thumb/arm mode per-source-file from the sidecar map that
# gen_delinks.py produces.
out_path = Path(sys.argv[1])
src_path = Path(sys.argv[2])
modes_path = ROOT / "build" / "file_modes.json"
extra = []
if modes_path.exists():
    modes = json.loads(modes_path.read_text(encoding="utf-8"))
    rel = src_path.resolve().relative_to(ROOT).as_posix()
    if modes.get(rel) == "thumb":
        extra.append("-thumb")

env = dict(os.environ, LM_LICENSE_FILE=str(LICENSE))
sys.exit(subprocess.run(
    [str(MWCCARM), *FLAGS, *extra, "-o", str(out_path), str(src_path)], env=env
).returncode)
