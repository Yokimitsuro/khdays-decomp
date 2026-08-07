# ★★★ UN HELPER DE REESCRITURA QUE NO ENCUENTRA NADA TIENE QUE PETAR, NO DEVOLVER LA ENTRADA
*(27/07, cazado en el barrido de formas de `func_ov011_0205ac40`)*

**El fallo**: un barrido que reescribe el fuente para generar variantes usaba un helper que
buscaba el texto literal `frame.openParams.enabled` para mover una sentencia. Las variantes con
`union` renombran ese campo a `frame.s.openParams.enabled`, asi que el helper **no encontro nada,
devolvio la entrada sin tocar**, y el barrido informo de la variante union como "2 palabras" --
o sea **volvio a medir el control y parecio un avance**.

**Es la misma familia que ya nos ha mordido tres veces**: un blob de `asm_stubs` verifica
trivialmente; Jython informa `SCRIPT COMPLETED SUCCESSFULLY` mientras revienta por el limite de
64K; un scorer que cuenta lineas distintas leyo el diff vacio de una compilacion abortada como
**cero diferencias, o sea MATCH**. Siempre lo mismo: **la ausencia de efecto leida como exito.**

**La defensa es mecanica**, y va en cualquier barrido que transforme texto:

```python
m = re.search(pattern, text)
assert m, "el helper no encontro nada"
text = text[:m.start()] + ... + text[m.end():]
```

Sin el `assert`, basta con renombrar un identificador en una variante para que la ejecucion
entera se convierta en un no-op silencioso que informa del control como si fuera la variante.

# Tools & commands

Run from `E:\KH 3582\decomp`. Windows `python` has capstone; git-bash `python3`
does not. Use the Bash tool (Git Bash) for POSIX scripts, PowerShell for others.

## Verify (per-function gate)

```
python tools/verify_idx.py <file.c> <func_name>            # ARM, reloc-aware
python tools/verify_idx.py <file.c> <func_name> --thumb    # THUMB
```
`>>> MATCH <<<` = byte-exact. `>>> DIFIERE <<<` prints the first differing byte
offset (after masking relocs) or the size mismatch. NEVER chain `verify && commit`.

Other: `python tools/match.py <file.c> <hex> [--thumb]` (reloc-free),
`python tools/getcand.py <func>` (mode/kind/hex/verify_cmd),
`python tools/td.py <func>` (THUMB disasm), `python tools/diffdis.py <c> <name>`
(ARM instruction diff) / `tdiff.py` (THUMB).

## ★★★ `python tools/build_sweep.py <func> [...]` — compile against ALL 27 mwccarm builds

The answer to *"maybe it needs a different compiler build"*. Compiles the function's C with every
`mwccarm.exe` under `tools/mwccarm/` (1.2/*, 2.0/*, 3.0_136*, 3.0_patch4, dsi/* — 27 usable, plus
unpatched `3.0_136` which always says `compile-fail`) and compares reloc-aware against
`build/func_index.json`. One row per build; `*** MATCH` flags a hit.

```
python tools/build_sweep.py func_ov000_020552b4                    # source auto-located
python tools/build_sweep.py func_a func_b func_c                   # one column each
python tools/build_sweep.py src/.../nonmatching/func_x.c:func_x    # explicit path:name
```

**Run it before ever writing "no mwcc version reproduces this" in a park note.** That claim used to
be made from memory; it is one command, and the standing answer is *no build differs*.

**Feed it only C already proven correct** — right size AND right instruction stream, differing in
something like one register. Sweeping doubtful C says nothing: the original tie-suite was run on
sources later found to have ordinary bugs, which is why its conclusion had no evidence behind it
even though it may have been right.

★★★ **The question is CLOSED as of 2026-07-18 — do not re-run this over the park set.** All 421
parks were triaged, and the 235 whose size is already right (the only ones where "which build" is
even a coherent question) were swept against all 26 usable builds:

- **0 / 235 match under ANY build.**
- The **12 modern builds** (`2.0/*`, `3.0_136_patched`, `3.0_patch4`) agree with each other on
  **232 / 235**. The 3 exceptions are trivial (606-vs-607 off; one `size+8`; one `off34`→`off6`
  across the `2.0/sp1p5`→`sp1p6` boundary). `1.2/*` and `dsi/*` are the wrong era.
- No build ever gets meaningfully closer than the project default.

So the build is not the variable, and one of those 235 was cracked the same day by changing the
**caller's return type** (24 functions — see `codegen-cracks.md`). The other 186 parks fail on
**size**, which is a source bug by definition.

## ⚠ `verify_idx` prints the FIRST differing byte — that is not a distance

`>>> DIFIERE <<< byte diff @0x21` vs `@0x38` tempts you to read the second as closer. It is not a
measure of anything: one early register choice can push the offset down while the rest of the
function matches perfectly, and vice versa.

Real case (2026-07-18, func_ov141_020cd2b0): a rewrite moved the first difference *earlier*
(0x38 → 0x21) and looked like a regression, but I checked — it was, by **36 differing bytes vs 8**.
The offset had been misleading in the *other* direction all day.

**When comparing two candidate sources, count differing bytes** (mask the relocs first) or use
`rank_parks.py`, which counts differing *instructions*. Cheap inline version:

```python
m, ob = bytearray(mine), bytearray(orig)          # after masking every reloc offset to 0
n = sum(1 for x, y in zip(m, ob) if x != y)
```

## ★★★ `python tools/rank_parks.py [N]` — rank parks by REAL closeness, not byte delta

Aligns each park's compiled stream against the ROM's (difflib over the disassembly) and sorts by
**how many instructions actually differ**. Writes `build/try/rank.json` with the ROM-only and
mine-only instructions per park — which is the diagnosis itself (signedness, cmp order,
if-conversion, …). Auto-detects ARM/THUMB.

⚠ **Byte delta does NOT measure closeness, and believing it costs a session.** On 2026-07-18 I
filtered the parks to "±4 bytes = one ARM instruction = the dropped-argument signature" and got
**103** candidates that looked like a huge vein. It is a coincidence filter: measured properly,
**1 of the 103** was a one-instruction difference. The other 102 differ by **5–58** instructions
and merely land 4 bytes apart. A mechanical dropped-argument tryer — self-tested against a real
positive first, so the zero is trustworthy — scored **0/103**.

The real ranking found **14 parks within 2 instructions**, and of the first five examined, **3
were fixed in minutes**: two `ldrb`-vs-`ldrsb` signedness twins (ov202/ov203) and one `v = i = 0`
chained assignment (`func_0203b9ac`). Those had been sitting in `nonmatching/` for months behind a
metric that never pointed at them.

**Generalisation: when you invent a proxy for "close", verify it against the thing it proxies
before you build a work queue on it.** ±4 bytes *sounds* like one instruction. It isn't.

Standing result (2026-07-17, on four proven-correct sources): **no build matches any of them**, and
all twelve `2.0/*` + `3.0_136_patched` + `3.0_patch4` emit **byte-identical output** (the same
17/27/44/112-off numbers everywhere). `1.2/*` and `dsi/*` are the wrong era (sizes off by 8–70 B).
So *"which point release"* has no traction across the set we have — and the real prior is
`references/state.md`'s: **12,191 functions match byte-exactly with this exact compiler**, so a
systematic regalloc difference would break all of them, not fifty. The build is the least likely
explanation, not the first.

Two traps, both hit for real — note that each made the sweep return a **uniform** answer, which is
exactly what looks like a clean result:

- ⚠ **`asm_stubs/` (2026-07-17, the tool's first run).** `glob("src/**/calls/<name>.c")` also matches
  `src/overlays/ovNNN/asm_stubs/calls/<name>.c`, and an asm stub reproduces the ROM under **any**
  compiler → the whole sweep came back `MATCH` and meant nothing. Now skipped. A check that cannot
  fail is not evidence.
- ⚠ **ARM-only compilation (2026-07-18).** The tool compiled every build in ARM, so a THUMB function
  reported `size N` on 27/27 — *"no compiler reproduces this"* on C that is a **perfect match**.
  Verified on `func_02020974` (2 B THUMB): 27/27 `size 4` before, 27/27 `MATCH` after. **994 THUMB
  functions have real C.** Fixed: the mode is read from `config/arm9/**/symbols.txt`
  (`kind:function(thumb…)`) and printed in the header as a `# <func>: thumb|arm` line — **read that
  line**; if it says `modo desconocido` the symbol wasn't found and both modes were tried (a THUMB
  hit is tagged `MATCH (t)`).

