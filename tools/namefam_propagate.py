#!/usr/bin/env python3
"""Propagate Ghidra names across byte-identical shape families.

If `func_ov228_020d01e8` is named `Ov228_SteerToTarget` and `func_ov229_020d0154` is byte-identical
to it modulo relocs, the twin is the same routine compiled into another overlay -- it has earned the
same name. That is the same equivalence `dedupprop.py` already trusts to propagate the *code*; this
propagates the *semantics*, which the project's hard rule says is the half that counts.

The name is rewritten so its overlay prefix follows the member: `Ov228_Foo` -> `Ov229_Foo`.
A family whose named members disagree on the base name is skipped and reported -- that is a real
signal (either a bad name or a coincidental shape), not something to paper over.

Ghidra must be open with days.nds, bridge on 127.0.0.1:8089.

Usage:  python tools/namefam_propagate.py            # dry run: what would be named
        python tools/namefam_propagate.py --write    # emit + run the Jython, then read back
"""
import glob
import http.client
import json
import os
import re
import sys
import urllib.parse
from collections import defaultdict

PORT = 8089
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def get(endpoint, params=None, timeout=180):
    q = '?' + urllib.parse.urlencode(params) if params else ''
    c = http.client.HTTPConnection('127.0.0.1', PORT, timeout=timeout)
    c.request('GET', '/' + endpoint + q)
    r = c.getresponse()
    out = r.read().decode('utf-8', 'replace')
    c.close()
    return out


def ghidra_names():
    out = get('list_functions', {'limit': 30000})
    names = {}
    for line in out.splitlines():
        if ' at ' not in line:
            continue
        name, _, addr = line.rpartition(' at ')
        names[addr.strip().lower()] = name.strip()
    return names


def key_for(func):
    """func_ov228_020d01e8 -> arm9_ov228::020d01e8 ; func_0201a124 -> 0201a124"""
    m = re.search(r'([0-9a-fA-F]{8})$', func)
    if not m:
        return None
    addr = m.group(1).lower()
    ov = re.match(r'func_(ov\d+)_', func)
    return 'arm9_%s::%s' % (ov.group(1), addr) if ov else addr


def unit_of(func):
    m = re.match(r'func_(ov\d+)_', func)
    return m.group(1) if m else 'main'


def matched_c():
    """func name -> path, real byte-exact C only (never asm_stubs / nonmatching)."""
    out = {}
    for root, _dirs, files in os.walk(os.path.join(ROOT, 'src')):
        if 'nonmatching' in root or 'asm_stubs' in root:
            continue
        for f in files:
            if f.endswith('.c') and f.startswith('func_'):
                out[f[:-2]] = os.path.join(root, f).replace(os.sep, '/')
    return out


def canon(f):
    """Masked hex: reloc operands zeroed, so the same routine in two overlays collides."""
    b = bytearray.fromhex(f['hex'])
    for off, _s in f['relocs']:
        for j in range(4):
            if off + j < len(b):
                b[off + j] = 0
    return bytes(b).hex()


# `Ov228_SteerToTarget` / `ov228_SteerToTarget` -> ('Ov', '228', 'SteerToTarget')
OVNAME = re.compile(r'^(Ov|ov)(\d{3})_(.+)$')

# Two ways a propagated name is worse than no name at all, both seen in the first dry run:
#
#  1. The name embeds the REP's address (`SetMode95d0`, `Fwd_020521a0`, `CleanupEntry_83f4`).
#     Retargeting keeps the digits, so `Ov008_SetMode95d0` points at an ov025 address -- a name
#     that actively lies. These are placeholders anyway; the twin deserves better, not a copy.
#  2. The name asserts a SCENE the twin is not in. `func_ov006_0204fa88` is `MissionPollKeys`
#     because ov006 IS Mission-Mode character select; its byte-identical twin in ov008 is the
#     same *routine*, not the same *screen*. The skill's own scene table exists because ~23
#     symbols were once misnamed exactly this way. Structure propagates; scene identity does not.
ADDR_IN_NAME = re.compile(r'[0-9a-fA-F]{4,8}$')
SCENE_WORDS = ('mission', 'title', 'multiplayer', 'mlt', 'panel', 'moogle', 'shop')

# One definition of "this is not a name", shared with the tool that counts the debt -- see the
# comment on PLACEHOLDER there. Two copies disagreed by 17 functions once; never again.
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from audit_unnamed import PLACEHOLDER  # noqa: E402


def base_name(gname):
    m = OVNAME.match(gname)
    return m.group(3) if m else gname


