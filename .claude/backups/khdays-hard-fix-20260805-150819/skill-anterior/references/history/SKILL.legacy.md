---
name: khdays-decomp
description: >
  Standing procedure + codegen-crack catalog + shape-family map for the byte-exact
  MATCHING DECOMPILATION of Kingdom Hearts 358/2 Days (Nintendo DS, EU YKGP) at
  E:\KH 3582\decomp. Load this at the START of ANY khdays / "KH 358/2 Days" / days.nds
  decomp work — matching a function to byte-exact C, shape-family harvest, the
  verify_idx / dsd-306 build gate, mwccarm 3.0/139 codegen steering (bitfields,
  division-by-constant, conditional block layout, register/declaration order,
  offset splitting, 64-bit fields), the do-NOT-retry tie list, and the commit /
  hourly-push / progress-regen cadence. Use whenever the user says "continua con
  el decomp", asks to carve/match/verify a func_ovNNN_ADDR, run a family scan, or
  work anywhere under E:\KH 3582\decomp — even if they never say the word "skill".
  This is the living reference: append every new crack/family/tie you discover to
  the relevant references/ file.
---

# khdays-decomp — matching decompilation of KH 358/2 Days

Matching decompilation of **Kingdom Hearts 358/2 Days** (NDS, EU `YKGP`). Goal:
byte-exact C that recompiles (mwccarm 3.0/139) to the original machine code.
This skill is the single standing reference — it folds together what used to live
in `DECOMP_WORKFLOW.md`, `CLAUDE.md`, and a dozen memory files. **When you learn a
new crack, family, or tie, append it to the matching `references/` file** so the
next session inherits it.

Bigger goal beyond byte-exact: **human-readable code for an eventual PC port.**
Give genuinely good names in Ghidra (functions, params, locals, struct fields)
grounded in real understanding. The C symbol must stay `func_ovNNN_ADDR` (for
delinking) but Ghidra gets the meaningful names. A match with no semantic layer is
"half done" and does not count (hard user rule).

⚠ **"struct fields" in that sentence was ignored for the entire project.** On 2026-07-20 the user
asked "¿estás haciendo structs?" and the answer was no — **Ghidra contained zero user data types.**
See the STRUCTS rule below; it is not optional and it is not a later phase.

## ★★★ Explicit user-assigned function mode — highest priority

When the user explicitly names a function and asks to match it, that function enters
**assigned-function mode**.

This mode overrides every general instruction elsewhere in this skill about:

- parking;
- moving to `nonmatching/`;
- consulting the do-NOT-retry list as a stopping condition;
- abandoning a compiler-tie shape;
- moving to another candidate;
- continuing a family harvest;
- maximizing the number of functions processed.

For an explicitly assigned function, the task is complete only when:

1. `tools/verify_idx.py` reports a byte-exact match in the correct ARM/THUMB mode;
2. target and generated sizes match;
3. instructions and relocations match;
4. the matching source is ready to be wired into `auto/` or `calls/`.

The following are **not** successful outcomes for an explicitly assigned function:

- placing it in `nonmatching/`;
- marking it as parked;
- writing a park note;
- declaring a register-allocation tie;
- declaring a compiler tie without exhaustive evidence;
- returning equivalent but unmatched C;
- switching to another function;
- continuing the family/batch workflow.

Do not optimize for closing, classifying, or clearing the worklist. Optimize
exclusively for obtaining the byte-exact match of the assigned function.

`nonmatching/` is permitted only for unassigned batch candidates, or when the user
explicitly authorizes parking the currently assigned function.

If the assigned function does not match, keep experiments in `build/try/` and
continue the local:

```text
edit -> compile -> verify -> inspect diff -> form hypothesis -> repeat
```

Do not ask the user to compile experiments manually when the local MWCC toolchain
and `verify_idx.py` are available.

Do not stop merely because:

- the percentage is unchanged;
- several variants produce the same assembly;
- only registers differ;
- only scheduling differs;
- only stack offsets differ;
- the function resembles an entry in `deferred-ties.md`;
- Ghidra produced plausible pseudocode;
- the C is semantically equivalent;
- progress temporarily stalls.

A `deferred-ties.md` match is a hypothesis to challenge, never permission to stop
an explicitly assigned function.

Before reporting a genuine blocker, perform and record at least 30 distinct compiled
experiments covering every relevant axis:

- caller return type;
- callee arity;
- argument and return types;
- function-pointer prototypes;
- struct shape and aliasing;
- signedness and integer width;
- local declaration order;
- stack-object order, size and alignment;
- temporary lifetime;
- parameter reuse;
- direct field access versus aliases;
- `register` and justified `volatile`;
- branch orientation and shared tails;
- expression grouping and evaluation order;
- struct copy versus field assignments;
- ARM versus THUMB;
- literal-pool and relocation structure;
- matching forms already present in the repository.

“Could not make it match” and “likely compiler noise” are not blockers.

A blocker report must identify a concrete missing external requirement, such as:

- unavailable target bytes;
- unavailable relocations;
- unavailable exact compiler;
- demonstrably unknown compiler flags;
- missing binary section;
- an infrastructure disagreement between `verify_idx.py` and the full build gate.

When blocked, do not move or classify the function. Leave the best source in
`build/try/`, report the evidence, and wait for the user’s decision.


## ★★★ Port-first play-order mode — default for autonomous work

When the user asks for an autonomous decompilation loop without naming one exact
function, enter **port-first play-order mode**.

The purpose of this mode is not to maximize the number of matched functions. Its
purpose is to advance the earliest playable vertical slice of the future PC port,
starting at boot and following the order in which code becomes reachable during a
normal playthrough.

Read both files before choosing work:

1. `references/game-flow.md` — verified runtime and scene-flow facts.
2. `references/port-play-order.md` — the living port frontier and current queue.

The prompt does not need to repeat the struct rule, the no-park rule, Ghidra usage,
verification, staging inspection, or the edit/compile/verify loop. They are
mandatory in this skill.

### Selection authority

Selection priority is:

1. A function explicitly named by the user.
2. A module explicitly named by the user.
3. A verified real-C handoff in `staging/` that advances the current port frontier.
4. The earliest unresolved function on the current play-order frontier.
5. A direct dependency required by that function.
6. The teardown or transition needed to reach the next gameplay milestone.
7. Other functions in the same currently reachable scene.
8. Later scenes and unrelated shape families.

Once a function is selected through this queue, treat it exactly like an explicitly
assigned function: assigned-function mode applies until byte-exact MATCH. Do not
park it, move it to `nonmatching/`, classify it, or switch to another function.

**Overlay number, address order, size, relocation count, and expected matching yield
are not play order.** Do not choose work merely because it is easy, reloc-free, part
of a large family, or numerically close to the current overlay.

### Existing `nonmatching/` files

Existing `nonmatching/` files are historical candidates, not the global work queue.

Do not start by processing every `nonmatching/` file indiscriminately. Many belong
to late-game systems, optional modes, middleware, or scenes the port cannot reach
yet.

