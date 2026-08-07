# Current state — authoritative rules

This file is intentionally short. It is not an experiment diary.

## Runtime source of truth

The only authoritative active-function state is:

```text
build/active_function.json
```

Read it through:

```bash
python .claude/hooks/khdays_control.py status
```

If the file exists, do not infer another active function from old notes, `staging/`,
`nonmatching/`, commit history, or any `NEXT` line.

If it does not exist, confirm the actual repository state and choose exactly one function from the
current port frontier. Create the lock immediately with `khdays_control.py select`.

## Migration note

The previous `state.md` and `port-play-order.md` accumulated multiple overlapping sessions and
conflicting `NEXT`, `held`, `blocked`, and in-progress entries. They are preserved under
`references/history/` only for targeted searches. They are not current state.

At migration time, do not guess which of the historical candidates is active. Inspect:

1. `build/active_function.json`;
2. existing candidates in `build/try/`;
3. integrated real C in `calls/` and `auto/`;
4. current `staging/`;
5. callers, callees, scene flow and the latest repository commits.

## Fields that must remain current

The lock records:

- active function;
- ARM/THUMB mode;
- best candidate path;
- selected port milestone;
- selection evidence;
- current exact residue;
- next single hypothesis;
- experiment count.

Update it after every meaningful compiled experiment with `khdays_control.py record`.
