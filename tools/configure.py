#!/usr/bin/env python3
"""Generate build.ninja for the khdays decompilation.

Prototype scope: build ov000 (only module with a populated delinks.txt) using
`mwccarm` for our matched C files and the pre-delinked `.o` files from
`dsd delink` for the remaining gaps. Link everything into an ELF with
`mwldarm` using the `dsd lcf`-generated `build/arm9.lcf`.

Regenerate delinks.txt for ov000, run `dsd delink` + `dsd lcf`, and finally
emit build.ninja.
"""
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BUILD = ROOT / "build"
# objdiff.json expects `base_path` = build/<same relative src path>.o
COMPILE_OUT = BUILD
LINK = BUILD / "link"

MWCCARM = ROOT / "tools" / "mwccarm" / "3.0_patch4" / "mwccarm.exe"
MWLDARM = ROOT / "tools" / "mwccarm" / "2.0" / "sp2p4" / "mwldarm.exe"
LICENSE = ROOT / "tools" / "mwccarm" / "license.dat"
DSD = ROOT / "tools" / "dsd.exe"

CFLAGS = [
    "-c", "-O4,p", "-proc", "arm946e", "-interworking",
    "-lang", "c99", "-enum", "int", "-char", "signed",
    "-inline", "on,noauto", "-Cpp_exceptions", "off", "-gccext,on",
]

def discover_modules():
    """Every module that has a delinks.txt and at least one matched
    source file. Multi-module builds are byte-exact after tightening the
    LCF alignment from 4 down to 2 (see tools/_run_mwld.py) — mwld's
    default ALIGNALL(4) was inserting padding at every THUMB function
    at a 2-aligned offset."""
    modules = []
    cfg_root = ROOT / "config" / "arm9"
    for name in ("", "itcm", "dtcm"):
        d = cfg_root / name if name else cfg_root
        if (d / "delinks.txt").exists():
            modules.append(d)
    ov_cfg = cfg_root / "overlays"
    ov_src = ROOT / "src" / "overlays"
    if ov_cfg.is_dir():
        for ov_dir in sorted(ov_cfg.iterdir()):
            if not (ov_dir / "delinks.txt").exists():
                continue
            src_ov = ov_src / ov_dir.name
            if not src_ov.exists():
                continue
            has_c = any(
                p.is_file()
                for sub in ("auto", "calls", "asm_stubs/auto", "asm_stubs/calls")
                for p in (src_ov / sub).glob("*.c") if (src_ov / sub).exists()
            )
            if has_c:
                modules.append(ov_dir)
    return modules


MODULES = discover_modules()


def files_from_delinks(delinks_txt: Path):
    """Return the list of source-file paths declared in delinks.txt FILES."""
    out = []
    for line in delinks_txt.read_text(encoding="utf-8").splitlines():
        if line.endswith(":") and "/" in line and not line.startswith(" "):
            out.append(line[:-1])
    return out


def stage_delinked_objects(link_dir: Path):
    """Copy every `.o` from build/delinks/ into build/link/ with a flat name.

    dsd lcf references bare object names (no path), so mwldarm needs to find
    them via -L. Flattening avoids per-file -L flags.
    """
    for src in (BUILD / "delinks").rglob("*.o"):
        dst = link_dir / src.name
        if dst.exists() and dst.stat().st_mtime >= src.stat().st_mtime:
            continue
        shutil.copyfile(src, dst)


def rel(p):
    """Path relative to ROOT, posix, ninja-safe."""
    return Path(p).resolve().relative_to(ROOT).as_posix()


