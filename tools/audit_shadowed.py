#!/usr/bin/env python3
"""Find functions that have real C in auto/ or calls/ AND an asm_stubs/ twin.

The stub wins the last-wins sort, so such a function is (a) miscounted as asm_stub_matched and
(b) BUILT FROM THE ASM BLOB while finished C sits next to it unused. On 2026-07-17 a sweep found
50 of these; 46 verified and their stubs were deleted (+46 C / -46 ASM, gate still 306/0). No new
decompilation -- it was all already done and simply not counted.

They accumulate after bulk `dedupprop.py --write` runs, so re-run this after any big propagation.
The tell in progress.py is C moving by less than you added.

Usage:  python tools/audit_shadowed.py            # report only
        python tools/audit_shadowed.py --verify   # also compile-check each real C (slow, exact)
        python tools/audit_shadowed.py --fix      # verify, then delete stubs whose C matches

--fix NEVER deletes a stub whose real C does not verify: in that case the .c is the broken one and
the stub is what is holding the build together. Those are reported so you can move the .c to
nonmatching/ by hand (a non-matching .c in auto/ or calls/ violates the project's hard rule).

ALWAYS re-run the full 306 gate after --fix; it changes what the ROM is built from.
"""
import os
import subprocess
import sys


# NOT just src/: libs/{nitro,msl}/... carries its own asm_stubs/ + calls/ + auto/ trees and is
# counted the same way. Scanning only src/ reported "0 shadowed" while 74 SND veneers sat shadowed
# under libs/nitro/snd/ (2026-07-17).
TREES = ('src', 'libs')


def scan():
    real, stub = {}, {}
    for tree in TREES:
      if not os.path.isdir(tree):
        continue
      for root, _dirs, files in os.walk(tree):
        for f in files:
            if not f.endswith('.c'):
                continue
            name = f[:-2]
            path = os.path.join(root, f).replace(os.sep, '/')
            if 'asm_stubs' in root:
                stub[name] = path
            elif 'nonmatching' not in root:
                real[name] = path
    return real, stub


def verify(path, name):
    """Try ARM, then THUMB. Verifying a THUMB function as ARM gives a meaningless size gap
    (e.g. '152 != 104'), which reads exactly like broken C -- this cost 4 matching functions
    a wrong trip to nonmatching/ on 2026-07-17 before dedupprop (which tries both) caught it."""
    for extra in ([], ['--thumb']):
        r = subprocess.run([sys.executable, 'tools/verify_idx.py', path, name] + extra,
                           capture_output=True, text=True)
        out = (r.stdout + r.stderr).strip().splitlines()
        line = out[0] if out else '?'
        if 'MATCH' in line:
            return line + ('  (thumb)' if extra else '')
    return line


def main():
    do_verify = '--verify' in sys.argv or '--fix' in sys.argv
    do_fix = '--fix' in sys.argv

    real, stub = scan()
    both = sorted(set(real) & set(stub))
    print('shadowed functions (real C + asm_stubs twin): %d' % len(both))
    if not both:
        return
    if not do_verify:
        for n in both:
            print('   ' + stub[n])
        print('\nre-run with --verify to compile-check, or --fix to delete the safe ones')
        return

    ok, bad = [], []
    for n in both:
        line = verify(real[n], n)
        (ok if 'MATCH' in line else bad).append((n, line))

    print('  real C verifies (stub safe to delete): %d' % len(ok))
    print('  real C does NOT verify (stub is load-bearing): %d' % len(bad))
    for n, line in bad:
        print('     BAD %-26s %s' % (n, line[:60]))
        print('         -> move %s to nonmatching/ and keep the stub' % real[n])

    if do_fix:
        for n, _ in ok:
            p = stub[n]
            for q in (p, p + '.o'):
                if os.path.exists(q):
                    os.remove(q)
        print('\ndeleted %d stubs. NOW RE-RUN THE FULL 306 GATE.' % len(ok))


if __name__ == '__main__':
    main()