When the earliest unresolved play-order function already has a `nonmatching/` copy:

- use its best source as the initial candidate;
- distrust the old park explanation;
- run the current arity, return-type, mode, struct, array-shape, literal-pool and
  infrastructure checks again;
- keep new experiments only in `build/try/`;
- delete the old `nonmatching/` copy only after a verified replacement is integrated.

### Port-frontier algorithm

At the beginning of every autonomous iteration:

1. Sweep `staging/` recursively.
2. Reject staged files containing `asm`, `dcd`, inline instruction blobs, or any
   other disguised assembly.
3. Verify staged real C in both the correct mode and the fallback mode when needed.
4. Integrate verified staging work that advances the earliest current milestone.
5. Read the current frontier from `references/port-play-order.md`.
6. Confirm it against the current tree, Ghidra, `func_index.json`, scene transitions,
   callers and callees.
7. Identify the earliest milestone that is not yet backed by sufficient real C.
8. Build a small dependency queue for that milestone.
9. Select the first unresolved function from that queue.
10. Keep matching that function until byte-exact.
11. Update the play-order reference with verified facts and the newly exposed next
    frontier.

Do not treat a stale status line in a reference file as ground truth. Verify current
repository state before selecting or reporting work.

### Vertical-slice ordering inside a scene

Within the current scene or gameplay milestone, prefer this order:

1. scene/task constructor and initial state;
2. state dispatcher and transition conditions;
3. object/class framework required to tick the state;
4. resource and archive loading required for the first visible frame;
5. input required for the first user interaction;
6. player/object spawn and transforms;
7. camera;
8. collision and room/world loading;
9. HUD and essential rendering;
10. save/config state required by the path;
11. teardown and transition to the next scene;
12. optional branches, secondary effects and unreachable alternatives.

This is a priority order, not permission to leave a selected function unmatched.

### Platform-replaced Nintendo DS code

The PC port will replace some hardware-specific code. Mark a function as
**platform-replaced** in `references/port-play-order.md` only when runtime evidence
shows that it is pure DS platform bring-up or direct hardware plumbing and no game
semantics are hidden inside it.

Platform-replaced code may be skipped for port-frontier purposes, but do not invent
a replacement classification from an address range or overlay name. `ov001` boot
hardware initialization is the established example.

### Living roadmap updates

After every integrated match that changes reachability or understanding, update
`references/port-play-order.md`:

- current milestone;
- newly matched function;
- whether it is port-required, port-helpful, or platform-replaced;
- direct dependencies still unresolved;
- next exact function;
- evidence for the ordering;
- any newly discovered scene or state transition.

Put verified flow facts in `references/game-flow.md`. Put scheduling and frontier
state in `references/port-play-order.md`. Do not turn either file into an experiment
diary.

### Initial verified play-order backbone

Use the current tree to confirm status, but the known backbone is:

1. MAIN boot and runtime framework:
   `crt0 -> main -> BootTask -> object tick -> scene dispatcher`.
2. Scene 1, `ov000`: boot/logo and first visible pixels.
3. Scene 7, `ov006`: title.
4. Scene 19 (`0x13`), `ov008`: main menu and configuration.
5. Scene 2, `ov002`: gameplay bootstrap.
6. First playable story/tutorial slice discovered from the `ov002` constructor,
   initial states and transitions.
7. Continue by actual runtime transitions and mission/day progression, not by
   overlay number.

The currently documented gameplay-frontier entry is
`func_ov002_020679d4`, but always verify whether an earlier unresolved boot,
logo, title or menu dependency remains before selecting it.


## Donde va cada cosa que escribes (2026-07-19, corregido por el usuario)

- **`dudas.md` = dudas PARA EL USUARIO.** Preguntas abiertas y decisiones que tomaste solo y que
  el habria querido opinar. Formato **duda -> que hice -> por que**. Es corto por diseño.
  ⚠ **NO es un diario de trabajo.** En una sesion autonoma lo convertí en 4.197 lineas con 93
  entradas "Iteracion NNN" y hubo que reescribirlo entero. Si lo que vas a escribir no es una
  pregunta ni una decision discutible, **no va ahi**.
- **Hallazgos tecnicos** (cracks, empates, familias, estado, herramientas) -> `references/*.md`.
- **Que se hizo y cuando** -> el log de git. No lo dupliques en prosa.

⚠ **El skill esta gitignored: NO se pushea y NO se menciona en los mensajes de commit.**
(2026-07-20, corregido por el usuario.) Actualizarlo no genera nada que subir, asi que no hay
que hacer commit por ello ni escribir "written up in codegen-cracks.md" / "SKILL.md updated" en
un mensaje: quien lea el repo no puede abrir esos ficheros y solo le sobra texto. **El crack o la
leccion, si merece la pena contarla, se cuenta ENTERA en el mensaje de commit o en el comentario
del `.c`** -- que es lo que si viaja con el repo. La referencia interna se queda en local.

## Todo lo que se SUBE al repo va en INGLES

Regla del usuario (2026-07-19). El chat es en español, **el repo es en inglés**: los `.md`
que se suben, los comentarios de los `.c` (incluidas las notas de `nonmatching/`), los
nombres de símbolo y los identificadores. El único sitio donde el español es correcto es
este skill (que está gitignored) y los mensajes de commit.

⚠ Es fácil incumplirlo sin darse cuenta al *reescribir* un fichero: la nota de
`ov029_020b2ee0` estaba en inglés, la reescribí entera en español al mejorarla y hubo que
rehacerla. **Antes de reescribir una cabecera existente, mira en qué idioma estaba.**

## Nada de `build/` se sube

`build/try/` es el scratch donde escribes los `.c` candidatos antes de verificarlos, y
`build/sweep/` son barridos intermedios. Los dos estan en `.gitignore` desde el 2026-07-19,
despues de que `git add -A` colara **3.393 ficheros** al repo. Si añades una carpeta de trabajo
nueva bajo `build/`, ignórala en el mismo commit.

## Hard rules (never violate)

- **Ghidra FIRST for every decomp**, and keep its symbols renamed in sync with the C.
  If Ghidra is genuinely unreachable, **don't stop and don't wait** — the ground truth is
  `func_index.json` + capstone, not the decompiler (see below). Keep matching, and **write the
  naming scripts to `~/ghidra_scripts/` as you go** so nothing is lost; run them the moment it is
  back, then read the renames back. That is how 27 renames survived a mid-session freeze on
  2026-07-17.
  ⚠ **An unnamed match is a debt, and "I'll track it" does not work** — six rescues were committed
  unnamed on 2026-07-17 *an hour after* that sentence was written into this file. **Name in the
  same batch as the match**, and run `python tools/audit_unnamed.py` at the end of every session.
  It is at **50%** project-wide, so the debt is real and it is invisible unless you count it.