def name_is_propagable(base, src_unit, dst_unit):
    """Reject names that would be wrong -- not merely ugly -- once moved to another overlay."""
    if PLACEHOLDER.match(base):
        return 'placeholder'
    if ADDR_IN_NAME.search(base):
        return 'embeds an address'
    if OVNAME.match(base) or re.search(r'_Ov\d+$', base):
        return 'already overlay-qualified'
    if src_unit != dst_unit:
        low = base.lower()
        for w in SCENE_WORDS:
            if w in low:
                return 'asserts scene identity (%s)' % w
    return None


def retarget(gname, unit):
    """Rewrite a name for another unit. None = this name cannot be moved there.

    Two name shapes, and mishandling the second one made this tool silently blind:
      - `Ov228_Foo` spells its overlay INTO the name, so the digits must follow the member.
        There is no sensible `Ov228_Foo` in main, so refuse that move.
      - A bare `TickTagTrackerNodes` carries no unit at all, so it moves VERBATIM. That is not
        a fallback -- it is this codebase's dominant convention for a cross-overlay family:
        `TickTagTrackerNodes` and `BuildTagTrackerNode` are each spelled identically in EIGHT
        overlays, because Ghidra namespaces them by address space (`arm9_ov008::` vs
        `arm9_ov025::`), so the same bare name in two overlays is unambiguous and correct.

    Returning None for the bare case (as this did until 2026-07-17) meant every family whose rep
    had a plain semantic name was dropped by the `if nn is None: continue` in main() -- not
    rejected, not counted, just gone. It hid 66 propagable twins behind the reassuring line
    "0 propagable". The negative-result rule in SKILL.md, exactly: state the positive form
    (`SetTagTrackerNodeArmed` moving to its ov002 twin) and check the search could express it.
    This one could not.
    """
    m = OVNAME.match(gname)
    if not m:
        return gname
    if unit == 'main':
        return None
    return '%s%s_%s' % (m.group(1), unit[2:], m.group(3))


