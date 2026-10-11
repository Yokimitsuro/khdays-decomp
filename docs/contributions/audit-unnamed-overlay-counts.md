# Contribution classification: naming-audit overlay counts

**Contribution type: tooling fix (naming-audit reporting).**

This change fixes `tools/audit_unnamed.py` so its per-overlay summary uses
the resolved Ghidra address space instead of the old `func_ovNNN_...`
symbol prefix. It adds four regression tests.

The categories in CONTRIBUTING.md apply when contributing a function.
This contribution adds or changes no game function, so none of those
function categories applies:

| Function contribution category | Applies? |
| --- | --- |
| real C matched | No — no game C implementation is contributed. |
| non-matching C | No — no non-matching game implementation is contributed. |
| inline ASM placeholder | No — no assembly or placeholder is contributed. |
| SDK/library identification | No — no SDK or library function is identified. |
| symbol/name-only improvement | No — no function, data symbol, or struct field is renamed. |

CONTRIBUTING.md separately calls for tooling fixes to go in separate PRs,
one problem each, linked to the issue they fix. This branch addresses one
reporting problem.

## Validation

- Four regression tests pass; two fail against the original audit.
- Full tooling suite: 139 tests ran, 133 passed, six skipped because
  `build/func_index.json` is absent.
- `tools/gen_report.py`, `tools/audit_progress.py`, and `git diff --check` pass.

The tests use simulated Ghidra responses. The full ROM rebuild gate was
not run because the ROM and matching toolchain are unavailable.
No additional matched-function or C-decompilation progress is claimed.
