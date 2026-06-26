#!/usr/bin/env python3
"""Aplica sdk/build/names.json al config dsd (symbols.txt) y a src/auto, src/calls.

Reglas:
  - Solo renombra func_X cuyo nombre SDK es unico, O el func es >16 bytes
    o tiene relocs (=> identificacion inequivoca).
  - Duplicados grandes: primero (por addr) usa nombre limpio, resto sufijo _0xADDR.
  - Stubs minusculos ambiguos (≤16 bytes y sin relocs y nombre compartido): NO se tocan.
  - src/auto/<func>.c y src/calls/<func>.c: archivo se renombra y se reescribe
    la firma + todas las referencias internas. Tambien se reescriben referencias
    en OTROS .c (extern decls y call sites).
  - symbols.txt: la primera columna (nombre) se sustituye cuando la addr matchea.

Uso: python sdk/apply_names.py            # apply
     python sdk/apply_names.py --dry      # solo reportar
"""
import json, os, re, sys, shutil
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NAMES = json.load(open(os.path.join(ROOT, "sdk", "build", "names.json")))
INDEX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
DRY = "--dry" in sys.argv

FUNC_RE = re.compile(r"func_(?:ov\d+_)?[0-9a-f]{8}")


def parse_func_key(k):
    """func_02003c54 -> (None, 0x02003c54);   func_ov025_020b07dc -> ('ov025', 0x020b07dc)"""
    m = re.match(r"^func_(ov\d+_)?([0-9a-f]{8})$", k)
    if not m: return None, None
    ov = m.group(1).rstrip("_") if m.group(1) else None
    return ov, int(m.group(2), 16)


def build_rename_map():
    """func_X (clave names.json) -> nombre final unico para symbols.txt y src/."""
    counts = Counter(NAMES.values())
    # group func_X by SDK name to apply suffix policy per group
    by_name = defaultdict(list)
    for k, v in NAMES.items():
        ov, addr = parse_func_key(k)
        if addr is None: continue
        info = INDEX.get(k, {}); sz = info.get("size", 0); rl = info.get("relocs", [])
        ambiguous = counts[v] > 1
        tiny = sz <= 16 and not rl
        if ambiguous and tiny:
            continue  # skip: tiny generic stub matched to many names, leave func_X
        by_name[v].append((addr, k))
    out = {}
    for sdk_name, lst in by_name.items():
        lst.sort()  # by addr ascending
        if len(lst) == 1:
            out[lst[0][1]] = sdk_name
        else:
            out[lst[0][1]] = sdk_name
            for addr, k in lst[1:]:
                out[k] = "%s_0x%08x" % (sdk_name, addr)
    return out


def rewrite_symbols_txt(path, addr2name):
    with open(path) as f: lines = f.readlines()
    changed = 0
    for i, ln in enumerate(lines):
        m = re.match(r"^(\S+)\s+(.*\baddr:0x([0-9a-fA-F]+)\b.*)$", ln.rstrip())
        if not m: continue
        old = m.group(1); rest = m.group(2); addr = int(m.group(3), 16)
        if not old.startswith("func_"): continue
        new = addr2name.get(addr)
        if not new or new == old: continue
        lines[i] = "%s %s\n" % (new, rest)
        changed += 1
    if changed and not DRY:
        with open(path, "w") as f: f.writelines(lines)
    return changed


def main():
    rename = build_rename_map()
    print("rename map size:", len(rename))
    print("samples:")
    for k, v in list(rename.items())[:5]: print("  %s -> %s" % (k, v))

    # build addr -> final name (and an overall "any func name -> final name" for src/ rewriting)
    addr2name = {}  # (ov_or_None, addr_int) -> final
    src_rename = {}  # full func_X token -> final name
    for fk, fn in rename.items():
        ov, addr = parse_func_key(fk)
        addr2name[(ov, addr)] = fn
        src_rename[fk] = fn

    # 1) Walk all symbols.txt files
    sym_files = []
    cfg = os.path.join(ROOT, "config", "arm9")
    for sub in ("", "itcm", "dtcm"):
        p = os.path.join(cfg, sub, "symbols.txt") if sub else os.path.join(cfg, "symbols.txt")
        if os.path.isfile(p): sym_files.append((None, p))
    ov_root = os.path.join(cfg, "overlays")
    if os.path.isdir(ov_root):
        for ov in sorted(os.listdir(ov_root)):
            p = os.path.join(ov_root, ov, "symbols.txt")
            if os.path.isfile(p): sym_files.append((ov, p))

    total_sym = 0
    for ov, path in sym_files:
        # filter map to addresses owned by this scope
        scope = {}
        for (scope_ov, addr), n in addr2name.items():
            if scope_ov == ov: scope[addr] = n
        c = rewrite_symbols_txt(path, scope)
        if c: print("  symbols %-25s  %d renames" % (os.path.relpath(path, ROOT), c))
        total_sym += c
    print("TOTAL symbols.txt renames:", total_sym)

    # 2) Rewrite src/auto and src/calls
    src_touched = 0
    src_renamed_files = 0
    for d in ("src/auto", "src/calls"):
        dp = os.path.join(ROOT, d)
        if not os.path.isdir(dp): continue
        for fn in os.listdir(dp):
            if not fn.endswith(".c"): continue
            full = os.path.join(dp, fn)
            txt = open(full).read()
            new_txt = FUNC_RE.sub(lambda m: src_rename.get(m.group(0), m.group(0)), txt)
            file_changed = new_txt != txt
            # decide new filename: if basename func_X is in rename, rename file
            base = fn[:-2]
            newbase = src_rename.get(base, base)
            newpath = os.path.join(dp, newbase + ".c")
            if file_changed:
                if DRY:
                    src_touched += 1
                else:
                    if newpath != full:
                        with open(newpath, "w") as f: f.write(new_txt)
                        # also rename matching .c.o sibling if exists
                        oo = full + ".o"
                        if os.path.exists(oo):
                            try: os.remove(oo)
                            except OSError: pass
                        os.remove(full)
                        src_renamed_files += 1
                    else:
                        with open(full, "w") as f: f.write(new_txt)
                    src_touched += 1
            elif newpath != full:
                # file content unchanged but basename should be renamed (rare)
                if not DRY:
                    os.rename(full, newpath)
                    src_renamed_files += 1
    print("src files touched:", src_touched, "renamed:", src_renamed_files)

    # 3) Rewrite manifest build/decompiled.txt if present
    man = os.path.join(ROOT, "build", "decompiled.txt")
    if os.path.isfile(man):
        with open(man) as f: lines = [l.rstrip() for l in f]
        changed = 0
        for i, ln in enumerate(lines):
            base = ln.strip()
            if base in src_rename:
                lines[i] = src_rename[base]; changed += 1
        if changed and not DRY:
            with open(man, "w") as f: f.write("\n".join(lines)+"\n")
        print("manifest decompiled.txt renames:", changed)

if __name__ == "__main__":
    main()
