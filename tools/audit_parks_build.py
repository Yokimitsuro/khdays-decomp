#!/usr/bin/env python3
"""Check that every parked file still COMPILES.

A file in nonmatching/ is not built by the ROM, so nothing notices when it stops
compiling -- and the whole reason to park a function with a write-up is that a later
session can re-test it.  One that will not compile is a dead end wearing the costume of
a lead: the next person runs verify_idx, gets a compiler error instead of a diff, and
has to reconstruct the source before they can even start.

func_ov181_020cd1e0.c sat broken in the tree for a day.  Its note listed the type
combinations it had tried, written as pointer types separated by slashes, and one of
those sequences accidentally spelled a comment terminator -- so the block comment closed
early and the typedef below it was parsed as code.  Nothing flagged it because parked
files are outside the build.

Usage:
    python tools/audit_parks_build.py [--verbose]
"""
import io
import os
import re
import subprocess
import sys

MODE = re.compile(r'kind:function\((arm|thumb)')


def mode_of(name):
    """Look the function's instruction set up in the symbol tables, if it is there."""
    for root, _dirs, files in os.walk('config'):
        for f in files:
            if f != 'symbols.txt':
                continue
            path = os.path.join(root, f)
            try:
                text = io.open(path, encoding='utf-8', errors='replace').read()
            except OSError:
                continue
            for line in text.splitlines():
                if line.startswith(name + ' '):
                    m = MODE.search(line)
                    if m:
                        return m.group(1)
    return None


def main():
    verbose = '--verbose' in sys.argv
    parked = []
    for root, _dirs, files in os.walk('src'):
        if 'nonmatching' not in root:
            continue
        for f in files:
            if f.endswith('.c'):
                parked.append(os.path.join(root, f))

    broken = []
    for path in sorted(parked):
        name = os.path.basename(path)[:-2]
        # try both modes: an ARM-only attempt on a THUMB function reports a size gap,
        # not a compile error, so either result proves the file builds
        args = ['python', 'tools/verify_idx.py', path, name]
        result = subprocess.run(args, capture_output=True, text=True)
        out = result.stdout + result.stderr
        if 'compilacion fallo' in out or 'Errors caused tool to abort' in out:
            result = subprocess.run(args + ['--thumb'], capture_output=True, text=True)
            out = result.stdout + result.stderr
            if 'compilacion fallo' in out or 'Errors caused tool to abort' in out:
                first = ''
                for line in out.splitlines():
                    if 'Error:' in line or '#   ' in line:
                        first = line.strip()
                        break
                broken.append((path.replace(os.sep, '/'), first))
                print('BROKEN %s\n       %s' % (path.replace(os.sep, '/'), first))
                continue
        if verbose:
            print('ok     %s' % path.replace(os.sep, '/'))

    print('%d parked files, %d that do not compile' % (len(parked), len(broken)))
    return 1 if broken else 0


if __name__ == '__main__':
    sys.exit(main())
