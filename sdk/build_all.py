#!/usr/bin/env python3
"""Compila todos los .c en sdk/src/ con mwccarm y los compara con func_index.json."""
import os, sys, subprocess, json
from elftools.elf.elffile import ELFFile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SDK  = os.path.join(ROOT, "sdk")
MWCC = os.path.join(ROOT, "tools", "mwccarm", "3.0_patch4", "mwccarm.exe")
LIC  = os.path.join(ROOT, "tools", "mwccarm", "license.dat")
INC  = os.path.join(SDK, "include")
BUILD= os.path.join(SDK, "build")
INDEX= json.load(open(os.path.join(ROOT, "build", "func_index.json")))
FLAGS= ["-O4,p","-proc","arm946e","-interworking","-lang","c99","-enum","int",
        "-char","signed","-inline","on,noauto","-Cpp_exceptions","off","-gccext,on"]
ENV  = dict(os.environ, LM_LICENSE_FILE=LIC)

def compile_c(cpath):
    o = os.path.join(BUILD, os.path.basename(cpath)+".o")
    r = subprocess.run([MWCC,"-c",*FLAGS,"-i",INC,"-o",o,cpath],
                       capture_output=True, text=True, env=ENV)
    return o, r.returncode, r.stdout, r.stderr

def funcs_from_obj(opath):
    elf = ELFFile(open(opath,"rb"))
    sections=list(elf.iter_sections())
    st=elf.get_section_by_name(".symtab")
    sec_rel={}
    for i,s in enumerate(sections):
        if s.name.startswith(".rel"):
            tgt=s["sh_info"]
            rd=sec_rel.setdefault(tgt,{})
            for r in s.iter_relocations():
                nm=st.get_symbol(r["r_info_sym"]).name
                rd[r["r_offset"]]=(nm,r["r_info_type"])
    out={}
    for sym in st.iter_symbols():
        if sym["st_info"]["type"]!="STT_FUNC": continue
        if sym.name in ("$a","$t","$d",""): continue
        sh=sym["st_shndx"]
        if not isinstance(sh,int): continue
        sec=sections[sh]
        if not sec.name.startswith(".text"): continue
        val=sym["st_value"]&~1; size=sym["st_size"]
        if size==0: continue
        data=sec.data()
        rel={o-val:v for o,v in sec_rel.get(sh,{}).items() if val<=o<val+size}
        out[sym.name]=(bytes(data[val:val+size]),rel)
    return out

def search_exact(b):
    hx=b.hex(); n=len(b)
    return [f for f,info in INDEX.items() if info["size"]==n and info["hex"]==hx]

def search_reloc(b, rel):
    """Reloc-aware: encuentra func_X con mismo size, mismas posiciones de reloc
    y mismos bytes tras enmascarar 4 bytes en cada offset relocado."""
    n=len(b)
    rel_offs=set(rel.keys())
    mine=bytearray(b)
    for off in rel_offs:
        for k in range(4):
            if off+k<n: mine[off+k]=0
    mine_hx=mine.hex()
    hits=[]
    for f,info in INDEX.items():
        if info["size"]!=n: continue
        their_offs={r[0] for r in info.get("relocs",[])}
        if their_offs!=rel_offs: continue
        theirs=bytearray.fromhex(info["hex"])
        for off in their_offs:
            for k in range(4):
                if off+k<n: theirs[off+k]=0
        if theirs.hex()==mine_hx: hits.append(f)
    return hits

def main():
    os.makedirs(BUILD, exist_ok=True)
    files=sorted([f for f in os.listdir(os.path.join(SDK,"src")) if f.endswith(".c")])
    total_match=0; total_funcs=0
    results={}
    for fn in files:
        cpath=os.path.join(SDK,"src",fn)
        o,rc,out,err=compile_c(cpath)
        if rc!=0:
            print("# %s  COMPILE FAIL" % fn)
            print("    "+(out+err).strip()[:600].replace("\n","\n    "))
            continue
        funcs=funcs_from_obj(o)
        ms=0
        ident={}
        for name,(b,rel) in funcs.items():
            hits=search_exact(b) if not rel else search_reloc(b, rel)
            if hits:
                ms+=1; ident[name]=hits
        total_match+=ms; total_funcs+=len(funcs)
        print("# %-30s %d/%d matched" % (fn, ms, len(funcs)))
        for n,hits in ident.items():
            print("    %-30s -> %s" % (n, ", ".join(hits)))
        miss=[n for n in funcs if n not in ident]
        if miss: print("    miss: %s" % ", ".join(miss))
        results[fn]={"matched":ident,"miss":miss}
    print("\n== TOTAL: %d/%d funciones identificadas en %d archivos ==" % (total_match,total_funcs,len(files)))
    with open(os.path.join(BUILD,"identified.json"),"w") as f: json.dump(results,f,indent=2)

if __name__=="__main__": main()