## The c634 move-dispatcher tools (added 2026-07-17)

```
python tools/genmove.py func_ovNNN_ADDR [-w]        # parse the reset block, emit the whole C
python tools/clonedispatch.py <src_c> <src> <dst>   # clone onto a byte-identical twin
python tools/dumpdispatch.py func_ovNNN_ADDR        # raw view: reset block + case->handler map
```
`genmove` is the default move for that vein (15/24 open dispatchers in one sweep, first try each).
All three **refuse rather than guess** when the shape is not one they know, and a refusal is real
signal — it means the function carries extra code and needs a human. See families.md for the census
predicate and the ranking heuristic. **If you teach genmove a new reset block, re-run its regression
set** (regenerate 8 already-matched dispatchers and check they are still byte-exact).

Compile-and-diff from `tools/` for debugging:
```python
import match
o = match.compile_c('../src/overlays/ovNNN/calls/func.c', False)  # thumb=bool
b, r = match.text_relocs(o)   # (bytes, relocs)
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM
for x in Cs(CS_ARCH_ARM, CS_MODE_ARM).disasm(b, 0): print(x.mnemonic, x.op_str)
```

## Candidate scan (find tractable c634 handlers, skipping ties)

Working snippet — adjust the size band and `skip` set:
```python
import json, glob, os
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM
d = json.load(open('build/func_index.json'))
done = set(os.path.basename(p)[:-2] for p in glob.glob('src/**/*.c', recursive=True))
TIE = ('0203b9fc','020c0b90','020c5c54','02023eb4','01ffa724','VEC_','FX_','MTX_')
def bad(ins):
    txt = ' '.join(x.mnemonic for x in ins)
    if 'blx' in txt or 'ldm' in txt: return True
    for x in ins:
        if x.mnemonic == 'mla' or ('lsl #2' in x.op_str): return True
    for k in range(len(ins)-3):                          # hw60 |= (defer)
        if ins[k].mnemonic == 'ldrh' and '0x60' in ins[k].op_str:
            for j in range(k+1, min(k+9, len(ins))):
                if ins[j].mnemonic == 'orr' and '#' in ins[j].op_str and 'lsr' not in ins[j].op_str: return True
                if ins[j].mnemonic == 'strh': break
    return False
names = []
for n, i in d.items():
    if n in done or not n.startswith('func_ov') or not (96 <= i.get('size',0) <= 200): continue
    syms = [s for o, s in i['relocs']]
    if 'func_0203c634' not in syms or 'func_02031384' in syms: continue
    if any(any(t in s for t in TIE) for o, s in i['relocs']): continue
    ins = list(Cs(CS_ARCH_ARM, CS_MODE_ARM).disasm(bytes.fromhex(i['hex']), 0))
    if bad(ins): continue
    names.append((i['size'], n))
names.sort()
for sz, r in names[:3]:
    e = d[r]; print('== %s (%dB) reloc=%s ==' % (r, sz, [s for o,s in e['relocs']]))
    for x in Cs(CS_ARCH_ARM, CS_MODE_ARM).disasm(bytes.fromhex(e['hex']), 0):
        print('  %04x %-7s %s' % (x.address, x.mnemonic, x.op_str))
```
Extract a pool literal (e.g. c5af8 arg, div magic): read `hex[off:off+4]` with
`struct.unpack('<I', …)`. For `ldr rX,[pc,#IMM]` at addr A: pool offset = A+8+IMM.

## Family scan / generate / name

```
python tools/scan_fam.py <minsize> [--thumb]              # rank stub families
python tools/genfamily.py <template> --write              # ARM: gen+verify+wire siblings
python tools/genfamily_thumb.py <template> --write        # THUMB
# THEN by hand: rm src/overlays/ovNNN/asm_stubs/{calls,auto}/<template>.c
python tools/namefam.py <template> <Name> "<plate>"       # writes ~/ghidra_scripts/NameFam.py
```
Run NameFam.py via ghidra MCP `run_ghidra_script`. It ends with a "No transaction
is open" exception AFTER `named=N … SAVED_OK` — that IS success.

## ★★★ `python tools/audit_arity.py` — mine your own `nonmatching/` for dropped arguments
*(added 2026-07-17: found 20 candidates, the first 3 tested all matched immediately = +8 functions)*

Lists every parked file that declares a callee with an arity **the matched tree never uses**. That
is a strong dropped-argument signal, and a dropped *trailing* argument **does not change the
function's size** — it moves a constant into the wrong register, so the diff reads as an
unbreakable allocator permutation and gets written up as one.

```
python tools/audit_arity.py           # strict — the real signal
python tools/audit_arity.py --loose   # mostly noise (K&R decls with varying counts)
```
Rescued this way on day one: `ov115_020ce20c` (+7 with twins), `ov256_020cd8f0`,
`ov212_020ce0d4`. **17 strict candidates are still open** — cheap, and each may be a family.

Workflow per hit: disassemble the call site and read what the ROM sets in r0-r3 / `[sp]`. **The
giveaway is a `mov rN, #0` hoisted ABOVE a branch** — that means the same 0 is doing double duty as
a field store *and* a call's trailing argument, which is exactly what the missing parameter was.

⚠ **After rescuing, delete the `asm_stubs/` twin** — see the next section; it is a bigger problem
than it looks.

## ⚠ `dedupprop.py` only sees `func_*` symbols — it is blind to SDK/lib-named families

