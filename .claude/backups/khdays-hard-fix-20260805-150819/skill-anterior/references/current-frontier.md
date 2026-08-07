# Current PC-port frontier

This file defines the stable ordering rules, not a stale exact candidate.

## Verified execution backbone

Confirm against the current tree before selecting work:

1. MAIN boot and runtime framework:
   `crt0 -> main -> BootTask -> object tick -> scene dispatcher`.
2. Scene 1 / `ov000`: boot, logo and first visible pixels.
3. Scene 7 / `ov006`: character select / Mission Mode, not the title screen.
4. Scene `0x13` / `ov008`: menu and configuration systems.
5. Scene 2 / `ov002`: gameplay bootstrap.
6. First playable story/tutorial slice discovered from the `ov002` constructor, initial states and
   transitions.
7. Continue through real runtime transitions, action/script dispatch, scene teardown and mission/day
   progression.

## Selection algorithm

Run only when there is no active-function lock:

1. Sweep `staging/` recursively and reject embedded assembly.
2. Verify whether staged real C advances the earliest reachable milestone.
3. Confirm the current milestone from the repository, call graph, `func_index.json`, scene ids,
   resource strings and runtime transitions.
4. Build a small dependency queue for that milestone.
5. Select its first unresolved function or direct dependency.
6. Create `build/active_function.json` immediately.
7. Do not recompute the frontier until that function passes all completion gates.

## Ordering inside a scene

Prefer, in this order:

1. constructor and initial state;
2. state dispatcher and transition conditions;
3. object/task framework required to tick;
4. resource loading required for the first visible frame;
5. input required for first interaction;
6. spawn and transforms;
7. camera;
8. collision and room/world loading;
9. HUD and essential rendering;
10. save/config state required by the path;
11. teardown and transition;
12. optional or currently unreachable branches.

This ordering chooses a function. It never authorizes leaving the selected function unmatched.

## How to update this file

Only record verified reachability facts and the current milestone. Do not append per-experiment
logs, near-match diaries, tie discussions or hundreds of historical `NEXT` entries. Git history and
`build/active_function.json` hold that information.
