#!/usr/bin/env python3
"""Prepare a batch of undecompiled functions ranked by:
- size 16-120 (tractable)
- not in DONE
- maximum number of identified callers (good context)

For each candidate, emit:
- name, size, mode
- disasm (from regenerated delinks, with SDK callee names)
- delink path
- 'caller_contexts': up to 3 small src/ files that call this func (so the agent
  can see HOW it's being used)
"""
import json, os, re, sys
from collections import Counter, defaultdict
from elftools.elf.elffile import ELFFile
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CALLS = json.load(open(os.path.join(ROOT, "build", "calls.json")))
INDEX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
NAMES = json.load(open(os.path.join(ROOT, "sdk", "build", "names.json")))
DONE  = set(open(os.path.join(ROOT, "build", "decompiled.txt")).read().split())
DELINKS_DIR = os.path.join(ROOT, "build", "delinks")

# Build src_final mapping (re-applies apply_names logic)
counts = Counter(NAMES.values())
by_name = defaultdict(list)
for k, v in NAMES.items():
    m = re.match(r"^func_(ov\d+_)?([0-9a-f]{8})$", k)
    if not m: continue
    addr = int(m.group(2), 16)
    info = INDEX.get(k, {}); sz = info.get("size", 0); rl = info.get("relocs", [])
    if counts[v] > 1 and sz <= 16 and not rl: continue
    by_name[v].append((addr, k))
src_final = {}
identified = set()
for sdk, lst in by_name.items():
    lst.sort()
    src_final[lst[0][1]] = sdk
    identified.add(sdk)
    for addr, k in lst[1:]:
        suffixed = "%s_0x%08x" % (sdk, addr)
        src_final[k] = suffixed
        identified.add(suffixed)
def display(fn): return src_final.get(fn, fn)
identified |= DONE

# Index symbols in delinks
sym_to_delink = {}; sym_meta = {}
for f in sorted(os.listdir(DELINKS_DIR)):
    if not f.endswith(".o"): continue
    p = os.path.join(DELINKS_DIR, f)
    e = ELFFile(open(p, "rb"))
    st = e.get_section_by_name(".symtab")
    if not st: continue
    secs = list(e.iter_sections())
    for sym in st.iter_symbols():
        if sym["st_info"]["type"] != "STT_FUNC": continue
        if not sym.name or sym.name.startswith("$"): continue
        if sym["st_size"] == 0: continue
        sh = sym["st_shndx"]
        if not isinstance(sh, int) or sh == 0: continue
        sym_to_delink[sym.name] = p
        mode = "thumb" if (sym["st_value"] & 1) else "arm"
        sym_meta[sym.name] = (sym["st_value"] & ~1, sym["st_size"], mode, sh)

def disasm_func(sym_name):
    """Return (mode, hex, list of (off, mn, op, callee_name_or_None))."""
    p = sym_to_delink[sym_name]
    val, size, mode, sh = sym_meta[sym_name]
    e = ELFFile(open(p, "rb"))
    secs = list(e.iter_sections())
    data = secs[sh].data()[val:val+size]
    st = e.get_section_by_name(".symtab")
    rel_by_off = {}
    for s in e.iter_sections():
        if s.name.startswith(".rel") and s["sh_info"] == sh:
            for r in s.iter_relocations():
                if val <= r["r_offset"] < val + size:
                    nm = st.get_symbol(r["r_info_sym"]).name
                    rel_by_off[r["r_offset"]-val] = nm
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if mode == "thumb" else CS_MODE_ARM)
    items = []
    for i in md.disasm(bytes(data), 0):
        items.append((i.address, i.mnemonic, i.op_str, rel_by_off.get(i.address)))
    return mode, data.hex(), items, rel_by_off

def format_disasm(items):
    lines = []
    for off, mn, op, cal in items:
        if cal:
            if mn in ("bl", "blx", "b") and "#" in op: op = cal
            elif "ldr" in mn and "[pc" in op: op = "= " + cal
        lines.append("  %04x: %-6s %s" % (off, mn, op))
    return "\n".join(lines)

# Build caller_count map: undecompiled func -> set of identified callers
caller_set = defaultdict(set)
callee_info = {}  # callee -> sample (caller, mode, hex) for caller .asm
for c in CALLS:
    caller = c["name"]
    caller_disp = display(caller)
    if caller_disp not in identified and caller not in identified: continue
    for callee in c["callees"]:
        # is callee already identified?
        if display(callee) in identified or callee in identified: continue
        if callee in DONE: continue
        # filter out garbage names like 'r1', 'r2', 'r3'
        if not callee.startswith("func_"): continue
        caller_set[callee].add(caller_disp if caller_disp in identified else caller)

# Rank by caller count, then by smaller size (easier wins first)
ranked = sorted(
    [(c, callers) for c, callers in caller_set.items()
     if 16 <= INDEX.get(c, {}).get("size", 0) <= 120
     and c in sym_to_delink],
    key=lambda x: (-len(x[1]), INDEX[x[0]]["size"]),
)

n_want = int(sys.argv[1]) if len(sys.argv) > 1 else 12
chosen = ranked[:n_want]
out = []
for cname, callers in chosen:
    info = INDEX[cname]
    mode, hexb, items, rel = disasm_func(cname)
    out.append({
        "name": cname,
        "size": info["size"],
        "mode": mode,
        "hex": hexb,
        "n_callers": len(callers),
        "callers": sorted(callers)[:5],
        "delink": sym_to_delink[cname].replace("\\", "/"),
        "disasm": format_disasm(items),
    })
print(json.dumps(out, indent=2))