Its line 61 is `if not name.startswith("func_"): continue`, so **any family whose members carry
SDK-ish names is invisible to it** — `SND_*`, `SNDi_*`, `WM_*`, `NNS*`, `CARD_*`, `FS_*`, veneers,
anything the SDK identifier touched. On 2026-07-17 it reported **2 candidate twins for an 87-member
family** and nothing looked wrong; the count was simply silently filtered.

**The tell:** you match a rep by hand, `dedupprop --write` says `matched=0`, and you assume there
were no twins. Census the index yourself before believing it:
```python
def masked(v):
    b = bytearray.fromhex(v['hex'])
    for off, _ in v.get('relocs', []):
        if off + 4 <= len(b): b[off:off+4] = b'\0\0\0\0'
    return bytes(b).hex()
sig = masked(idx['MY_MATCHED_REP'])
fam = [k for k, v in idx.items() if v.get('mode') == m and masked(v) == sig]
```
Then generate each member from its own relocs. (Left as-is rather than "fixed": widening the filter
would let it propagate into SDK-named territory unattended, which is a bigger decision — see the
13 SDK-identified veneers left alone in `state.md`.)

## ★★★ `python tools/audit_unnamed.py` — the naming debt, counted (needs Ghidra on :8089)
*(2026-07-17: first run said **50%**)*

The hard rule is that a match with no semantic layer is "half done" and does not count. That rule
relied on discipline and duly failed — six rescues were committed unnamed an hour after "don't let
the debt accumulate silently" was added to SKILL.md. **Discipline does not work; counting does.**

```
python tools/audit_unnamed.py           # summary + worst units
python tools/audit_unnamed.py --list    # every unnamed function
```
Read-only. Of 12,026 byte-exact C functions: **4,741 (39%) named · 5,956 (50%) still `FUN_*` ·
1,329 (11%) with no Ghidra function at all.** Run it **at the end of every session**.

⚠ It hit the overlay-prefix trap on its first run: `func_ov000_020593f4` is at
`arm9_ov000::020593f4`, **not** `020593f4`. Looking up bare addresses found nothing for every
overlay and reported a tidy-looking 585 — the same prefix trap that made a rename read-back report
27/27 "missing". If a Ghidra query returns suspiciously few hits, check the space prefix first.

## ★★★ `python tools/audit_shadowed.py` — finished C that the build ISN'T USING
*(2026-07-17: found 50, of which 46 were free — C 11,922 → 11,969, ASM −47, gate still 306/0)*

A function with real C in `auto/`/`calls/` **and** an `asm_stubs/` twin: the stub wins the last-wins
sort, so the function is (a) miscounted as `asm_stub_matched` and (b) **built from the ASM blob while
finished, byte-exact C sits next to it unused.** That is worse than a counting bug — the ROM was not
being built from the decompilation.

```
python tools/audit_shadowed.py            # report
python tools/audit_shadowed.py --verify   # compile-check each real C
python tools/audit_shadowed.py --fix      # delete stubs whose C verifies, then RUN THE 306 GATE
```
`--fix` never deletes a stub whose C fails to verify — there the `.c` is the broken one and the stub
is holding the build up. Those get reported: move the `.c` to `nonmatching/` (a non-matching `.c` in
`auto/`/`calls/` breaks the hard rule; 4 such files were found and parked).

**They accumulate after bulk `dedupprop --write`, so re-run this after any big propagation.** The
tell in `progress.py` is **C moving by less than you added**; the correct shape when real C replaces
a stub is **C up N / ASM down N**. Zero shadowed as of `c9aef68c`.

## ★★★ Ghidra without the MCP tools — talk to the bridge over plain HTTP (port **8089**)
*(proved 2026-07-17: drove 27 renames + saves this way after the MCP server died)*

**The `mcp__ghidra__*` tools can disappear mid-session** (a Windows freeze killed the bridge process;
it never came back, and reopening Ghidra does NOT revive it — the MCP client only reconnects when
Claude Code restarts). **You do not need them.** The plugin (com.xebyte GhidraMCP 5.14.2) serves the
same ~206 endpoints over TCP, and the MCP server is only a proxy. Drive it directly:

```python
import http.client, json, urllib.parse
def post(endpoint, payload, timeout=600):
    c = http.client.HTTPConnection("127.0.0.1", 8089, timeout=timeout)
    b = json.dumps(payload).encode()
    c.request("POST", "/"+endpoint, body=b,
              headers={"Content-Type":"application/json","Content-Length":str(len(b))})
    r = c.getresponse(); out = r.read().decode("utf-8","replace"); c.close(); return r.status, out
def get(endpoint, params=None, timeout=60):
    q = "?"+urllib.parse.urlencode(params) if params else ""
    c = http.client.HTTPConnection("127.0.0.1", 8089, timeout=timeout)
    c.request("GET", "/"+endpoint+q); r = c.getresponse()
    out = r.read().decode("utf-8","replace"); c.close(); return out.strip()

post("run_ghidra_script", {"script_name": "NameFoo.py"})   # then, separately:
post("save_program", {})
get("get_function_by_address", {"address": "arm9_ov212::020cdd08"})   # read back
```

Three traps, all hit on the first attempt:
1. **The port is 8089, not 8080.** SKILL.md said 8080 for months and `curl :8080` returns nothing,
   which reads exactly like "Ghidra is down". Check `netstat | grep 8089` before believing that.
   (The GhidraMCP status dialog reports the port; UDS is also available.)
2. **Read-back needs the overlay space prefix.** `get_function_by_address(address="020cdd08")`
   answers `No function found` even when the rename worked — it searches the default space. Use
   `arm9_ov212::020cdd08`. 27/27 "missing" turned into 27/27 correct on that one change; a search
   that could not have matched is not evidence (SKILL.md).
3. `search_functions_by_name` rejected every obvious param name (`query`/`search_term`/`name`/
   `pattern`/`term`) — don't burn time on it, go by address.

## ★★ `run_script_inline` is DEAD — write a `.py` and use `run_ghidra_script` (2026-07-17)

**SKILL.md step 3 still says to batch renames into one `run_script_inline`. Do not bother.**
That tool writes your body to `~/ghidra_scripts/McpInline_<hex>.java` and compiles it with the
**Java** provider, which compiles the *whole* `ghidra_scripts` bundle. An earlier session passed
**Python** to it, so a Jython file got saved with a `.java` extension, failed to compile, and Ghidra
**cached the failure**. The file is long gone, but the cache reports

> `~/ghidra_scripts hasn't changed, with 1 file failing in previous build(s)`

and refuses to rebuild — so **no inline script compiles or runs, ever**, including a bare
`println("hi")`. Restarting the session does not clear it.

**The trap is that it still reports `=== SCRIPT COMPLETED SUCCESSFULLY ===`.** The only tell is that
*your* script's output is missing and the error list names a file you never wrote. Read the output,
don't trust the banner: a silent no-op looks exactly like a success, and a rename you never made
looks exactly like one you did until you read it back.

