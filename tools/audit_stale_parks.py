#!/usr/bin/env python3
"""Find nonmatching/ files whose function ALSO has real C in calls/ or auto/.

A park that survives its own match is worse than clutter: its write-up is a
confident, measured argument for why the function cannot be matched, sitting one
directory away from the file that matches it. That is exactly the kind of note
that persuades the next session not to look.

The one found on 2026-07-22 claimed "no natural C form reproduces the split
(constant*constant always folds; tried raw *0x30, *0x4030, (idx<<1)*0x2018 ...)"
while src/overlays/ov000/calls/func_ov000_02054e48.c matched using precisely
`(data[1] << 1) * 0x2018`. Ten more were sitting alongside it, four of them left
behind by hand-offs earlier the same day.

    python tools/audit_stale_parks.py            # list them
    python tools/audit_stale_parks.py --verify   # ... and compile-check each twin
    python tools/audit_stale_parks.py --fix      # delete the parks whose twin MATCHes

--fix never deletes a park unless the real file verifies byte-exact first, in
both ARM and THUMB, so a park can only be removed on evidence.
"""
import glob
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
VERIFY = os.path.join(ROOT, "tools", "verify_idx.py")


def find_stale():
    out = []
    pattern = os.path.join(ROOT, "src", "**", "nonmatching", "*.c")
    for park in sorted(glob.glob(pattern, recursive=True)):
        name = os.path.basename(park)[:-2]
        unit = os.path.dirname(os.path.dirname(park))
        for sub in ("calls", "auto"):
            real = os.path.join(unit, sub, name + ".c")
            if os.path.exists(real):
                out.append((park, real, name))
                break
    return out


def verify(real, name):
    """MATCH in either mode -- never trust a single-mode result (see SKILL.md)."""
    for args in ([], ["--thumb"]):
        r = subprocess.run([sys.executable, VERIFY, real, name] + args,
                           capture_output=True, text=True)
        if ">>> MATCH" in r.stdout:
            return r.stdout.strip().splitlines()[-1]
    return None


def main():
    do_verify = "--verify" in sys.argv or "--fix" in sys.argv
    do_fix = "--fix" in sys.argv

    stale = find_stale()
    if not stale:
        print("no stale parks: every nonmatching/ file is the only C for its function")
        return

    removed = kept = 0
    for park, real, name in stale:
        rel = os.path.relpath(park, ROOT).replace(os.sep, "/")
        if not do_verify:
            print("STALE %s" % rel)
            continue
        res = verify(real, name)
        if res is None:
            print("KEEP  %s  (twin does NOT verify -- investigate, do not delete)" % rel)
            kept += 1
            continue
        print("STALE %s  (twin %s)" % (rel, res))
        if do_fix:
            os.remove(park)
            removed += 1

    print("\n%d stale park(s)%s" % (len(stale),
                                    "; removed %d, kept %d" % (removed, kept) if do_verify else ""))


if __name__ == "__main__":
    main()
