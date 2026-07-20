#!/usr/bin/env python3
"""Catch functions named into a family they do not belong to.

Bulk Ghidra renames are written as tables of (overlay, address, name), and a
mis-copied address is invisible from inside the table: the name looks right, it
resolves to a real function, and nothing complains.  It only shows up as a symbol
whose body has nothing to do with its name.

The check is cheap.  Group every symbol by its name stem -- the name with the
Ov<NNN>_ prefix and any trailing digit stripped -- and compare the shapes of the
functions under it.  Members of a real shape family are byte-identical modulo
relocations and therefore identical in size; an outlier is a misnamed function.

Found func_ov166_020cc624 (312 bytes) sitting among ten 72-byte members of the
c5c0 spawn family, from the 2026-07-18 batch.  That was the batch's only bad row.

Usage:
    python tools/audit_name_shapes.py                     # audit ~/ghidra_scripts
    python tools/audit_name_shapes.py <script.py> [...]   # audit specific tables
"""
import ast
import collections
import glob
import json
import os
import re
import sys

ROW = re.compile(r'\("(ov\d+|arm9(?:_ov\d+)?)",\s*"([0-9a-fA-F]{6,8})",\s*"([A-Za-z_][\w]*)"')
STEM = re.compile(r'^(?:Ov\d+_)?(.*?)\d*$')


def masked(entry):
    """Function bytes with every relocated word zeroed, so twins compare equal."""
    body = bytearray.fromhex(entry['hex'])
    relocs = entry['relocs']
    if isinstance(relocs, str):
        relocs = ast.literal_eval(relocs)
    for offset, _symbol in relocs:
        for i in range(4):
            if offset + i < len(body):
                body[offset + i] = 0
    return bytes(body)


def main(argv):
    index = json.load(open('build/func_index.json'))
    scripts = argv[1:]
    if not scripts:
        scripts = glob.glob(os.path.expanduser('~/ghidra_scripts/*.py'))

    groups = collections.defaultdict(list)
    for path in scripts:
        try:
            text = open(path, encoding='utf-8', errors='replace').read()
        except OSError:
            continue
        for space, address, name in ROW.findall(text):
            overlay = space.replace('arm9_', '') or 'arm9'
            key = 'func_%s_%s' % (overlay, address.lower())
            entry = index.get(key)
            if entry is None:
                continue
            stem = STEM.match(name).group(1)
            groups[stem].append((os.path.basename(path), key, int(entry['size']), masked(entry)))

    suspects = 0
    for stem, members in sorted(groups.items()):
        if len(members) < 3:
            continue                      # too few to establish a majority shape
        sizes = collections.Counter(size for _, _, size, _ in members)
        if len(sizes) == 1:
            continue
        majority, count = sizes.most_common(1)[0]
        for script, key, size, _ in members:
            if size != majority:
                suspects += 1
                print('%s: %s is %d bytes but %d of %d %s* members are %d'
                      % (script, key, size, count, len(members), stem, majority))

    print('%d suspect%s across %d name stems'
          % (suspects, '' if suspects == 1 else 's', len(groups)))
    return 1 if suspects else 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