**Use Jython + `run_ghidra_script` instead** — it takes the `JythonScriptProvider`, bypasses the
Java bundle completely, and works today (proved on `NameOv235Chooser.py`, 2026-07-17):
1. `Write` a `.py` into `C:\Users\Yokimitsuro\ghidra_scripts\` (ASCII only — see SKILL.md).
2. Self-managed `startTransaction` / `endTransaction(tx, ok)` inside it, exactly as below.
3. `run_ghidra_script(script_name="Foo.py")`, then a SEPARATE `save_program`.
4. **Read the rename back** (`search_functions`) before believing it.

This is the same pattern the next section already uses for defining blob-gap funcs — it is now the
*only* scripting route, not just the preferred one for `create_function`.

## ★ Defining blob-gap funcs in Ghidra — from a SCRIPT, never `create_function`

Many undone funcs have no Ghidra function yet (`disassemble_function` → "No function found").
Define them first — but **not with the MCP `create_function` tool**: on an overlay it returns the
`endTransaction` NPE (edit applies anyway) and a second call **times out**, leaving a leaked tx so
`save_program` fails with "Unable to lock due to active transaction". (The old rule said "never on
the main region"; 2026-07-16 proved it leaks on overlays too.)

Working pattern — one Jython script, one self-managed tx, then a SEPARATE `save_program`
(`MakeOv024Funcs.py`: 7 funcs, zero leaks):
```python
from ghidra.program.model.address import AddressSet
from ghidra.app.cmd.disassemble import ArmDisassembleCommand
from ghidra.app.cmd.function import CreateFunctionCmd
tx = currentProgram.startTransaction("define")
try:
    for addr, size, thumb in TARGETS:
        a = sp.getAddress(addr)
        if fm.getFunctionAt(a) is not None: continue
        ArmDisassembleCommand(a, AddressSet(a, a.add(size-1)), thumb).applyTo(currentProgram, monitor)
        CreateFunctionCmd(None, a, None, None).applyTo(currentProgram, monitor)
finally:
    currentProgram.endTransaction(tx, True)
```
**Read `thumb` and `size` out of `symbols.txt` — do not assume ARM.** Defining a THUMB func as ARM
produces plausible-looking garbage (`strcs r11,[r0],#-0x5f8` …), i.e. a wrong answer rather than an
error. Repair = `fm.removeFunction(a)` + `listing.clearCodeUnits(a, end, False)` + redo with
`thumb=True` (`FixOv024Thumb.py`).

If a save is already blocked: `TxProbe.py` (read-only: `entries/not_done/changed`) then
`CloseTxAndSave.py` → `active=N base=X; closed=N; tx_after=NONE; SAVED_OK`. The trailing
`IllegalStateException: No transaction is open` is cosmetic; confirm with TxProbe (`changed=False`).
Never guess transaction ids. See memory `reference_ghidra_leaked_tx_recovery`.

## dedupprop.py (masked-hex twin propagation — free matches)

**Now permanent at `tools/dedupprop.py`** (it used to live in the session scratchpad and kept
getting lost — that cost six iterations of single carves on 2026-07-16 before someone re-derived
it and it instantly returned 18/18). Self-locating, no args needed:

```
python tools/dedupprop.py            # dry run — lists candidate twins
python tools/dedupprop.py --write    # write, verify, keep the MATCHes
```
Builds `masked_hex → a DONE func with a .c`, copies the rep's `.c` to every UNDONE byte-identical
twin substituting reloc symbols in sorted-offset order (placeholder-swap to avoid partial
replaces), verify_idx (ARM then --thumb), keeps MATCH / rm the rest. Skips reps that live in
`nonmatching/`. Idempotent — re-running after a clean sweep prints `candidate twins=0`.
**Run it FIRST in every batch, and after each batch.** Also `tools/dedup_apply.py` for main-region
src.

### ★★ The gap dedupprop does NOT cover: families where NOTHING is done yet

`dedupprop.py` only propagates *from a matched rep*. Groups where every member is undone are
invisible to it — and that is where the volume is. Measured 2026-07-16: **1288 undone families
covering 3052 functions**. `scan_fam.py` does not find these either (it only ranks `asm_stubs`
families, and those are exhausted — it returns 0).