- ★★★ **USE STRUCTS IN EVERY MODE, EVEN WHEN THE PROMPT DOES NOT REPEAT IT. When you decode an object layout, create the Ghidra type IN THE SAME BATCH**
  — exactly like naming. A layout that only exists in a comment or in `references/` does not count;
  the port cannot consume prose.
  **Why this is a hard rule (2026-07-20):** the project ran to 13k matched functions with **zero
  user data types in Ghidra**, while the C tree accumulated **~4,000 per-file ad-hoc declarations**
  — `struct hw60` copy-pasted into 645 files, and `struct Obj` (460) / `struct A` (390) /
  `struct S` (285) each describing **the same object with a different shape and name per file**.
  That is worse than having none, because every one of them looks authoritative.
  This is not a defect of the matching work: byte-exactness forces self-contained `.c` files,
  delinking rules out shared headers, and the struct there is a **codegen tool** (force a
  `ldrh`+shift pair, pick a base register), not a data model.
  **So the fix is Ghidra types, never C headers** — Ghidra types cannot perturb codegen or the 306
  gate, and they pay off in every decompilation that touches the object:
  `*(undefined2 *)(iVar2 + 0x22)` becomes `iVar2->wLocalPlayerIndex`.
  Three traps, all hit on the first attempt — details in `references/naming-hubs.md`:
  1. **Every type tool leaks a transaction and returns an `endTransaction` error WHILE SUCCEEDING**
     (`create_struct`, `apply_data_type`, `set_function_prototype`, `set_local_variable_type`).
     Read the result back, and finish with `CloseTxAndSave.py` or `save_program` fails
     ("Unable to lock due to active transaction") and the whole batch is lost. One batch left 13.
  2. ★★★ **TO TYPE A GLOBAL, TYPE THE POOL SLOT AS `T *` — that is the whole recipe.**
     `apply_data_type(<pool addr>, "CardTransferCtx *")`, where the pool address is the
     `ldr rX,[pc,#N]` target inside the function's own literal pool (e.g. `arm9_ov008::0208bea8`),
     NOT the `.bss` address of the object and NOT the consumer's local. The decompiler binds the
     local to the pool datum, so typing the slot propagates everywhere:
     `*(int *)(DAT + 4)` / `*pbVar1` / `pbVar1[1]` becomes
     `PTR_DAT->nResultCode` / `pCVar1->bBlockCounter` / `pCVar1->bSlot`.
     ⚠ Earlier drafts of this file said the opposite — "type the local variable instead" and
     "typing the pool slot is not typing the object". **Both were wrong**; `set_local_variable_type`
     answers *"Unable to use type for symbol"* precisely because the local is bound to an untyped
     pool datum. Corrected 2026-07-20 after it actually worked.
     ⚠⚠ **GET THE POINTER DEPTH RIGHT — one level short is plausible and wrong.** Ask whether the
     global *is* the object or *holds a pointer to* it; the C answers it: `data_x[0]` means it is
     the object (slot = `T *`), `*(int *)&data_x` means it holds a pointer (slot = `T **`).
     Typed one short, `data_0204c228` decompiled as `PTR_PTR->dwState` — reading the state field
     at the address where the *pointer* lives. It looks like a real field access, which is exactly
     why it would have survived review. Correct output is `*PTR_PTR` then `->wLocalPlayerIndex`.
     **`python tools/poolslots.py <symbol>` enumerates every slot for a global** from the reloc
     table (a reloc to `data_X` at offset N of function F means F+N is a slot), so one script types
     them all: 43 slots across 5 globals in one pass, and `data_0204be18` alone has **170**.
     ⚠ **Jython has a 64K method limit and lies about hitting it.** 2271 inline tuples produced
     `RuntimeException: Module or method too large` — *while the tool reported
     `SCRIPT COMPLETED SUCCESSFULLY` and `success: true`*. **Read the console output, never the
     status.** Fix: write the data to a sidecar `.txt` next to the script and read it with
     `open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'x.txt'))`; the script drops
     from 68 KB to 2 KB and runs fine.
  2b. **`.bss` blocks ship UNINITIALIZED, so their addresses have no bytes** and nothing can be
     attached to them directly. `~/ghidra_scripts/InitBssBlocks.py` converts every `*.bss` block to
     zero-filled initialised (106 blocks, 124 KB, ROM/build/gate untouched — BSS *is* zero at
     runtime, and it is reversible). Do this once per program; it makes the globals readable and
     inspectable. ⚠ **It is NOT what unblocks the struct typing** — the pool-slot recipe above is.
     Worth doing anyway, and worth not confusing the two.
  3. **Overlay globals live in a SEPARATE address space**: `arm9_ov008.bss::02090fb4`, not
     `arm9_ov008::02090fb4`. Using the wrong one answers "Address is not in program memory", which
     reads exactly like "this cannot be typed". Check `list_segments` before concluding anything.
  ★★ **COUNT IT: `python tools/audit_struct_sync.py`.** Within hours of writing this rule I typed
  three functions' C and skipped the Ghidra half on all three — the exact failure the naming debt
  had, so it gets the exact same fix. A struct is real only when BOTH halves exist: in the `.c`
  (what makes the match, what the port reads) and in Ghidra (what makes every *other* function
  touching that object readable). Current gap: **629 of 634** named C structs have no Ghidra type.
  ⚠ **And CHECK THE NAME THE TREE ALREADY USES before creating one.** I invented `Vec3` and
  `Hw60Flags` when 163 and 112 files already said `VecFx32` and `Hw60` — rivals to established
  names, which is the very thing this rule exists to stop. Both deleted; the real names now exist.
  `grep -rh "} Name;" src/ --include=*.c | sort -u` settles it in one command.
  Richest remaining, by files: `VecFx32` ✓, `Hw60` ✓, `MtxFx33` ✓, then `bit0` 45, `Flags` 43,
  `Field0` 37, `Entry` 36, `Params` 33. (`Node` appears in 147 files but with **conflicting**
  definitions, so it is a scratch name, not a shared type — do not unify it.)
- **Never** add a `Co-Authored-By: Claude` commit trailer.
- Verify **byte-exact** before wiring in. Never leave a non-matching `.c` in
  `auto/` or `calls/`.
- For an unassigned batch candidate, equivalent-but-unmatched C may temporarily go
  in `nonmatching/` only after completing the pre-park checklist
  (`gen_delinks` ignores `nonmatching/`, so it never touches the build).
- For an explicitly user-assigned function, `nonmatching/` is forbidden unless the
  user explicitly authorizes parking it. Keep experiments in `build/try/` and
  continue iterating.
- Standing authorization: routine decomp-loop commits + pushes (one per matched
  family/batch). Anything else (force-push, history rewrite): ask first.
- **COMMIT per batch, PUSH at most once an hour.** `dsd check` must give **306** before every push.
  ⚠ **This was already written here and I ignored it anyway** (2026-07-20, user had to say it
  twice): ~8 pushes in a single hour, one per matched family. Committing locally after each batch
  is right; pushing each one is not.
  **Make it a check, not an intention** — before `git push`, run:
  `git log -1 --format=%cr origin/main` and if it reads under an hour, just commit and carry on.
  The work is not at risk in the meantime: it is already committed locally.

## Toolchain (one line)

