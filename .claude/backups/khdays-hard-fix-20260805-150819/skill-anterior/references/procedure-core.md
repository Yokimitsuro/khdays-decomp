# Procedure core

## Start or resume

```bash
python .claude/hooks/khdays_control.py status
```

If no active function exists, select exactly one:

```bash
python .claude/hooks/khdays_control.py select func_XXXXXXXX \
  --candidate build/try/func_XXXXXXXX.c \
  --mode detect \
  --frontier "<current port milestone>" \
  --reason "<verified call-flow evidence>"
```

## After each compiled experiment

```bash
python .claude/hooks/khdays_control.py set-candidate build/try/<best>.c
python .claude/hooks/khdays_control.py record \
  --diff "<exact instruction/register/stack/reloc residue>" \
  --next "<single next source-shape hypothesis>" \
  --experiments 1
```

## Match gate

```bash
python .claude/hooks/khdays_control.py verify
```

The script detects ARM/THUMB from `symbols.txt` when possible and tries both when uncertain. A
nonzero result means continue matching.

## Semantic gate

Initialize or inspect the receipt:

```bash
python .claude/hooks/khdays_control.py semantic-init
python .claude/hooks/khdays_control.py status
```

Record every Ghidra read-back and audit result using `semantic-mark`; see
`semantic-ghidra.md`. Then:

```bash
python .claude/hooks/khdays_control.py semantic-check
```

## Integrate

- relocs present -> `src/.../calls/<function>.c`;
- no relocs -> `src/.../auto/<function>.c`;
- remove any `asm_stubs/` twin;
- verify again in place.

```bash
python .claude/hooks/khdays_control.py integration-check
```

## Close the lock

```bash
python .claude/hooks/khdays_control.py complete
```

This reruns MATCH_GATE, validates SEMANTIC_GATE, validates integration, archives the completed state
and only then removes `build/active_function.json`.

## Staging sweep

Search recursively and inspect bodies:

```bash
for d in staging/*/; do
  find "$d" -name '*.c' 2>/dev/null
 done
```

Never use directory placement or `verify_idx` alone as proof that staged content is decompiled C.
Reject `asm`, `__asm`, `dcd` and instruction blobs.