Scan for them directly (mask the reloc'd words, group, keep groups with ≥2 members and none done):
```python
import json, glob, os, collections
d = json.load(open('build/func_index.json'))
done = set(os.path.basename(p)[:-2] for p in glob.glob('src/**/*.c', recursive=True))
g = collections.defaultdict(list)
for n, e in d.items():
    if not n.startswith('func_') or not (40 <= e.get('size',0) <= 220): continue
    b = bytearray.fromhex(e['hex'])
    for off,_s in e['relocs']:
        if off+4 <= len(b): b[off:off+4] = b'\x00'*4
    g[bytes(b).hex()].append(n)
for mh, names in g.items():
    if len(names) >= 4 and not any(n in done for n in names):
        print(len(names), d[names[0]]['size'], names)
```
**Workflow: match ONE member by hand, then run `dedupprop.py --write` — the rest fall out free.**
Proven twice on 2026-07-16: `func_ov000_020550b0` (184 B) and `func_ov000_02055604` (196 B), both
6 members across ov000/005/008/009/025/026, both matched first try → 12 functions from 2 analyses.
The 40–220 B / ≥4-member band held 20 families / 86 functions; the whole undone-family set is far
bigger but the templates get large fast (the top one is 4512 B × 2).

★ **Write family templates with NO scene identity — structure only.** The propagated copies inherit
the template's prose verbatim, so a scene label in the template becomes a lie in five other
overlays (see below). Both templates above were written that way, and their copies needed zero
scrubbing.

### ★ ALWAYS fix the propagated comments before committing
The twin's `.c` is the rep's source verbatim, so it arrives carrying **the rep's scene identity**,
which is not established for the twin's overlay. The 2026-07-16 run produced 15 ov008 functions
labelled `Mission Mode:` (ov006's identity), one claiming to be the *ov006* scene constructor with
*ov006's scene id 7*, one claiming to drive "the ov025 panel", and an ov023 function labelled
`MobiClip:` cross-referencing an ov024 symbol. Committing those as-is would reproduce, at scale,
the exact mixup the scene-identity table in SKILL.md exists to prevent.

What to do: keep the structural body (offsets/logic — genuinely true, the code is identical),
strip the inherited scene label, and add a PROVENANCE banner naming the rep. **Check both
directions before scrubbing** — `ov008` really does load `UI/mlt/res.p2` (same pack as ov006), so
resource detail naming it is sound even though the "Mission Mode" label is not; `ov023` really is
*not* MobiClip (221 funcs, heavy `func_02021980`/`OS_SPrintf`). Grep the TRACKED files of the
target overlay for the label: if no committed file claims it, the label is not established.

## The 306 build gate (four lines -- run them directly)

```bash
cp dsd_extract/arm9/{arm9,itcm,dtcm}.bin build/build/
for f in dsd_extract/arm9_overlays/ov*.bin; do b=$(basename $f .bin); cp $f build/build/arm9_$b.bin; done
python tools/configure.py && ninja          # DEFAULT compile target, NOT arm9.elf
tools/dsd.exe check modules --config-path config/arm9/config.yaml -f
```
Expect `DSD_OK=306 FAILED=0`. `ninja build/arm9.elf` (mono) gives a FALSE 193/113 —
see procedure.md.

⚠ There used to be a `bck2.sh` wrapper for this in the session scratchpad. **Scratchpad
directories are per-session and do not survive**, so every pointer to one rots. If you
write a helper you want to keep, put it in `tools/` and commit it.

## Progress docs (hourly)

```
cd tools && python progress.py          # rewrites PROGRESS.md, prints counts
```
Then hand-update README.md Status table (C funcs+bytes, ASM, SDK,
named=23240−C−ASM−SDK, byte %). `grep '^| DONE ' PROGRESS.md` for the DONE list.
Commit `PROGRESS.md` + `README.md` together (`progress.md`/`readme.md` are the same
files on Windows). Then push (`git push origin main`).

## Git (routine loop)

```
git add -A src/                                   # only src/**.c (+ asm_stub deletions)
git commit -q -m "Carve <what> byte-exact"        # NO Co-Authored-By trailer
git rev-list --count origin/main..HEAD            # how far ahead (push ~hourly)
```
Do NOT stage `config/**/delinks.txt` (regenerated by configure, left dirty).

## Peer / concurrency

Overlapping loop fires can race — detect a live peer & yield before working. Another
session may own `staging/` (don't touch). See memory
`project_khdays_loop_concurrency`, `project_khdays_lane_directive`.

## ★★★★ `tools/nearfam.py` — funciones sin hacer que comparten FORMA con una ya casada

```
python tools/nearfam.py              # ranking: 1 edicion -> N matches
python tools/nearfam.py <func_name>  # que plantilla casada le corresponde
```

`dedupprop.py` propaga entre gemelas **byte-identicas** tras enmascarar relocs. `nearfam.py` va
un paso mas alla: agrupa por la **secuencia de mnemonicos** (ignora registros e inmediatos), asi
que encuentra la misma plantilla con otras constantes, otros offsets y otros simbolos.

Estado al crearlo (2026-07-18): **126 formas con plantilla casada cubriendo 382 funciones sin
hacer**. La primera valia 68.

⚠ **Filtra `asm_stubs/`.** El glob `src/**/calls/` tambien casa `src/**/asm_stubs/calls/`, y un
stub "casa" trivialmente: contarlo como plantilla hace que el ranking mienta. La primera version
de esta herramienta tenia ese bug y colaba 21 formas falsas (es exactamente la regla que ya
estaba escrita en SKILL.md, y aun asi la volvi a pisar al escribir la tool).

## `tools/gen_d15c_ctor.py` — genera una familia entera desde el desensamblado

Cuando `nearfam.py` saca una forma con muchas candidatas, **no las edites a mano**: escribe un
generador que extraiga los valores variables del desensamblado y emita el `.c`. Para la familia
de constructores `func_0203d15c` los valores eran cinco (tamaño del objeto, byte de tipo, tres
offsets) mas dos simbolos de los relocs → **145 candidatas, 145 MATCH, 0 fallos**.

Reglas que hicieron que saliera a la primera:
- **No heredar nada del template**: dos overlays de la misma forma difieren en el tamaño Y en el
  byte de tipo, y alguno en los offsets. Extraer los cinco, siempre.
- **Verificar cada fichero con `verify_idx` ANTES de escribirlo** en `calls/`, y no escribir los
  que no casen (regla dura del proyecto).
- Un mismo inmediato puede tener **dos usos** (aqui el byte de tipo es tambien el 3er argumento
  de `OS_SPrintf`); si lo extraes una vez y lo usas en los dos sitios, sale gratis.

## Ghidra: crear funciones que NO existen (ARM y THUMB)

Un `setName` que falla con **"no function"** casi nunca es una direccion mal puesta: es que
Ghidra nunca definio esa funcion. 105 de 145 constructores de esta familia estaban asi.

```python
from ghidra.app.cmd.disassemble import ArmDisassembleCommand
from ghidra.app.cmd.function import CreateFunctionCmd
ArmDisassembleCommand(addr, None, thumb).applyTo(currentProgram, monitor)  # 3er arg: True=THUMB
CreateFunctionCmd(addr).applyTo(currentProgram, monitor)
```
Para THUMB hay que ademas fijar el contexto antes: `pc.setRegisterValue(a, end,
RegisterValue(pc.getRegister("TMode"), BigInteger.ONE))` y limpiar las code units del rango.
Scripts listos: `~/ghidra_scripts/khdays_mkarm_20260718.py` y `khdays_mkthumb_20260718.py`.

⚠ **`except Exception` en Jython NO captura excepciones Java.** Usa un `except:` pelado. Un
`except Exception` alrededor de `endTransaction` deja escapar el `IllegalStateException` y el
script muere a medias — que es justo como se genera una transaccion colgada.

## Transaccion colgada → `save_program` falla con "Unable to lock due to active transaction"

`~/ghidra_scripts/khdays_fixtx.py`: abre una transaccion de sondeo para conocer el id actual y
cierra hacia atras hasta 40 ids con `except:` pelado. Cierra la fugada; el propio harness se
queja al terminar ("No transaction is open") porque le cerraste la suya, y eso es inofensivo —
**el `save_program` siguiente funciona**.

## ★★★★ `tools/port_template.py` — porta CUALQUIER plantilla casada a otra funcion de su forma

```
python tools/port_template.py <plantilla> <candidata> [--write]
python tools/port_template.py --all [--write]      # barre todo el ranking de nearfam
```

Generaliza `gen_d15c_ctor.py`: en vez de un generador por familia, empareja **por posicion** los
inmediatos y los simbolos de los relocs entre plantilla y candidata (que por construccion tienen
la misma secuencia de mnemonicos) y aplica las sustituciones al texto del `.c`. Verifica cada
salida con `verify_idx` en ARM **y** THUMB, y solo escribe las que casan.

Cosecha de la primera pasada (2026-07-18): **120 MATCH de 314 candidatas**, en un solo comando.
El resto: `DIFIERE=96` (la sustitucion textual fue ambigua o la forma esconde una diferencia
real → edicion a mano) y `forma/relocs no encajan=98` (distinto numero de relocs, o un inmediato
que mapearia a dos valores distintos — se rechaza a proposito en vez de arriesgar).

Detalles que importan:
- **Rechaza el mapeo ambiguo.** Si un mismo valor de la plantilla tendria que convertirse en dos
  valores distintos, devuelve "no encajan" en lugar de escribir algo dudoso. Preferir el falso
  negativo: cada MATCH que sale es real y verificado.
- **Escribe siempre con `encoding="utf-8"`.** Varias plantillas del arbol llevan `★`/`⚠` en los
  comentarios y el `open(...,"w")` por defecto de Windows (cp1252) revienta a mitad del barrido.
- Sustituye los simbolos de mas largo a mas corto para no romper prefijos comunes.

### Y despues: heredar el NOMBRE de la plantilla
`~/ghidra_scripts/khdays_name_20260718z.py` toma los pares (candidata, plantilla), lee el nombre
de la plantilla en Ghidra y se lo aplica a la candidata cambiando el prefijo de overlay; crea la
funcion antes si no existe. De 120: **69 nombradas, 51 saltadas porque la PLANTILLA tampoco tiene
nombre util**. Esas 51 son deuda de naming heredada, no nueva — y la forma barata de saldarla es
nombrar la plantilla y volver a pasar el script, que propaga a todas sus copias de golpe.

### `port_template.py`: las CUATRO estrategias, y por que existe cada una

Cada candidata se intenta con cuatro renderizados y se acepta **el primero que verifica**, asi que
añadir una estrategia nunca empeora: solo rescata candidatas que antes quedaban en `DIFIERE`.

| # | scaled | guard_shifts | min_val | rescata |
|---|---|---|---|---|
| 1 | no | si | 0 | el caso normal |
| 2 | **si** | si | 0 | el `.c` usa **indices de array** (`state[0xf]`) donde el mapa habla de **offsets de byte** (`#0x3c`). Sustituye tambien los valores /4. |
| 3 | si | si | **16** | un literal pequeño con **dos papeles** |
| 4 | si | **no** | 0 | la rara que si mueve de verdad el byte del bitfield |

Los dos blindajes (`guard_shifts` y los anchos `: N`) existen por la misma razon: en este arbol un
bitfield empaquetado se escribe como `(u << 0x10) >> 0x18` y esos numeros son **estructura**, no
datos. Un mapeo legitimo como `0x10 -> 5` los destroza y el residuo aparece en un sitio que no
tiene nada que ver con el cambio real — perseguirlo por el diff lleva a conclusiones falsas.

El caso de `min_val` es el mas instructivo: el mapa decia `8 -> 24` por UNA instruccion, y la
sustitucion textual reescribia tambien los `+ 8` que debian quedarse. **Es el limite de fondo de
sustituir por valor: el mismo literal con dos papeles.** Con las cuatro estrategias, la forma de
`func_ov270_020d4104` (6 candidatas) paso de 14 bytes a MATCH.

⚠ **El log se escribe con buffer**: durante un `--all` largo el fichero redirigido esta vacio
hasta el final. Para ver el avance, cuenta ficheros nuevos con `git status --porcelain src/`.

## `tools/audit_extern_sig.py` — externs de los parks contra la DEFINICION real

```
python tools/audit_extern_sig.py          # solo nonmatching/
python tools/audit_extern_sig.py --all    # tambien auto/ y calls/
```

Complementa a `audit_arity.py`: aquel compara contra como LLAMA el resto del arbol, este contra
como esta **definido** el callee. Nacio del rescate de func_ov041_020b3c10, donde el residuo era
un solo registro y la causa un `extern` con un parametro de menos.

Cosecha inmediata: **func_ov146_020ccdf4 rescatado** de `nonmatching/` (2 bytes → MATCH). El
`mov r1, #1` del ROM hacia doble papel — el store del campo Y el segundo argumento de la llamada.

Tres filtros que hubo que añadir, y cada uno es una leccion:

1. **`f()` NO es "cero argumentos"**, es "parametros sin especificar", y el arbol usa esa forma a
   proposito. Tratarla como 0 daba **70 falsos positivos de 377**.
2. **Solo cuenta si el fichero LLAMA al callee.** Cuando unicamente toma su direccion (callback
   pasado a `func_0203c634`), la aridad declarada no afecta al codegen.
3. ★ **Solo la direccion "declaro MENOS de lo definido" es accionable.** Al reves es legitimo:
   en el ABI de ARM un callee que lee menos parametros ignora los registros de mas, asi que el
   original puede pasar 2 a una funcion que solo usa 1 — **y el ROM SI pone r1**. Quitar ese
   argumento "sobrante" en `func_ov185_020ced78` lo llevo de +8 a **-44** bytes.
   La definicion **no es autoritativa** sobre lo que pasan los llamadores.

Con los tres filtros quedan **12 candidatos reales** de 376 parks. Cuatro estan exactamente a
`size -4` (una instruccion corta), que es la firma de un argumento perdido: son la cola natural
de rescates. Ojo: `func_ov000_02054e7c` es **THUMB** — lo delata que su reloc cae en un offset no
alineado a 4 (0x2e), truco util para detectar el modo sin abrir symbols.txt.

⚠ **Tras borrar stubs con `audit_shadowed.py --fix`, hay que volver a lanzar `configure.py` ANTES
de `ninja`.** Si no, ninja falla con `'src/.../asm_stubs/calls/func_X.c', needed by ... missing and
no known rule to make it` -- el `build.ninja` viejo sigue listando el stub recien borrado. Y ojo:
un `dsd check` lanzado despues de ese ninja fallido **sigue diciendo 306**, porque comprueba los
binarios anteriores. El 306 de un gate cuyo ninja fallo NO vale (2026-07-18).

## ⚠ Dos `ldr rX,[pc,#N]` pueden apuntar a LA MISMA palabra del pool

Al mapear cargas pc-relativas, calcula **siempre** el destino (`offset + 8 + N` en ARM,
`(offset + 4) & ~3 + N` en THUMB) y comparalo con la lista de relocs. Es facil suponer que dos
cargas distintas usan dos simbolos distintos: en func_ov188_020cee00 las dos primeras apuntaban a
**la misma** palabra (el mismo `data_02042264` para dos llamadas seguidas) y solo la tercera usaba
el otro simbolo.

Suponer lo contrario me costo cuatro compilaciones persiguiendo un supuesto problema de "orden del
pool" que no existia: mi codigo era correcto salvo que estaba pasando dos tablas donde el original
pasa una.

Script de un vistazo:
```python
for i in md.disasm(code, base):
    if 'pc' in i.op_str and i.mnemonic.startswith('ldr'):
        n = int(re.search(r'#(0x[0-9a-f]+|\d+)', i.op_str).group(1), 0)
        print(hex(off), '-> pool', hex(off + 8 + n))   # ARM
```
Cruzalo con `e['relocs']` y sabras que simbolo lleva cada carga antes de escribir una linea de C.

### El fallo transitorio de `configure` -- diagnostico (2026-07-19)

Ocurrio **5 veces** en una sesion, siempre verde al repetir, siempre en un `gen_delinks.py` de un
overlay distinto (ov124, ov057, ov194, ov199, ov272). Lo investigado:

- **No hay paralelismo**: `configure.py` usa un unico `subprocess.run` secuencial.
- El `gen_delinks.py` señalado **funciona bien lanzado a mano**, y tres `configure.py` seguidos
  salen limpios.
- ★ Con la salida ya visible (antes `gate.sh` la mandaba a /dev/null), el subproceso fallido
  **no imprime NADA**: ni traceback ni mensaje. Solo devuelve un codigo != 0. El unico `sys.exit`
  del script es el de "usage", que si imprime.

Un proceso que muere sin escribir en stderr no es una excepcion de Python: apunta a que **algo
externo lo mata** -- lo mas probable, el antivirus escaneando los `.c` recien escritos por
`dedupprop`/el porte justo antes. No es un problema del arbol ni del codigo generado.

**Que hacer**: repetir el gate. Si el segundo intento sale verde, era esto. Si alguna vez imprime
un mensaje real, ese mensaje es la pista buena.

⚠ **`gate.sh` puede fallar en `configure.py` de forma transitoria** (visto 2026-07-19: un
`gen_delinks.py` de ov124 salio con error y al repetirlo fue bien; probablemente un bloqueo de
fichero por el antivirus o por un `dedupprop` que acababa de escribir). **Repite el gate antes de
investigar**: si el segundo intento sale verde, era eso. Lo importante es que el script **aborto**
en vez de seguir hasta un `dsd check` enganado -- que es justo para lo que se escribio.

### Crear funciones THUMB: dos trampas encadenadas (2026-07-19)

1. **Limpia las code units ANTES de tocar TMode.** Si la direccion ya tiene instrucciones
   desensambladas (como ARM), `pc.setRegisterValue(...)` lanza
   `ContextChangeException: Context register change conflicts with one or more instructions`.
   Orden correcto: `listing.clearCodeUnits(a, end, False)` y **despues** el `setRegisterValue`.
2. **El script debe ser ASCII puro.** Un `⚠` en un comentario da
   `SyntaxError: Non-ASCII character ... but no encoding declared` en Jython, y el mensaje no
   menciona el comentario. (La regla ya estaba en SKILL.md para los heredocs; aplica igual a los
   scripts de Ghidra.)

## `tools/allcc.py` — probar TODAS las versiones de mwccarm

```
python tools/allcc.py <fichero.c> <func_name> [--thumb]
```

Compila el mismo `.c` con los **27** `mwccarm.exe` de `tools/mwccarm/` (1.2 sp*, 2.0 sp*, 3.0_136,
3.0_136_patched, 3.0_patch4, dsi 1.1..1.6sp2) y mide el residuo enmascarado contra el ROM.

**Cuando usarlo:** solo cuando el residuo es puro reparto de registros Y la busqueda sobre el
FUENTE ya esta agotada (ordenes de declaracion, formas del bucle, tipos, aridad). Antes de eso es
tiempo tirado: el fuente casi siempre tiene la respuesta.

**Que esperar (medido en func_ov043_020b5274, 2026-07-19):** las 1.2 dan tamaños distintos
(+20/+24) y **todas** las 2.0/3.0/dsi dan **exactamente el mismo residuo**. Eso confirma
`reference_mwcc_build_hunt`: la build de retail es 3.0 >= 140 y no la tenemos, asi que el eje del
compilador **no discrimina** — un empate que sobrevive a allcc.py es un empate de verdad y se
puede aparcar con la conciencia tranquila. Y al reves: si alguna build casara, se anota para ese
fichero en `config/arm9/file_compilers.json`, **nunca** se cambia la build por defecto del arbol.

## `poolmap.py` ahora resuelve los DESTINOS DE SALTO (2026-07-19)

Cada `beq`/`bne`/`blt`/`b` sale anotado con el offset relativo y **la instruccion que hay alli**:

```
  002c  bne  #0x2086f28    ; --> +0x6c  [ldr r1, [pc, #0x3c]]
```

Nacio de contar los fallos de una sesion: **nueve de ~40 eran destinos de salto mal leidos**, cero
eran empates del compilador. capstone imprime el destino como direccion ABSOLUTA y la columna de la
izquierda son offsets; traducir a ojo falla, y el diff que sale despues parece codegen -- que es
justo el diagnostico caro. `[FUERA DE ESTA FUNCION]` marca los saltos a otra funcion (tail calls).

**Uso obligatorio:** antes de escribir la primera llave, mira a que instruccion salta cada
condicional. Si el salto cae DENTRO del bloque, el codigo de despues NO va anidado.

## "db.NoTransactionException: Transaction has not been started" (2026-07-20)

Distinct from the routine `endTransaction` leak, and it means something different.

```
db.NoTransactionException: Transaction has not been started
  at ghidra.app.plugin.core.function.StackVariableAnalyzer.added(...)
  at ghidra.app.plugin.core.analysis.AutoAnalysisManager.startAnalysis(...)
  at ghidra.framework.plugintool.mgr.BackgroundCommandTask.run(...)   <-- ANOTHER THREAD
```

**We cause it.** `createFunction()` (in `DefineThumb.py`, and anything else that defines
functions) does not analyse inline -- it **queues auto-analysis as a background task**. That
task runs after the script returns. `CloseTxAndSave.py` then force-closes the leaked
transactions, so when the analyzer finally wakes there is no transaction and it throws on its
first write.

So the trace looks like a corrupted program or a dead bridge and is neither: it is the
transaction being pulled out from under work we queued. Nothing of ours is lost -- the
analyzer only adds stack-variable references -- and the renames, structs and prototypes from
the same batch are all intact (verified by read-back when it happened).

**Fix, already applied in `DefineThumb.py`: drain the analysis synchronously inside the
script's own transaction, before the transaction-closing block.**

```python
from ghidra.app.plugin.core.analysis import AutoAnalysisManager
AutoAnalysisManager.getAnalysisManager(p).startAnalysis(monitor)
```

Keeps the analyzer's work and kills the exception. Two traps found doing this:
- **`setAnalysisEnabled()` is NOT bound in this Jython runner** (`NameError`), even though it
  is a `GhidraScript` method. Do not reach for it; use `AutoAnalysisManager` directly.
- Non-ASCII in the script body breaks it -- the same rule SKILL.md already gives. A `⚠` in
  the comment had to become `!!`.

**Generalise it:** any script that force-closes transactions must first drain whatever it
queued. `CloseTxAndSave.py` is safe after tools that only rename/type (those write inline),
and unsafe after anything that defines functions, disassembles, or triggers re-analysis.

## ★★★ THE "No transaction is open" DIALOG -- cause and the correct script pattern

*(2026-07-20. The user reported it recurring; it was MY script pattern generating it.)*

**There are TWO different exceptions with this message and they mean different things. Read the
stack, not the message.**

| stack ends in | meaning |
|---|---|
| `GhidraScript.executeNormal` | the script force-closed its OWN transaction, so GhidraScript's `end()` found none. Cosmetic. |
| **`BackgroundCommandTask.run` / `ToolTaskManager.run`** | **auto-analysis queued by `disassemble()` / `createFunction()` woke up AFTER every transaction was force-closed.** This is the one that pops a dialog at the user. |

Nothing is lost either way -- the analyzer only adds stack-variable references -- but the second
one is alarming, it fires asynchronously (so it appears long after the script "succeeded"), and it
is entirely avoidable.

### The correct pattern for a Jython script

```python
#  ... do the work ...

# 1. DRAIN queued analysis while OUR transaction is still open
from ghidra.app.plugin.core.analysis import AutoAnalysisManager
AutoAnalysisManager.getAnalysisManager(p).startAnalysis(monitor)

# 2. that's it. Do NOT force-close. Do NOT save from inside the script.
```

Then save with a **separate** `mcp__ghidra__save_program` call. Verified: a script written this
way returns `SCRIPT COMPLETED SUCCESSFULLY` with **no exception at all**, and the following
`save_program` reports success with `isChanged` going to False.

The force-close block is ONLY for transactions leaked by the **MCP type/prototype tools**
(`create_struct`, `apply_data_type`, `set_function_prototype`, `modify_struct_field`), which
return an `endTransaction` error while succeeding. That is what `CloseTxAndSave.py` is for --
and it now **drains analysis BEFORE closing**, which is the whole fix.

⚠ Order is the entire point: drain first, close second. Roughly 160 legacy one-off scripts in
`~/ghidra_scripts/` still force-close without draining. They have already run, so they are not
worth patching, but **do not copy their postamble** -- copy the block above.

### Checking the program really is saved

`~/ghidra_scripts/VerifySaved.py` prints `isChanged`, the open transaction, and spot-checks a list
of known function names and struct sizes. Run it whenever a save is in doubt rather than trusting
a `SAVED_OK` line -- the same "read the console, not the status" rule applies to saving.

## mwccarm `#pragma`: the legal set, and the trap that makes an ignored one look inert

*(2026-07-25, while trying to break a one-slot scheduling residue in
`func_ov008_02068e68`. It did not break it, but the axis is now closed and the
mechanism is worth knowing.)*

**mwccarm silently ignores an unknown `#pragma` unless you pass `-w all`.** With the
project's normal flags, `#pragma scheduling off` compiles clean and changes nothing --
which reads exactly like "the pragma exists and had no effect". It does not exist.
Always probe first:

```bash
mwccarm -c <FLAGS> -w all -o /dev/null x.c 2>&1 | grep -i "illegal #pragma"
```

**CORRECTED 2026-07-26: THERE ARE 90 LEGAL PRAGMAS, NOT 29 -- AND DO NOT GUESS THE
LIST, EXTRACT IT FROM THE BINARY.** The old note here listed 29 names probed one at a
time. That list was a guess dressed up as a census: it only ever contained pragmas
somebody had already thought of, so every later session "closed the pragma axis"
against a fifth of it. The real table is inside mwccarm.exe -- pull the identifier
strings out and probe each one:

```python
data = open("tools/mwccarm/3.0_patch4/mwccarm.exe", "rb").read()
cand = sorted({s.decode() for s in re.findall(rb"[a-z_][a-z0-9_]{3,40}", data)})
# probe each with -w all and keep the ones that do not answer "illegal #pragma"
```

90 come back legal, and the ones the old list missed are exactly the ones you would
reach for when fighting codegen: `aggressive_hoisting`, `opt_serializeassignments`,
`opt_pulloutconstants`, `opt_moveinvariantsinaddressexpr`, `opt_repositioncode`,
`opt_defineargorder`, `opt_movepostops`, `opt_optimizecontrolflow`, `opt_scalarize`,
`opt_prelinearize`, `opt_treetransformation`, `opt_arithtransformation`,
`opt_rebuildconditionals`, `opt_rebuildlogicals`, `opt_rotateloops`,
`opt_reverseloops`, `opt_removetailrecursions`, `opt_decomposeaggregates`,
`opt_recomposeaggregates`, `opt_scalarizeliveranges`, `opt_marknonregtemps`,
`opt_obeyfunceffects`, `reg_class_allocs`, `side_effects`, `inlineforsize`,
`defer_codegen`, and ~40 more. The full list is regenerated by the snippet above.

The current list lives in `build/try/pragmas.txt` after running it.

**There is NO scheduling pragma and no register-allocation pragma.** `scheduling`,
`ARM_conditionalize`, `no_conditionalize`, `register_coloring`, `no_register_coloring`,
`volatileasm`, `instmgr`, `opt_pointer_analysis`, `opt_bool_constants` and
`exception_handling` are all illegal -- so instruction order and register colouring
cannot be steered from the command line or from a pragma at all. They are source-shape
problems, always.

Effects measured on a size-exact candidate (relative to the project's `-O4,p`): only
`opt_common_subs off`, `opt_lifetimes off`, `opt_propagation off`, `optimize_for_size on`,
`optimization_level <=2` and `explicit_zero_data on` change anything, and every one of
them makes a near-match worse or changes the size. The other 20 are bit-identical.
Pragmas are function-granular: scoping one to a single function gives exactly the same
result as putting it at the top of the file.

## ⚠ 2026-07-27 -- UN SCORER QUE CUENTA DIFERENCIAS DEBE DETECTAR EL FALLO DE COMPILACION

Un barrido sobre `func_ov011_0205b814` incluyo `__attribute__((always_inline))`, que mwccarm
**no soporta** (`illegal or unsupported __attribute__`). La compilacion aborta, `diffdis` no
imprime ni una linea de listado, y el scorer -- que contaba lineas marcadas con `<<<` --
devolvio **0 diferencias, o sea MATCH**. Trece variantes aparecieron en cabeza del ranking
como si estuvieran resueltas.

Es exactamente la misma clase de trampa que ya hay documentada en dos sitios de este skill:
un `asm_stubs` verifica trivialmente porque ES los bytes, y Jython reporta
`SCRIPT COMPLETED SUCCESSFULLY` mientras revienta por el limite de 64K. **El patron comun es
que la ausencia de salida se confunde con exito.**

Regla, para cualquier herramienta de medida que escribas: **el caso "no hay nada que comparar"
tiene que ser un error explicito, nunca el minimo de la metrica.** En la practica:

```python
if ("Errors caused tool to abort" in out or "compilacion fallo" in out
        or "orig" not in out):
    return 9999, "COMPILE FAILED"
```

Y el corolario de siempre: **si un barrido saca de golpe un puñado de ceros donde llevabas
cientos de compilaciones clavado en el mismo numero, sospecha de la herramienta antes que del
hallazgo.** Confirmalo con `verify_idx.py` sobre un solo fichero antes de creertelo.

Atributos que mwccarm 3.0 NO acepta (comprobado): `__attribute__((always_inline))`. Si acepta
`static inline`, `inline static`, `inline`, `static __inline`, `static __inline__` y `static`
-- las seis dan salida identica en esa funcion.

## Race: never run gen_delinks.py while a 306 gate is compiling (2026-08-01)

gen_delinks.py REWRITES `build/file_modes.json` (the thumb/arm map that tools/_run_mwcc.py:36
reads for every compile). Running it while a background `ninja` is mid-compile truncates the file
under the reader, and the concurrent MWCC wrapper dies with
`json.decoder.JSONDecodeError: Expecting value: line 1 column 1 (char 0)` on whatever ov002 files
it hit -> ninja stops, gate rc=1. This looks alarming (0 OK / N FAILED) but is NOT a regression or
corruption: file_modes.json is valid again once gen_delinks finishes. Fix: don't gen_delinks (or
otherwise write build/*.json) while a gate runs; if a gate fails with this exact JSONDecodeError,
just re-run it clean.