`mwccarm` 3.0 build 139 (patched license) · flags
`-O4,p -proc arm946e -interworking -lang c99 -enum int -char signed -inline on,noauto -Cpp_exceptions off -gccext,on`
· linker `mwldarm` · delink/config `dsd` = `tools/dsd.exe` · Ghidra MCP bridge at
**`:8089`** (program `days.nds` open) — **NOT 8080; that was wrong here for a long time.** If the
`mcp__ghidra__*` tools ever vanish mid-session, the bridge is still drivable over plain HTTP:
see "Ghidra without the MCP tools" in `references/tools.md`. Full compiler collection in `tools/mwccarm/`
(1.2 … 3.0_136_patched — 27 usable builds; sweep them all with `tools/build_sweep.py`, see
`references/tools.md`); per-file overrides in `config/arm9/file_compilers.json`.
`-inline on,noauto` = only `inline`-marked funcs inline (SDK-style
`static inline void f(T *ctx,…)` helpers reproduce codegen open-coding can't).

## ⇒ START OF EVERY ITERATION: sweep staging for WORK, not for paperwork

Peer lanes produce while you work on something else, so "the lane is empty" is a statement about
a MOMENT, not a state. This has cost twice: an ov006 lane refilled within minutes of my writing
that it was empty, and an entire **ov000** lane went unnoticed because I keyed the check on
`WORKLIST.txt` -- the lane's paperwork -- instead of on staged `.c` files.

⚠⚠ **AND IT HAS NOW COST A THIRD TIME, THE SAME WAY ONE LEVEL DOWN.** The snippet below used to
glob only `$d/calls/*.c` and `$d/auto/*.c`. The ov294/295/296 lane put its `.c` files at the
**lane root** (`staging/ov294/func_ov294_020d1a24.c`), so the sweep printed nothing while **six
byte-exact matches** sat there -- and I reported "staging is empty" in the same breath. The user
had to hand them over by name. The fix is to search the lane RECURSIVELY and never assume a
sub-layout: a peer lane's directory shape is its own business, and it will not match yours.

⚠⚠⚠ **AND THE "DONE" TEST WAS WRONG TOO — `src/overlays/$u/*/$n.c` MATCHES `nonmatching/`.**
A function that exists ONLY as a park looked already-integrated, which is exactly backwards: a
park is the strongest possible signal that a staged match is worth taking. `func_ov000_02055d98`
hid behind its own park note this way, in the same sweep that had just been fixed for the previous
bug. **Only `calls/` and `auto/` count as done** — `nonmatching/` and `asm_stubs/` never do.

```bash
for d in staging/*/; do u=$(basename "$d")
  find "$d" -name '*.c' 2>/dev/null | while read -r f; do n=$(basename "$f" .c)
    case "$n" in func_ov*|func_0*) ;; *) continue;; esac
    # ONLY calls/ and auto/ count as integrated -- never nonmatching/ or asm_stubs/
    [ -f "src/overlays/$u/calls/$n.c" ] || [ -f "src/overlays/$u/auto/$n.c" ] \
      || echo "PENDING $u/$n  ($f)"; done; done
```

⚠⚠⚠⚠ **AND A STAGED FILE THAT VERIFIES BYTE-EXACT CAN STILL BE AN ASM STUB. LOOK AT THE BODY.**
(2026-07-24, caught only because the user asked "are they actually decompiled?".) Ten `.c` files
from the ov000 lane verified MATCH, were wired into `calls/`, passed the 306 gate — and every one
of them was `asm Name f(void) { dcd 0xe92d4010; dcd ... }` with a decorative struct header on top.
An ASM stub verifies *trivially*: it IS the bytes. **`verify_idx.py` MATCH is not evidence of
decompilation, only of bytes.** Before integrating anything you did not write yourself:
`grep -c '  *dcd \|^asm ' <file>` must be 0.
The same sweep found **7 more already in `calls/` from earlier sessions**, so this had been
happening for a while, and the accounting hid it two ways:
- `audit_progress.py`'s ASM regex listed only builtin return types, so `asm Ov000StateFn f(void)`
  and `asm u8 f(int)` were classified as real C (fixed: any `asm <type> name(`);
- `progress.py`'s byte metric — the one the README calls honest — keyed purely on the PATH, so
  anything sitting in `calls/` counted regardless of content (fixed: it now calls
  `source_category()` too).
**Rule: never let the byte/function metric key on a directory name.** A stub in the wrong
directory is invisible to a path-based check and passes every other gate the project has.

**Then predict the arithmetic before you wire, and check it after.** Replacing an `asm_stubs/` twin
is *C up N / ASM down N*; a blob-gap carve with no stub is *C up N / ASM unchanged*. The ov000
family was handed over as "C up 6 / ASM down 6" and is really *C up 6 / ASM 0* — five of the six
had no stub. A mismatch means one of the two of you is wrong about what is on disk, and it is worth
ten seconds to find out which.

**The general rule, now three incidents deep: never key the sweep on a SHAPE you expect** — not
`WORKLIST.txt`, not `calls/`, not `auto/`. Key it on "a `.c` named after a function that is not
yet in `src/`", and let `find` do the walking. Also worth saying plainly: the sweep returning
nothing is the one result you should be suspicious of, because it is indistinguishable from a
sweep that is looking in the wrong place.

Then follow the hand-off procedure in `references/state.md`: verify every file from staging in
BOTH modes before moving it, verify again in place, rewrite the lane's proposed names to the
receiving unit's vocabulary, delete superseded `nonmatching/` twins, and run `audit_shadowed.py`
BEFORE the commit.

## The per-function loop (every time, in order)

1. **Pick a candidate according to the active mode.**
   - Explicit function/module from the user has priority.
   - In autonomous work, use **port-first play-order mode** and
     `references/port-play-order.md`; do not default to the easiest reloc-free
     function or to numeric overlay/address order.
   - Reloc-free status and shape-family yield may break a tie only between functions
     at the same play-order frontier.
   Undone funcs live as `asm_stubs/` files, existing historical `nonmatching/`
   candidates, or raw blob-gap functions (no per-func file — "carve" = create the
   `.c`). Ground truth is `build/func_index.json` (keyed `func_ovNNN_ADDR`; fields
   `hex`, `size`, `relocs`=[[offset,symbol],…]). See `references/tools.md` for the
   candidate-scan snippet.
2. **Ghidra first — always.** Read the decompilation, understand it, and rename the
   symbol + params + locals semantically as you go. Overlay addresses use a space
   prefix, e.g. `arm9_ov107::020cXXXX`. Known quirk: `endTransaction` may throw an
   NPE but the mutation still applies — verify by read-back, don't retry blindly.
   **And if the function reveals an object layout — a stride, a flag bit, a field you had to
   work out — CREATE OR EXTEND THE GHIDRA STRUCT NOW**, then type the parameter or the local so
   the decompilation actually uses it. `SrtTransform`, `SlotEntry`, `GameSession`,
   `CardTransferCtx` already exist; extend them rather than inventing a rival. A struct you
   postpone is a struct nobody writes — that is exactly how the project reached 13k matches with
   zero types.
3. **Write the C.** Keep the address name `func_ovNNN_ADDR`. Semantics live in
   Ghidra + an optional one-line comment when the WHY is non-obvious.
   **Before writing any call, grep the tree for that callee's real arity** —
   `grep -rh "func_XXXX(" src/ --include=*.c | grep -v extern | sort -u`. Free, and it is the
   single highest-value check in this file (see the arity section below).
   **Ghidra mutations: write a Jython `.py` into `~/ghidra_scripts/` and run it with
   `run_ghidra_script`, then a SEPARATE `save_program`, then READ THE RENAME BACK.**
   ⚠ **`run_script_inline` is DEAD** — it compiles as Java against a bundle stuck in a cached
   failure, runs nothing, and still prints `SCRIPT COMPLETED SUCCESSFULLY`. Details + the working
   pattern + the plain-HTTP fallback (port **8089**) are in `references/tools.md`.
   ⚠⚠ **AND THE WARNING ALONE DOES NOT WORK — IT HIT TWICE MORE ON 2026-07-25**, in the same
   session, on two different files, hours after this line was re-read. Knowing the rule does
   not help because the `★` gets typed into prose you are *writing about* the work. **The
   defence is mechanical: validate BEFORE you open the file**, because `open(p,'w')` truncates
   first and the encode error arrives too late:
   ```python
   assert all(ord(ch) < 128 for ch in text), "file must stay ASCII"
   open(p, "w").write(text)
   ```
   Recovery is cheap only if a copy of the body exists elsewhere in `build/try/` — both times
   it did, by luck. **Keep the source ASCII** — a `★` in a Python heredoc that writes a file truncates it on
   `open(p,'w')` before the cp1252 encode fails (`wc -c` catches it).
4. **Verify byte-exact BEFORE wiring in** (never chain `verify && commit` — a
   DIFIERE still commits):
   `python tools/verify_idx.py <file.c> <func_name>` — **and if it fails, run it again with
   `--thumb` before believing the failure.** Windows `python` has capstone; git-bash `python3`
   does not.
5. **Wire it in.** Match → keep the `.c` in `auto/` (reloc-free) or `calls/` (has
   relocs); **delete any `asm_stubs/` twin** — it shadows via last-wins sort, so the function
   keeps counting as ASM *and the ROM keeps being built from the blob*. `tools/audit_shadowed.py`
   sweeps for these (50 found on 2026-07-17, 46 of them free). Commit locally.
   DIFIERE:
   - **Unassigned batch candidate:** run the pre-park checklist before considering
     `nonmatching/`.
   - **Explicitly user-assigned function:** do not park it, do not move to another
     function, and do not treat completion of the checklist as permission to stop.
     Continue the compiled matching loop until byte-exact, unless the user explicitly
     authorizes parking.

## ★★★ Before you park ANYTHING in `nonmatching/` — unassigned batch candidates only

This section does **not** grant permission to park an explicitly user-assigned
function. Assigned-function mode has higher priority and requires continued matching
until byte-exact or until the user explicitly authorizes parking.

On 2026-07-17, **five** functions parked as "register-allocation ties" turned out to be dropped
arguments — including one with ten ruled-out variants and one whose author had tried **25 mwcc
builds**. Parking is the most expensive mistake in this project: it burns the analysis, blocks the
whole shape family (dedupprop will not propagate from a `nonmatching/` rep), and the write-up then
*persuades the next session not to look*. Run every item:

1. **`--thumb`.** A THUMB function verified as ARM prints a meaningless size gap. Always both.
2. **Arity of every callee.** `grep` the tree for real call sites; `python tools/audit_arity.py`
   does it in bulk. **A dropped trailing argument does NOT change the size** — so "the size is
   right" is not a reason to skip this.
3. **Is a constant in the wrong register?** That is the arity smell, not a regalloc smell. Look for
   a `mov rN, #0` hoisted ABOVE a branch: one 0 doing double duty as a field store *and* a call's
   trailing argument.
4. **Read your own diff back.** "Everything matches except <one register>" is exactly what a
   dropped argument looks like.
5. **Is our `void` actually `void`?** A function's return type is part of its register
   allocation: a discarded return value frees r0, a propagated one reserves it. If the ROM avoids
   r0 right after a `bl`, ask whether the enclosing function *returns that call's result*. This
   was worth **22 functions** on 2026-07-18 against a park note that had ruled out 27 builds, 44
   flag combinations and 13 source spellings — all of them varying the callee, none the caller.
5b. ★★★ **Does your C contain a POINTER CAST or a hand-computed byte offset?** `(char *)table + n`,
   `(T *)(base + i*0x10)`, `group <<= 4`. If so the C is probably wrong, not the compiler: you are
   transcribing the ROM's addressing instead of reconstructing the source. Write `table[i]`,
   **duplicate the lookup instead of caching it in a local**, and read `base + a + b*K` as a nested
   array. This closed `func_ov029_020b2ee0` at the first attempt after months parked behind ~19
   spellings, 12 compiler builds and 10 flag sets. Full rules at the end of `codegen-cracks.md`.
   **It is a RE-TEST VEIN, not one case**: `python tools/find_cast_parks.py` ranks the parked files
   by the symptom — **209 of 410 (51%) carry it**.
   ⚠ **But the symptom is a SCREEN, not a verdict.** First re-test off that list
   (`ov022_02083bd8`) did carry three `(char *)&data + 8` casts, was rewritten to the array form —
   and the residue did not move: its park was right, the constant really is a pool-loaded literal.
   Confirmed the cheap way, by checking the pool word has **no reloc** (a reloc there would have
   meant a symbol, not a literal). So: rewrite the cast anyway because it is better C, but expect
   a real hit rate well under 51%, and check the pool-vs-literal distinction before blaming
   anything.
6. **Only if you are about to blame the COMPILER BUILD: run the sweep.**
   `python tools/build_sweep.py <func> [...]` compiles it with all 27 mwccarm builds in
   `tools/mwccarm/` and compares reloc-aware. "No mwcc version reproduces this" is the one park
   rationale that is cheap to actually test, so it is never admissible untested — and the answer
   has been *no build differs* every time (see `references/tools.md`). Feed it **only C already
   proven correct** (right size, right instruction stream): sweeping doubtful C is what made the
   original tie-suite meaningless.

★★★ **THE PARKED FILE MUST HOLD YOUR BEST FORM, NOT YOUR LAST ONE.** (2026-07-20.)
`func_ov002_020760ec` sat parked carrying form 9 of nine attempts simply because it was the
one on disk when I stopped. A later build sweep run against it reported 52 bytes off for our
compiler and 47 for the dsi line -- a number that would have sent the next reader chasing dsi
for nothing. Before you park, put the closest source back, and say in the note which form it
is and what the residue is *for that form*. Every later measurement is against whatever you
left behind.

★★ **A park can also be INFRASTRUCTURE, not codegen -- and grinding source forms will never
find it.** `func_020234e8` was 4 bytes short with the size, every instruction and every reloc
OFFSET already exact. The cause: the ROM's literal pool holds `0x0204be08` twice, and mwcc
emits two pool entries only for two DISTINCT symbols, while `config/arm9/symbols.txt` gave that
address one name. It is now the file's **only duplicate address** (`data_0204be08_params`),
added with the user's approval and measured clean -- gate 306/0 with it, and again with the
function wired in; `gen_delinks.py` and `audit_progress.py` filter to `kind:function(...)` so a
`kind:bss` alias is invisible to them. **`verify_idx.py` had to be taught to compare reloc
ADDRESSES rather than spellings**, because `func_index.json` resolves an address to its FIRST
symbol and was reporting `relocs difieren` on a function the real gate accepted -- the tool
disagreeing with the gate is the tell. If you meet a function that is exact except for its
literal pool, count the pool entries against the distinct symbols before blaming anything else.

And when you do park: the write-up records **one attempt at one moment, not a property of the
function.** Say what you ruled out and on what axis. Never write "unreachable".

## The family-harvest loop (HIGH YIELD — subordinate to play order)

In port-first play-order mode, family harvesting is allowed only when the family
representative is on the current frontier or the propagated matches are direct
dependencies of that same frontier. Do not leave the current gameplay milestone to
harvest a larger late-game family.

Many funcs are byte-identical across overlays modulo reloc symbols ("shape
families"). Match ONE template by hand, fan out the rest mechanically. See
`references/families.md` for the full family map and the c634-handler catalog
(the biggest vein), and `references/tools.md` for `scan_fam.py` / `genfamily.py` /
`dedupprop.py`. The masked-hex dedup (`dedupprop.py`) propagates a matched rep to
its byte-identical twins for free — run it after each batch.

**Efficient batch loop (proven on the ov006/ov008 title-menu sweep, 2026-07-16):**
1. `dedupprop.py` first — free byte-identical twins (yielded 19+4 in one session).
2. Prefer **medium funcs WITH calls** (100–250 B, 4+ relocs): the reloc-masked bl's dominate,
   so scheduling/regalloc noise is hidden. Tiny reloc-free leaf accessors are the WORST ratio
   (one instruction = the whole function → most are 1-instr ties).
3. Decompile 4 at a time; write them; verify all; commit the matches, diff the rest.
4. Suspect a **wrong arg count** before anything else — whether the size is off *or not*.
   Phantom args change the size; dropped trailing args don't.
5. Recognise the **tie class** from the first diff (catalog in `deferred-ties.md`). ⚠ **Do not
   route to `nonmatching/` on a class match alone.** "Regalloc swap" and "read-order" are exactly
   what a dropped argument looks like, and five 2026-07-17 rescues were sitting under those
   labels. For an unassigned batch candidate, run the pre-park checklist first; only then may it be
   parked. For an explicitly assigned function, do not park — assigned-function mode overrides
   this batch rule.
6. ov008 funcs usually have a **twin** in ov006 (same shape, other globals): a twin's outcome
   predicts this one's.
7. After a bulk `dedupprop --write`, run **`python tools/audit_shadowed.py`** — propagation creates
   `asm_stubs/` shadows. The tell is **C moving by less than you added**; the correct shape when
   real C replaces a stub is **C up N / ASM down N**.

## ★ Ghidra's DECOMPILE is not a source of truth — the disassembly is

The single most expensive recurring error. In one session (2026-07-16) the decompiler was wrong
**six times**, and every one was caught only by reading `disassemble_function`:

| trap | example |
|---|---|
| **Phantom / dropped arguments** | `func_02033fec(0)` really takes `(0, 0x1e)`; `02055a54` takes 3 not 2; `020551a4` takes 5 (the 5th on the stack via `str r1,[sp,#0]`); `02084c24` takes 1, Ghidra invented 4 |
| **A pool label read as a data symbol** | `DAT_arm9_ov024__02093a20` is the **pool entry**, and its value is the literal `0x04000304` = REG_POWCNT1. Taking it for a variable costs a bogus `extern` and an extra deref. **Tell them apart by checking for a reloc at that offset — no reloc ⇒ it's a literal.** |
| **Inverted constant mapping** | ov006 020521a0's flags: Ghidra's order was backwards; the pool says 1→0x821, 2→0x411, 3→0x412 |
| **Signedness** | fields rendered `undefined`/`char` that are really `ldrsb` (signed) or `ldrb` (unsigned) — wrong choice = instant mismatch |

★★ **A dropped TRAILING ZERO-argument does not change the size — it moves a constant into the
wrong register** (2026-07-17, cost a bogus `nonmatching/` write-up). `func_ov212_020ce0d4` was
parked as "a pure allocator coin-flip" after ten ruled-out variants; the real cause was declaring
`func_0203b9fc` with 3 args when it takes 4. The dropped `0` is the ROM's `mov r3, #0` — the *same*
value its zero-stores share — so with the argument present mwcc is forced to put it in r3, and
without it the 0 is free scratch and lands in ip. **The size was RIGHT the whole time**, which is
exactly why the arity was never suspected: the rule above says to suspect arity when the size is
off, and that quietly implies the converse. It doesn't.
- **Before writing any call, grep the tree for existing call sites of that callee**
  (`grep -rh "func_XXXX(" src/ --include=*.c | sort -u`). It already had
  `func_0203b9fc(a, b, c, 0)` in several files. The check is free and it beats ten compiles.
- Corollary: **when a diff is "one constant is in the wrong register", check the arity of every
  call that could want that constant** before concluding regalloc.
- And: a confident `nonmatching/` write-up is not evidence. That one listed ten variants — every
  one testing the wrong axis.

**Rule: when the size is far off, or a constant looks odd, disassemble before touching the C.**
`verify_idx.py` also flags reloc-NAME mismatches (it prints `orig = {...}`) — the index usually
already knows the real symbol (`SND_SetChannelVolume`, …). Read that instead of inventing names.

## ★ Check the mode BEFORE diagnosing anything

`symbols.txt` carries `kind:function(arm|thumb,size=…)`. **A THUMB function verified as ARM gives
a meaningless size gap** — `func_020342e8` carried a `nonmatching` note claiming a 392-vs-228
register-allocation tie; verified with `--thumb` the real gap is 3 instructions. Always:
`grep '^<name> ' config/arm9/**/symbols.txt` → add `--thumb` if needed.

★★★ **It also fabricates WHOLE FALSE THEORIES, and those outlive the session that made them.**
The memory archive carried a confident entry: *"0x0203xxxx symbols are SYSTEMATICALLY MIS-BOUNDED
(~16B late) — SKIP all 0x0203xxxx worklist entries"*, with three named "confirmed" functions and a
diagnostic tell (*"the ORIG disasm starts with a PREDICATED return"*). **All of it was the mode
trap.** Re-checked 2026-07-18: all seven parked funcs in that range start with a normal `push`
prologue **in their correct mode**, and `func_0203b9ac` matched byte-exact that same day. A
predicated-looking first instruction (`bmi`, `addlt`, `moveq`) is simply what THUMB looks like read
as ARM. Retracted in memory. Two lessons: **check the mode before believing any claim about a
function's shape**, and **never let a blanket address-range skip stand without re-testing it** —
that one silently fenced off a whole address range.

★★ **This bites NEW TOOLS, not just people — the cheap fix is to always try both.**
2026-07-17: a fresh `audit_shadowed.py` shelled out to `verify_idx.py` in ARM only, reported
`152 != 104` on four THUMB functions, and I moved **four perfectly matching functions out of
`calls/`** on that basis. `dedupprop` does `verify(...) or verify(..., thumb=True)`, re-rescued all
four, and **the two tools contradicting each other is the only reason it was caught**.
**Any tool that COMPILES must handle both modes** — you rarely know the mode up front, and the
ARM-only failure is indistinguishable from broken C.

★★★ **Widened 2026-07-18, because the narrower rule ("any tool that calls `verify_idx.py`") let the
next one through.** `tools/build_sweep.py` doesn't call `verify_idx` — it re-implements
compile-and-compare inline — so it read as out of scope, and it compiled **ARM-only across all 27
builds**. On `func_02020974` (2 B THUMB, a **perfect match**) it reported `size 4` on 27/27, i.e.
*"no compiler in existence reproduces this"* — the single most expensive false negative available,
since that is precisely the evidence a park is written on. **994 THUMB functions have real C**, so
the exposure was ~8% of the corpus. Fixed: the mode now comes from `symbols.txt`, with try-both as
the fallback. The lesson is about the rule, not the tool: **scope a hard-won rule by the failure
mode (compiling in one mode), never by the API that happened to expose it.**
(The old note here said an audit of all 46 THUMB `nonmatching/` files found zero mis-verified cases,
so "don't re-run that sweep". True of that sweep — but it read as "the THUMB trap is handled", and
it is not: it recurs every time a new tool is written.)

## ★★★ GREP THE MATCHED TREE FOR THE INSTRUCTION before experimenting on the C

*(2026-07-18, cost 7 compile experiments that a one-line search would have replaced.)*

`func_ov194_020ccb78` needed a **post-indexed** `ldr r0,[r4],#0x18`. I wrote seven candidate C
forms, compiled them, found none emitted post-indexing, and was about to file it as
"no C form known". Then I searched the already-matched functions for the instruction:
**175 matched functions contain post-indexed loads, and one — `func_ov247_020d281c` — had the
exact `#0x18` stride, with a comment explaining the form was deliberate.**

```c
owner = *ctx;
ctx = (int *)((char *)ctx + 0x18);   /* BYTE cast, not `ctx += 6` */
*(Vec3 *)(owner + 0xf0) = *(Vec3 *)ctx;
```

**So: when you need a specific instruction you do not know how to produce, the first move is
`disassemble every matched function and grep for it`, not a compile experiment.** The corpus is
12,000+ functions of known-good C; whatever you need has probably been solved once already.

```python
# for each name with real C (skip asm_stubs/ and nonmatching/), disassemble in the RIGHT mode
# and regex the mnemonic+operands. Filter pool garbage: require plain registers, and note that
# the literal pool at the end decodes as nonsense instructions.
PI = re.compile(r'^(ldr|ldrb|ldrh|str|strb|strh) (r\d+|ip|lr), \[(r\d+|ip|lr)\], #(0x[0-9a-f]+|\d+)$')
```

## ★ Negative results: state the positive form first

Adopted with the port team after four separate misfires in one session:

> **Before concluding from a negative, state the positive form the thing would take and confirm
> your search could match it.**

Real cases: a `str rX,[rY,#0x38]` sweep returned zero because the mask `0x0FFF0FFF` leaves Rn *in*
(so it only matched `[r0,#0x38]` — correct mask `0x0FF00FFF`); a "nobody validates the MODS magic"
claim from scanning 32-bit constants when the check is byte-wise (`cmp #0x4e`/`cmp #0x33`); "the
blob has no transform because `mla == 0`" when H.264-family integer transforms are add/shift by
design. **Zero hits from a search that could not have found it is not evidence.**

★ **The most expensive instance so far (2026-07-17), because it reached a commit.** The RNG copy
artifact was declared an unbreakable compiler tie and a function was routed to `nonmatching/` on
that basis. Both halves of the evidence were wrong:
- The pattern has **two spellings** — `add r0,r0,#0`, and `adds r0,r0,#0` when the result is tested
  against zero (copy and test fused). The census grepped only the first.
- Of the functions that *did* carry it, nearly every "match" was an **`asm_stubs` blob**, which
  verifies trivially. They made the crack look never-achieved when 7 real-C functions already used
  it.

Two rules fall out, and they generalise beyond that one artifact:
1. **When you grep for a codegen shape, ask what its variants look like first** (flag-setting vs
   not, scheduled apart vs adjacent — the same artifact also turned up one instruction *after* the
   `bl` in `func_ov125_020cd27c` because a load got scheduled in between).
2. **Filter `asm_stubs` out of any "has this ever been done in C?" count**, or the answer is
   meaningless. Same for "matched" in `dedupprop` terms.

## When it DIFFERE: steer, don't defer (usually)

A shape difference (same semantics, wrong regs/instructions) is usually
**steerable** by rewriting equivalent C. Read `references/codegen-cracks.md` — it
is the distilled catalog (bitfields, division-by-constant, conditional block
layout, register/declaration order, offset splitting, 64-bit fields, loops,
tail-calls, ternary order). Try the matching crack before giving up.

Some patterns may be genuine mwcc-version ties. Those are recorded in
`references/deferred-ties.md`.

For an unassigned batch candidate, a listed tie may justify parking only after the
complete pre-park checklist and compiler sweep.

For an explicitly user-assigned function, the tie list is not a stopping condition.
Treat it as historical evidence that may itself be wrong. Continue investigating
source shape, prototypes, caller return type, arity, aliasing, stack layout and
infrastructure until the function matches or the user authorizes parking.

⚠ **Treat that list as a prior, not a verdict.** Its whole point is to save cycles, which makes it
the most dangerous file here: matching a listed tie is a reason to *stop iterating on steers*, never
a reason to skip the checklist. Track record so far — the RNG `add r0,r0,#0` entry was wrong (155
functions blocked by a one-spelling census), and on 2026-07-17 five functions filed under
"regalloc swap" / "scheduling tie" were dropped arguments. **When a listed tie turns out to be
wrong, fix the entry** — leaving it costs the next session the same day.

## ★★★ Recent assigned-function rescues — do not repeat these false parks

The following functions were previously treated as nonmatching/park candidates and
were later solved byte-exact. Use them as mandatory evidence that high-score register
or stack residues are normally source-shape, prototype, or aliasing problems:

- `func_ov007_0204d0ec`: a justified `volatile` store fixed instruction scheduling.
- `func_ov301_020cbfc4`: `register` plus the exact order of two local struct
  declarations fixed register allocation and stack layout.
- `func_ov010_0204cac0`: the enclosing function was not `void`; preserving and
  returning the callee result produced the target registers.
- `func_ov294_020d1a24`: `func_0203355c` had a missing second argument; the extra
  live argument fixed the final register stream.
- `func_ov294_020d2008`: exact stack-local grouping, declaration order and direct
  struct use were required.
- `func_ov000_02055d98`: both call sites had dropped arguments.
- `func_ov000_020552b4`: representing the same object with one `struct Root` instead
  of two aliasing types fixed MWCC register allocation.

When a new assigned function resembles any of these residues, test the same axis
before considering a compiler tie. A score above 95% is evidence that the function
is probably solvable, not permission to stop.

## The 306 build gate + push (hourly)

Per-function `verify_idx.py` = MATCH is the fast gate. Before a push, run the FULL
306 gate — but ONLY via the correct procedure (`ninja build/arm9.elf` mono link
gives a FALSE ~193/113). The gate script and the exact steps are in
`references/tools.md` (restore reference bins → `configure && ninja` DEFAULT target
→ `dsd check modules`). Expect `DSD_OK=306 FAILED=0`.

**Every hour, at/just before the push, also regenerate the progress docs**
(user asked 2026-07-13): `python tools/progress.py` (from `tools/`) rewrites
`PROGRESS.md` and prints the counts; then hand-update the 5 count lines +
percentages in `README.md`'s Status table (`named_only = 23240 − C − ASM − SDK`,
plus the byte %) and commit `PROGRESS.md`+`README.md` together. `progress.md` /
`readme.md` are the same case-insensitive files on Windows.

## References (read on demand)

- **`references/port-play-order.md` — READ WITH `game-flow.md` BEFORE AUTONOMOUS
  CANDIDATE SELECTION.** It is the living boot-to-gameplay frontier for the PC port:
  current milestone, exact next function, dependencies, and evidence.
- **`references/game-flow.md` — verified boot, scene and transition facts.** Update it
  only when runtime/disassembly evidence changes the known execution order.
- **`references/state.md` — READ FIRST: where things stand, which fronts are open, what
  the port is waiting on. Keep it current.**
- `references/procedure.md` — full toolchain, per-function + family loops in
  detail, THUMB specifics, `nonmatching/` policy, git rules, the exact 306 gate.
- `references/codegen-cracks.md` — the distilled "symptom → C form" crack catalog.
- `references/families.md` — shape-family map, c634-handler hubs & catalog, the
  big veins (c5c0 spawn, d15c ctor, registrar, accessors, THUMB families).
- `references/deferred-ties.md` — do-NOT-retry compiler ties. ⚠ **Its `func_ov029_020b2ee0` row is
  retracted** (2026-07-20) and the rest of that table has not been re-tested against the
  array-lookup crack.
- `references/ov028-dsprotect.md` — **ov028 is not game code: it is DS Protect 1.10**, a commercial
  anti-piracy library (emulator/flashcart detection) used by 300+ DS titles. Identified via the
  decomp.me Discord and **verified here by decrypting the bodies**. It explains three long-standing
  oddities at once: why `0208a994` must be built with **mwcc 1.2 sp4** (third-party precompiled
  middleware, not the studio's 3.0), what the `0x88888889` is (`if (i % 15 == 0) key[i] ^= 0xFF`),
  and why the RC4 KSA runs backwards (a deliberate DS Protect modification).
  ★ **The `0x88888889` pattern appears in NINE overlays** (ov005/028/039/058/078/095/115/116…), so
  if you meet an anti-tamper function carrying it, read that file before analysing from scratch —
  it is the same product and can be named the same way.
  ⚠ **It does NOT change the `.rodata` classification.** In the static ROM the bodies are still
  encrypted; `dsd delink` dies with `IllegalIns @0x0208ac00` if the blob is marked `.text` (tried
  and reverted 2026-07-10). The identification is for **naming and understanding**, not for moving
  sections. Credit: taxicat1's `dsprot` decompilation.
- `references/naming-hubs.md` — **the naming debt AND the struct catalogue**: rank it by call-graph in-degree (naming 3% of
  the debt removed 37% of the call-site opacity: 24,639 -> 15,510), why the debt is self-referential and only clears from
  the named frontier outward, the evidence behind every hub name so far, and the honest unknowns.
  Also **the four structs that exist and the three traps of creating more**, and the THUMB trap in
  the Ghidra *define* path (1-byte phantom functions).
- `references/tools.md` — every tool command, the candidate-scan snippet, the 306
  gate script, `dedupprop.py`, Ghidra naming.
- `references/title-menu-layout.md` — ov006/ov008/ov025 menu resource & layout map
  (Archive_LoadFile path-vs-packed-handle, res.p2/BGU files, the 12-slot cursor object,
  layout = archive subfile #0x13 → tag-table). **⚠ Its title-screen framing is WRONG and the
  file opens with the correction** — see the scene-id table below.
- `references/ov028-dsprotect.md` — **ov028 is DS Protect 1.10**, a third-party anti-piracy
  library (300+ DS titles), not game code. Verified by decrypting the bodies with
  `tools/dsprot_decrypt.py`. Real names for all 17 symbols, and it explains three
  long-standing puzzles at once (the `0x88888889` reciprocal, the reversed RC4 KSA, and why
  `0208a994` needs mwcc 1.2 sp4). The same pattern is in nine overlays. Read before touching
  any `0x88888889` anti-tamper function.
- `references/ov024-mobiclip.md` — the MobiClip codec: YCoCg (not YUV) + the proven
  saturation table + the 2×2 dither, the MODS container, the audio path, and the video
  decoder's 26 KB ITCM blob. Read before any ov024 work.

## ★ Scene identities — verify before naming anything after a screen

| overlay | what it actually is | evidence |
|---|---|---|
| **ov000** | **title + every menu level + the "Load" screen** (the KH logo stays on top throughout); also the boot chain | runtime `curId = 1`; `/ttl/ttl.p2` + `ttl/ttl_&.p2` live here |
| **ov006** | **character select (Mission Mode / multiplayer)** — *not* the title | runtime `curId = 7`; every resource it loads is `UI/mlt/*` + the font |
| **ov012** | movie player scene wrapper (enters ov024 at `func_ov024_02084df4`) | 7,904 B — too small to be the codec |
| **ov024** | MobiClip codec **and** its own player scene tick (`func_ov024_02082f04`) | not codec-only |

`~23 Ov006_Title*` symbols had to be renamed to `Ov006_Mission*` and 61 source comments fixed
because a brief said "título ov06" and it was taken as given. **Check the runtime scene id or the
overlay's resource strings before naming anything after a screen** — it costs ten seconds.

Deep archive (exhaustive, older): the memory files under
`~/.claude/projects/E--KH-3582-decomp/memory/` (esp. `project_khdays_codegen_steering`,
`project_khdays_shapefamily_harvest`, `reference_c634_handler_cracks`). Prefer this
skill; fall back to memory only for a crack not yet distilled here — then distill it.