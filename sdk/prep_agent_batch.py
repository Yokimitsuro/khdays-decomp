#!/usr/bin/env python3
"""Prepara N candidatos (all-SDK-callee, sin decompilar) con disasm
fresco desde los delinks regenerados (con nombres SDK) y el comando
de verificacion. Emite JSON listo para los agentes."""
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

# build src_final (matches apply_names dedup logic)
def build_src_final():
    counts=Counter(NAMES.values()); by_name=defaultdict(list)
    for k,v in NAMES.items():
        m=re.match(r"^func_(ov\d+_)?([0-9a-f]{8})$", k)
        if not m: continue
        addr=int(m.group(2),16); info=INDEX.get(k,{})
        sz=info.get("size",0); rl=info.get("relocs",[])
        if counts[v]>1 and sz<=16 and not rl: continue
        by_name[v].append((addr,k))
    out={}
    for sdk,lst in by_name.items():
        lst.sort(); out[lst[0][1]]=sdk
        for addr,k in lst[1:]: out[k]="%s_0x%08x"%(sdk,addr)
    return out

SRC_FINAL = build_src_final()
def display(fname): return SRC_FINAL.get(fname, fname)
SDK_KNOWN = set(SRC_FINAL.keys())

# Index symbol -> delink path (only for delinks; uses NEW symbol names)
sym_to_delink = {}
sym_meta = {}  # sym -> (st_value, st_size, mode)
for f in sorted(os.listdir(DELINKS_DIR)):
    if not f.endswith(".o"): continue
    p = os.path.join(DELINKS_DIR, f)
    e = ELFFile(open(p, "rb"))
    st = e.get_section_by_name(".symtab")
    if not st: continue
    secs = list(e.iter_sections())
    text_sec_indices = {i for i,s in enumerate(secs) if s.name==".text" or s.name.startswith(".text.")}
    for sym in st.iter_symbols():
        if sym["st_info"]["type"] != "STT_FUNC": continue
        if not sym.name or sym.name.startswith("$"): continue
        if sym["st_size"] == 0: continue
        sh = sym["st_shndx"]
        # accept any non-undefined shndx
        if not isinstance(sh, int) or sh == 0: continue
        sym_to_delink[sym.name] = p
        # heuristic mode: thumb if odd LSB on val
        mode = "thumb" if (sym["st_value"] & 1) else "arm"
        sym_meta[sym.name] = (sym["st_value"] & ~1, sym["st_size"], mode, sh)

def disasm_from_delink(sym_name):
    """Returns (mode, hex_bytes, list of (off, mnemonic, op_str, callee_or_None))."""
    p = sym_to_delink[sym_name]
    val, size, mode, sh = sym_meta[sym_name]
    e = ELFFile(open(p, "rb"))
    secs = list(e.iter_sections())
    sec = secs[sh]
    data = sec.data()[val:val+size]
    st = e.get_section_by_name(".symtab")
    # collect relocs for this section
    rel_by_off = {}
    for s in e.iter_sections():
        if s.name.startswith(".rel") and s["sh_info"]==sh:
            for r in s.iter_relocations():
                if val <= r["r_offset"] < val+size:
                    sym = st.get_symbol(r["r_info_sym"])
                    rel_by_off[r["r_offset"]-val] = sym.name
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if mode=="thumb" else CS_MODE_ARM)
    out=[]
    for i in md.disasm(bytes(data), 0):
        out.append((i.address, i.mnemonic, i.op_str, rel_by_off.get(i.address)))
    return mode, data.hex(), out, rel_by_off

def format_disasm(items, rel_by_off):
    lines=[]
    for off, mn, op, cal in items:
        if cal:
            # replace numeric branch target with symbol name for clarity
            if mn in ("bl","blx","b") and "#" in op:
                op = cal
            elif "ldr" in mn and "[pc" in op:
                op = "= " + cal
        lines.append("  %04x: %-6s %s" % (off, mn, op))
    return "\n".join(lines)

def main():
    n_want = int(sys.argv[1]) if len(sys.argv)>1 else 16
    mode = sys.argv[2] if len(sys.argv)>2 else "all_sdk"   # all_sdk | any_sdk
    # pool: undecompiled, callees ≥1 SDK (mode dependent), reasonable size
    pool=[]
    for c in CALLS:
        fn=c["name"]
        if display(fn) in DONE: continue
        callees=set(c["callees"])
        if not callees: continue
        if mode == "all_sdk":
            if not callees.issubset(SDK_KNOWN): continue
        else:  # any_sdk
            if not (callees & SDK_KNOWN): continue
        if c["ninstr"]<6 or c["ninstr"]>25: continue
        if fn not in sym_to_delink: continue
        pool.append(c)
    pool.sort(key=lambda c: c["ninstr"])  # easiest first
    sys.stderr.write("# candidate pool: %d\n" % len(pool))
    chosen = pool[:n_want]
    out=[]
    for c in chosen:
        fn = c["name"]
        new_name = display(fn)
        # mode from calls.json is the authoritative source
        true_mode = c.get("mode","arm")
        mode, hex_bytes, items, rel_by_off = disasm_from_delink(new_name if new_name in sym_to_delink else fn)
        # if calls.json says thumb but delink said arm, redisasm thumb
        if true_mode != mode:
            md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if true_mode=="thumb" else CS_MODE_ARM)
            data = bytes.fromhex(hex_bytes)
            items = [(i.address, i.mnemonic, i.op_str, rel_by_off.get(i.address)) for i in md.disasm(data, 0)]
            mode = true_mode
        # rewrite callee names in items already done via rel_by_off
        disasm = format_disasm(items, rel_by_off)
        delink_path = sym_to_delink[new_name if new_name in sym_to_delink else fn].replace("\\","/")
        callees_new = [display(x) for x in c["callees"]]
        out.append({
            "name_old": fn,
            "name": new_name,
            "mode": mode,
            "size": c["size"],
            "ninstr": c["ninstr"],
            "hex": hex_bytes,
            "callees": callees_new,
            "delink": delink_path,
            "disasm": disasm,
        })
    print(json.dumps(out, indent=2))

if __name__=="__main__":
    main()
