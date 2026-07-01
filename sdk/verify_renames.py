#!/usr/bin/env python3
"""Compila N src/*.c renombrados al azar y verifica que siguen siendo byte-exact
contra el func_X original en build/func_index.json."""
import os, sys, json, subprocess, random
from elftools.elf.elffile import ELFFile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MWCC = os.path.join(ROOT, "tools", "mwccarm", "3.0_patch4", "mwccarm.exe")
LIC  = os.path.join(ROOT, "tools", "mwccarm", "license.dat")
FLAGS= ["-O4,p","-proc","arm946e","-interworking","-lang","c99","-enum","int",
        "-char","signed","-inline","on,noauto","-Cpp_exceptions","off","-gccext,on"]
ENV  = dict(os.environ, LM_LICENSE_FILE=LIC)
NAMES= json.load(open(os.path.join(ROOT,"sdk","build","names.json")))
INDEX= json.load(open(os.path.join(ROOT,"build","func_index.json")))

def reverse_map():
    """build name_in_src -> func_X (the original key)."""
    # names.json is func_X -> sdk_name; we need src name -> func_X
    # Since duplicates use SDK_name_0xADDR, parse those too
    out={}
    # invert: but we need to know what sdk_name the apply_names script chose
    # Reconstruct: apply same dedup logic
    from collections import Counter, defaultdict
    counts=Counter(NAMES.values())
    by_name=defaultdict(list)
    import re
    for k,v in NAMES.items():
        m=re.match(r'^func_(ov\d+_)?([0-9a-f]{8})$',k)
        if not m: continue
        addr=int(m.group(2),16)
        info=INDEX.get(k,{}); sz=info.get("size",0); rl=info.get("relocs",[])
        if counts[v]>1 and sz<=16 and not rl: continue
        by_name[v].append((addr,k))
    for sdk,lst in by_name.items():
        lst.sort()
        out[sdk]=lst[0][1]
        for addr,k in lst[1:]:
            out["%s_0x%08x"%(sdk,addr)]=k
    return out

def compile_and_extract(cpath, sym_name):
    o=cpath+".o"
    r=subprocess.run([MWCC,"-c",*FLAGS,"-o",o,cpath],capture_output=True,text=True,env=ENV)
    if r.returncode: return None,None,r.stderr[:300]
    e=ELFFile(open(o,"rb"))
    sections=list(e.iter_sections()); st=e.get_section_by_name(".symtab")
    bytes_=None; offs=set(); shndx=None
    for sym in st.iter_symbols():
        if sym.name==sym_name and sym["st_info"]["type"]=="STT_FUNC" and sym["st_size"]>0:
            sh=sym["st_shndx"]
            bytes_=bytes(sections[sh].data()[sym["st_value"]:sym["st_value"]+sym["st_size"]])
            shndx=sh; break
    for s in e.iter_sections():
        if s.name.startswith(".rel") and s["sh_info"]==shndx:
            for rr in s.iter_relocations(): offs.add(rr["r_offset"])
    return bytes_, offs, None

def verify_one(cpath):
    base=os.path.basename(cpath)[:-2]  # sym name = filename stem
    inv=reverse_map()
    orig_key=inv.get(base)
    if not orig_key:
        return False, "no reverse map for " + base
    mb, my_offs, err = compile_and_extract(cpath, base)
    if err: return False, "compile: " + err
    if mb is None: return False, "symbol %s missing in .o" % base
    orig=INDEX[orig_key]
    ob=bytes.fromhex(orig["hex"]); orig_offs={off for off,_ in orig["relocs"]}
    size=len(ob)
    if len(mb)<size: return False, "compiled shorter than orig"
    mb=bytearray(mb[:size]); ob=bytearray(ob)
    for off in my_offs|orig_offs:
        for k in range(4):
            if off+k<size: mb[off+k]=0; ob[off+k]=0
    if bytes(mb)!=bytes(ob): return False, "byte diff after mask"
    if my_offs!=orig_offs: return False, "reloc offsets differ %s vs %s" % (sorted(my_offs), sorted(orig_offs))
    return True, "ok"

def main():
    from _src_roots import src_roots
    pool=[]
    for d in src_roots(ROOT):
        dp=os.path.join(ROOT,d)
        if not os.path.isdir(dp): continue
        for f in os.listdir(dp):
            if f.endswith(".c") and not f.startswith("func_"):
                pool.append(os.path.join(dp,f))
    random.seed(42)
    sample=random.sample(pool, min(8, len(pool)))
    ok=0
    for cp in sample:
        b, msg = verify_one(cp)
        flag="OK" if b else "FAIL"
        print(" %-4s %s   (%s)" % (flag, os.path.relpath(cp,ROOT), msg))
        if b: ok+=1
    print("\n%d/%d byte-match after rename" % (ok, len(sample)))

if __name__=="__main__": main()