def main():
    write = '--write' in sys.argv
    try:
        gn = ghidra_names()
    except OSError as e:
        print('cannot reach the GhidraMCP bridge on 127.0.0.1:%d (%s)' % (PORT, e))
        return 1

    idx = json.load(open(os.path.join(ROOT, 'build', 'func_index.json')))
    have_c = matched_c()

    fams = defaultdict(list)
    for func in have_c:
        f = idx.get(func)
        if not f:
            continue
        fams[canon(f)].append(func)

    plan = []          # (func, unit, addr, newname, source_func)
    conflicts = []
    rejected = defaultdict(list)
    singles = 0
    for _c, members in sorted(fams.items()):
        if len(members) < 2:
            singles += 1
            continue
        named = []
        unnamed = []
        for func in members:
            k = key_for(func)
            cur = gn.get(k) if k else None
            if cur is None:
                continue                       # no Ghidra function at all -- not our job here
            # A placeholder is a rename TARGET, not a source: `ov002_helper_5ef08` is no more a
            # name than FUN_ is, so a family's real name should overwrite it.
            is_debt = cur.startswith('FUN_') or PLACEHOLDER.match(base_name(cur))
            (unnamed if is_debt else named).append((func, cur))
        if not named or not unnamed:
            continue
        bases = {base_name(cur) for _f, cur in named}
        if len(bases) > 1:
            conflicts.append((sorted(bases), [f for f, _ in named]))
            continue
        src_func, src_name = named[0]
        base = base_name(src_name)
        for func, _cur in unnamed:
            dst_unit = unit_of(func)
            nn = retarget(src_name, dst_unit)
            if nn is None:
                continue                       # unprefixed name (main, SDK) -- don't guess
            why = name_is_propagable(base, unit_of(src_func), dst_unit)
            if why:
                rejected[why].append((func, src_name))
                continue
            plan.append((func, dst_unit, re.search(r'([0-9a-f]{8})$', func).group(1), nn, src_func))

    # Two byte-identical functions in the SAME overlay want the same name. Ghidra would either
    # throw or silently create an ambiguous pair; neither is a name worth having. Report and skip.
    #
    # Seeded with every real name ALREADY in the program, per unit -- not just with the renames
    # planned in this run. Comparing the plan only against itself missed the case where a
    # destination collides with the family's own REP: `func_0203c634` is already `SetIndexedSlot`
    # in main, and its byte-identical main twin `func_02011f88` was planned to become
    # `SetIndexedSlot` too, which is the exact "duplicated routine, needs a human" this check
    # exists to refuse. Bare names made that common (a prefixed `Ov008_Foo` can only retarget
    # into a different overlay, so it hid the gap); checking against the program catches the
    # cross-family case as well, and cannot block a legitimate move -- the destination is
    # unnamed by construction.
    seen_name = {}
    for k, cur in gn.items():
        if cur.startswith('FUN_') or PLACEHOLDER.match(base_name(cur)):
            continue
        m = re.match(r'arm9_(ov\d+)::', k)
        seen_name[(m.group(1) if m else 'main', cur)] = '(already in the program)'
    collided = []
    keep = []
    for item in plan:
        func, unit, _addr, nn, _src = item
        prev = seen_name.get((unit, nn))
        if prev:
            collided.append((func, prev, nn))
            continue
        seen_name[(unit, nn)] = func
        keep.append(item)
    plan = keep

    print('byte-identical families with C: %d (+%d singletons)' % (len(fams) - singles, singles))
    print('unnamed twins of an already-named function: %d propagable' % len(plan))
    if collided:
        print('\n%d skipped: same name twice in one overlay (duplicated routine -- needs a human):'
              % len(collided))
        for func, prev, nn in collided[:6]:
            print('   %-28s collides with %-28s as %s' % (func, prev, nn))
    if rejected:
        print('\nrejected (the rep\'s own name is not safe to move):')
        for why, items in sorted(rejected.items(), key=lambda kv: -len(kv[1])):
            print('   %-32s %4d   e.g. %s <- %s' % (why, len(items), items[0][0], items[0][1]))
    if conflicts:
        print('\n%d families whose named members DISAGREE (skipped -- worth a look):' % len(conflicts))
        for bases, funcs in conflicts[:10]:
            print('   %s  <- %s' % (' | '.join(bases), ', '.join(funcs[:4])))

    by_unit = defaultdict(int)
    for _f, u, _a, _n, _s in plan:
        by_unit[u] += 1
    if plan:
        print('\nby unit:')
        for u, n in sorted(by_unit.items(), key=lambda kv: -kv[1])[:15]:
            print('   %-8s %d' % (u, n))
        print('\nsample:')
        for f, _u, _a, nn, src in plan[:12]:
            print('   %-28s -> %-34s (from %s)' % (f, nn, src))

    if not write:
        print('\ndry run. re-run with --write to apply.')
        return 0
    if not plan:
        return 0

    L = ["from ghidra.program.model.symbol import SourceType",
         "p=currentProgram; fm=p.getFunctionManager(); af=p.getAddressFactory()",
         "DATA=["]
    for _f, unit, addr, nn, _src in plan:
        L.append('  ("arm9_%s","%s","%s"),' % (unit, addr, nn))
    L += ["]", "ok=0; miss=[]; err=[]",
          "for sp,ad,nm in DATA:",
          "    try:",
          "        a=af.getAddressSpace(sp).getAddress(long(int(ad,16)))",
          "        f=fm.getFunctionAt(a)",
          "        if f is None: miss.append(sp+':'+ad); continue",
          "        f.setName(nm, SourceType.USER_DEFINED); ok+=1",
          "    except:",
          "        err.append(sp+':'+ad)",
          "print('named=%d missing=%d err=%d'%(ok,len(miss),len(err)))",
          "print('MISS='+str(miss[:20]))",
          "print('ERR='+str(err[:20]))",
          # A leaked transaction makes every later Save fail; close ours the documented way.
          "ti=p.getCurrentTransactionInfo()",
          "if ti is not None:",
          "    lf=ti.getClass().getDeclaredField('list'); lf.setAccessible(True); Ls=lf.get(ti)",
          "    bf=ti.getClass().getDeclaredField('baseId'); bf.setAccessible(True); base=bf.get(ti)",
          "    for i in range(Ls.size()):",
          "        e=Ls.get(i); s=e.getClass().getDeclaredField('status'); s.setAccessible(True)",
          "        if str(s.get(e))=='NOT_DONE':",
          "            try: p.endTransaction(base+i,True)",
          "            except: pass",
          "try: p.getDomainFile().save(monitor); print('SAVED_OK')",
          "except:",
          "    import sys; print('SAVE_FAIL '+str(sys.exc_info()[1]))"]
    gsdir = os.environ.get('GHIDRA_SCRIPTS_DIR', os.path.expanduser('~/ghidra_scripts'))
    if not os.path.isdir(gsdir):
        os.makedirs(gsdir)
    path = os.path.join(gsdir, 'NameFamProp.py')
    open(path, 'w', newline='\n').write('\n'.join(L) + '\n')
    print('\nwrote %s (%d renames) -- run it with run_ghidra_script, then READ THE RENAMES BACK.'
          % (path, len(plan)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
