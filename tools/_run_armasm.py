#!/usr/bin/env python3
"""Assemble one checked-in ARM source for the Ninja build."""

from __future__ import annotations

import shutil
import subprocess
import sys
from pathlib import Path


def find_assembler() -> str:
    configured = shutil.which("arm-none-eabi-as")
    if configured:
        return configured
    candidates = sorted(Path("C:/Program Files (x86)").glob(
        "Arm GNU Toolchain arm-none-eabi/*/bin/arm-none-eabi-as.exe"
    ))
    if not candidates:
        raise SystemExit("arm-none-eabi-as was not found")
    return str(candidates[0])


def main() -> None:
    if len(sys.argv) != 3:
        raise SystemExit("usage: _run_armasm.py <out.o> <source.s>")
    output = Path(sys.argv[1])
    source = Path(sys.argv[2])
    output.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run([
        find_assembler(), "-mcpu=arm946e-s", "-o", str(output), str(source),
    ], check=True)


if __name__ == "__main__":
    main()
