# Toolchain and gates

## Compiler

```text
mwccarm 3.0 build 139 (patched license)
-O4,p -proc arm946e -interworking -lang c99 -enum int -char signed
-inline on,noauto -Cpp_exceptions off -gccext,on
```

The user has confirmed the compiler/toolchain. Do not use “wrong compiler” as an ordinary exit from
an assigned function.

## Per-function verification

```bash
python tools/verify_idx.py <candidate.c> <function>
python tools/verify_idx.py <candidate.c> <function> --thumb
```

Prefer the wrapper:

```bash
python .claude/hooks/khdays_control.py verify
```

## Full 306 gate

Run before push, using the default Ninja target rather than the mono `arm9.elf` target:

```bash
cp dsd_extract/arm9/{arm9,itcm,dtcm}.bin build/build/
for f in dsd_extract/arm9_overlays/ov*.bin; do
  b=$(basename "$f" .bin)
  cp "$f" "build/build/arm9_$b.bin"
done
python tools/configure.py && ninja
tools/dsd.exe check modules --config-path config/arm9/config.yaml -f
```

Required result:

```text
DSD_OK=306 FAILED=0
```

## Git cadence

Commit locally after each completed function or coherent batch. Before pushing:

```bash
git log -1 --format=%cr origin/main
```

Push at most once per hour and only after a fresh 306/0 gate. Never add a
`Co-Authored-By: Claude` trailer. Do not stage `build/` or generated delink noise.