def emit_ninja(ninja_path: Path, src_files):
    """Write build.ninja with compile + link rules for the prototype scope.

    All paths are relative to ROOT so ninja (invoked from ROOT) doesn't have
    to escape the space in the project directory name.
    """
    py = sys.executable.replace("\\", "/")
    lines = [
        "ninja_required_version = 1.10",
        "",
        f"python = {py}",
        "",
        "rule mwcc",
        # file_modes.json flips a file between ARM and THUMB — recompile when it
        # changes so an old .o built without -thumb doesn't shadow the correct
        # THUMB output.
        "  command = $python tools/_run_mwcc.py $out $in",
        "  description = MWCC $in",
        "  restat = 1",
        "",
        "rule mwld",
        "  command = $python tools/_run_mwld.py $out $lcf $out.rsp",
        "  description = MWLD $out",
        "  rspfile = $out.rsp",
        "  rspfile_content = $rspcontent",
        "",
    ]

    compiled_objs = []
    modes_dep = rel(BUILD / "file_modes.json")
    compilers_dep = rel(BUILD / "file_compilers.json")
    for src in src_files:
        # Match objdiff.json's expected base_path layout.
        obj_path = COMPILE_OUT / Path(src).with_suffix(".o")
        obj_path.parent.mkdir(parents=True, exist_ok=True)
        obj = rel(obj_path)
        compiled_objs.append(obj)
        # Implicit deps on file_modes.json (arm <-> thumb flips) and
        # file_compilers.json (per-file compiler-version overrides) so either
        # change invalidates any cached .o for this file.
        lines.append(f"build {obj}: mwcc {src} | {modes_dep} {compilers_dep}")

    lines.append("")
    lines.append("build compile: phony " + " ".join(compiled_objs))
    lines.append("")

    # Optional full-ROM link target. Inputs: our compiled .o + every
    # delinked .o staged under build/link/. Ordering follows twewy's setup
    # (one flat @rsp file, LCF handles the layout).
    all_link_inputs = list(compiled_objs)
    compiled_set = set(compiled_objs)
    for p in sorted(LINK.glob("*.o")):
        rp = rel(p)
        if rp not in compiled_set:
            all_link_inputs.append(rp)

    lcf = rel(BUILD / "arm9.lcf")
    # mwldarm resolves the LCF's `> build/arm9.bin` output redirects relative
    # to the ELF output directory. Placing the ELF at build/arm9.elf makes
    # the raw binaries land at build/build/*.bin — matching dsd's
    # config.yaml (`object: ../../build/build/arm9_ov000.bin`).
    elf_out = rel(BUILD / "arm9.elf")
    rspcontent = " ".join(all_link_inputs)
    joined_deps = " ".join(compiled_objs)
    lines.append(f"build {elf_out}: mwld {joined_deps} | {lcf}")
    lines.append(f"  lcf = {lcf}")
    lines.append(f"  rspcontent = {rspcontent}")
    lines.append("")
    lines.append("default compile")
    lines.append("")

    ninja_path.write_text("\n".join(lines), encoding="utf-8", newline="\n")


def run(*cmd, cwd=None):
    r = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True)
    if r.returncode != 0:
        print(r.stdout)
        print(r.stderr, file=sys.stderr)
        raise SystemExit(f"failed: {' '.join(str(c) for c in cmd)}")
    return r


def main():
    LINK.mkdir(parents=True, exist_ok=True)
    (BUILD / "build").mkdir(parents=True, exist_ok=True)

    # Publish the checked-in per-file compiler-override map (a few precompiled
    # middleware TUs, e.g. the ov028 crypto core, build with an older mwcc) to
    # build/ where _run_mwcc.py reads it. Always write it (empty {} if absent)
    # so the ninja implicit dep resolves.
    src_compilers = ROOT / "config" / "arm9" / "file_compilers.json"
    compilers_text = src_compilers.read_text(encoding="utf-8") if src_compilers.exists() else "{}\n"
    (BUILD / "file_compilers.json").write_text(compilers_text, encoding="utf-8", newline="\n")

    for module_dir in MODULES:
        rel = module_dir.relative_to(ROOT)
        print(f"[configure] regen delinks.txt for {rel}")
        run(sys.executable, str(ROOT / "tools" / "gen_delinks.py"), str(module_dir))

    print("[configure] dsd delink")
    run(str(DSD), "delink", "--config-path",
        str(ROOT / "config" / "arm9" / "config.yaml"))
    print("[configure] dsd lcf")
    run(str(DSD), "lcf", "--config-path",
        str(ROOT / "config" / "arm9" / "config.yaml"))

    print("[configure] stage delinked .o files into build/link/")
    stage_delinked_objects(LINK)

    src_files = []
    for module_dir in MODULES:
        src_files.extend(files_from_delinks(module_dir / "delinks.txt"))
    # De-dup: same source file could theoretically appear from two module
    # scans (shouldn't with our layout, but be safe).
    src_files = sorted(set(src_files))
    print(f"[configure] {len(src_files)} matched source files to compile")

    emit_ninja(ROOT / "build.ninja", src_files)
    print("[configure] wrote build.ninja")


if __name__ == "__main__":
    main()
