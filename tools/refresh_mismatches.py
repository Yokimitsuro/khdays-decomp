#!/usr/bin/env python3
"""Compile every matched .c and record which ones don't reproduce the
delinked baseline byte-for-byte. The output list is what gen_delinks.py uses
to keep faulty decomps out of the link (dsd emits their gap bytes instead,
so the built module stays byte-exact against the ROM).

Usage:  python tools/refresh_mismatches.py

Writes: build/known_mismatches.txt (one path per line, relative to ROOT).
"""
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import audit_progress  # noqa: E402
import diff_objs  # noqa: E402


def matched_c_files():
    """Every .c file we currently consider a real C decomp (not asm-stub)."""
    for src_dir in audit_progress.SRC_DIRS:
        if not src_dir.exists():
            continue
        # skip src/asm_stubs and libs/*/asm_stubs subtrees
        if "asm_stubs" in src_dir.parts:
            continue
        for p in sorted(src_dir.glob("*.c")):
            if audit_progress.source_category(p) == "c_decompiled_matched":
                yield p


def main():
    # Pass 1: regenerate delinks with EVERY matched file included, so dsd
    # produces a per-file delink baseline for candidates that would normally
    # be excluded. This is the only way to diff them.
    print("== refresh_mismatches: pass 1 (no exclusion) ==")
    env = dict(**dict(**{k: v for k, v in __import__('os').environ.items()}),
               KHDAYS_NO_EXCLUDE="1")
    r = subprocess.run(
        [sys.executable, "tools/configure.py"], cwd=str(ROOT), env=env,
    )
    if r.returncode != 0:
        raise SystemExit("pass-1 configure failed")
    r = subprocess.run(["ninja", "compile"], cwd=str(ROOT), env=env)
    if r.returncode != 0:
        raise SystemExit("pass-1 compile failed")

    mismatches = []
    for c_path in matched_c_files():
        rel_c = c_path.relative_to(ROOT).as_posix()
        # Compiled output layout matches base_path in objdiff.json:
        # build/<same relative path as .c>.o
        compiled = ROOT / "build" / c_path.relative_to(ROOT).with_suffix(".o")
        delinked = ROOT / "build" / "delinks" / c_path.relative_to(ROOT).with_suffix(".o")
        if not compiled.exists() or not delinked.exists():
            continue
        ok, msg = diff_objs.compare(compiled, delinked)
        if not ok:
            mismatches.append((rel_c, msg))

    out = ROOT / "build" / "known_mismatches.txt"
    out.parent.mkdir(exist_ok=True)
    out.write_text(
        "\n".join(path for path, _msg in sorted(mismatches)) + "\n",
        encoding="utf-8",
        newline="\n",
    )
    print(f"wrote {out.relative_to(ROOT)}  ({len(mismatches)} mismatches)")
    for path, msg in mismatches[:15]:
        print(f"  {path}  ({msg})")
    if len(mismatches) > 15:
        print(f"  ... and {len(mismatches) - 15} more")

    # Pass 2: reconfigure using the fresh exclusion list so the next ninja
    # build produces a byte-exact ROM again.
    print("== refresh_mismatches: pass 2 (with exclusion) ==")
    r = subprocess.run([sys.executable, "tools/configure.py"], cwd=str(ROOT))
    if r.returncode != 0:
        raise SystemExit("pass-2 configure failed")


if __name__ == "__main__":
    main()
