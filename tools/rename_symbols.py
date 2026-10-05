#!/usr/bin/env python3
"""Rename function symbols in one pass, from a docs/renames table.

    python tools/rename_symbols.py docs/renames/<table>.tsv [--dry-run]

Each line of the table is `old_name<TAB>new_name<TAB>module` (`#` starts a comment). For every
row this updates the module's symbols.txt, renames the source file whose stem is the old name
(`git mv`), and replaces the old name as a whole word in the C/assembly sources, the headers and
docs/ (the tables under docs/renames are left alone). delinks.txt is not touched: run
tools/configure.py afterwards so gen_delinks regenerates it (it follows the table to carry DATA
claims over to the new file names).

The table must be committed under docs/renames/ before configure runs, and the Ghidra project
renamed to match.
"""
import argparse
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import srctree  # noqa: E402

TEXT_DIRS = ('src', 'libs', 'include', 'docs')
TEXT_EXTS = ('.c', '.cpp', '.h', '.s', '.inc', '.md')


def load_table(path):
    rows = []
    for line in open(path, encoding='utf-8'):
        line = line.split('#', 1)[0].rstrip('\n')
        if not line.strip():
            continue
        old, new, module = (f.strip() for f in line.split('\t'))
        rows.append((old, new, module))
    olds = [r[0] for r in rows]
    news = [r[1] for r in rows]
    if len(set(olds)) != len(olds) or len(set(news)) != len(news):
        sys.exit('duplicate names in the table')
    return rows


def symbols_file(module):
    if module == 'main':
        return os.path.join(ROOT, 'config', 'arm9', 'symbols.txt')
    if module in ('itcm', 'dtcm'):
        return os.path.join(ROOT, 'config', 'arm9', module, 'symbols.txt')
    return os.path.join(ROOT, 'config', 'arm9', 'overlays', module, 'symbols.txt')


def text_files():
    for top in TEXT_DIRS:
        for dirpath, dirnames, filenames in os.walk(os.path.join(ROOT, top)):
            rel = os.path.relpath(dirpath, ROOT).replace(os.sep, '/')
            if rel.startswith('docs/renames'):
                continue
            for name in filenames:
                if name.endswith(TEXT_EXTS):
                    yield os.path.join(dirpath, name)


def rename_in_indexes(mapping):
    """Carry the renames into the verifiers' ground truth.

    build/func_index.json (verify_idx) and build/data_index.json (verify_data, and through it
    refresh_data_receipts) key symbols and relocation targets by name. A DATA table whose
    relocations point at a renamed function would otherwise fail its receipt: the new name
    resolves to the address, the old one in the index no longer resolves at all."""
    import json
    for name in ('func_index.json', 'data_index.json'):
        path = os.path.join(ROOT, 'build', name)
        if not os.path.exists(path):
            continue
        index = json.load(open(path))
        renamed = {}
        for sym, entry in index.items():
            entry['relocs'] = [[off, mapping.get(target, target)] for off, target in entry.get('relocs', [])]
            renamed[mapping.get(sym, sym)] = entry
        json.dump(renamed, open(path, 'w'))


def rename_in_data_receipts(mapping):
    """build/data_receipts/<symbol>.json proves one DATA symbol and names it inside; a renamed data
    symbol takes its receipt along (tools/refresh_data_receipts.py --fix then re-verifies the
    source, whose hash the rename changed)."""
    import json
    folder = os.path.join(ROOT, 'build', 'data_receipts')
    if not os.path.isdir(folder):
        return
    for old, new in mapping.items():
        src = os.path.join(folder, old + '.json')
        if not os.path.exists(src):
            continue
        receipt = json.load(open(src, encoding='utf-8'))
        receipt['symbol'] = new
        open(os.path.join(folder, new + '.json'), 'w', encoding='utf-8').write(json.dumps(receipt, indent=2) + '\n')
        os.remove(src)


def rename_in_report_asm(mapping, moves):
    """config/arm9/report_asm_matches.json keys its attested non-C sources by function name and
    records each one's path; carry both over (tools/verify_report_asm.py refreshes the hashes)."""
    import json
    path = os.path.join(ROOT, 'config', 'arm9', 'report_asm_matches.json')
    if not os.path.exists(path):
        return
    manifest = json.load(open(path, encoding='utf-8'))
    moved = {os.path.relpath(s, ROOT).replace(os.sep, '/'): os.path.relpath(d, ROOT).replace(os.sep, '/')
             for s, d in moves}
    functions = {}
    changed = False
    for name, entry in manifest['functions'].items():
        if entry['source'] in moved or name in mapping:
            changed = True
        entry['source'] = moved.get(entry['source'], entry['source'])
        functions[mapping.get(name, name)] = entry
    if changed:
        manifest['functions'] = functions
        open(path, 'w', encoding='utf-8', newline='\n').write(json.dumps(manifest, indent=2, sort_keys=True) + '\n')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('table')
    ap.add_argument('--dry-run', action='store_true')
    args = ap.parse_args()
    rows = load_table(args.table)
    mapping = {old: new for old, new, _ in rows}
    word = re.compile(r'\b(' + '|'.join(re.escape(o) for o in sorted(mapping, key=len, reverse=True)) + r')\b')

    # symbols.txt: the name is the first field of its line
    for old, new, module in rows:
        path = symbols_file(module)
        lines = open(path, encoding='utf-8').read().split('\n')
        hits = [i for i, l in enumerate(lines) if l.split(' ', 1)[0] == old]
        if len(hits) != 1:
            sys.exit('%s: %d definitions of %s' % (path, len(hits), old))
        # a name the table itself renames away is free (swaps and chains apply in one pass)
        clash = [l for l in lines if l.split(' ', 1)[0] == new and new not in mapping]
        if clash:
            sys.exit('%s: %s already defined' % (path, new))
        lines[hits[0]] = new + lines[hits[0]][len(old):]
        if not args.dry_run:
            open(path, 'w', encoding='utf-8', newline='').write('\n'.join(lines))

    # source files named after the symbol (nonmatching/ and asm_stubs/ copies included)
    by_stem = {}
    for top in ('src', 'libs'):
        for dirpath, dirnames, filenames in os.walk(os.path.join(ROOT, top)):
            for name in filenames:
                stem, ext = os.path.splitext(name)
                if ext in srctree.SOURCE_SUFFIXES and stem in mapping:
                    by_stem.setdefault(stem, []).append(os.path.join(dirpath, name))
    moves = []
    for old, new, _ in rows:
        for p in by_stem.get(old, []):
            dst = os.path.join(os.path.dirname(p), new + os.path.splitext(p)[1])
            moves.append((p, dst))
    for src, dst in moves:
        print('git mv', os.path.relpath(src, ROOT), '->', os.path.basename(dst))
        if not args.dry_run:
            subprocess.run(['git', 'mv', src, dst], cwd=ROOT, check=True)
    if not args.dry_run:
        rename_in_report_asm(mapping, moves)

    # whole-word references
    changed = 0
    for path in text_files():
        raw = open(path, 'rb').read()
        text = raw.decode('utf-8', 'surrogateescape')
        new_text = word.sub(lambda m: mapping[m.group(1)], text)
        if new_text != text:
            changed += 1
            if not args.dry_run:
                open(path, 'wb').write(new_text.encode('utf-8', 'surrogateescape'))
    if not args.dry_run:
        rename_in_indexes(mapping)
        rename_in_data_receipts(mapping)
    print('renamed %d symbols, moved %d files, rewrote %d files%s'
          % (len(rows), len(moves), changed, ' (dry run)' if args.dry_run else ''))


if __name__ == '__main__':
    main()
