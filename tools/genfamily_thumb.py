#!/usr/bin/env python3
"""Generate byte-exact C for shape-family siblings from a verified template.

Usage: python tools/genfamily.py <template_func_name> [--write]
  Reads the verified template .c (searched under src/, non-stub), finds all
  still-stubbed ARM functions with the SAME canonical (reloc-masked) bytes,
  and for each emits C by positional reloc-symbol substitution + func rename.
  Verifies every generated file with verify_idx. --write keeps matches on disk
  (into calls/ or auto/) and deletes the corresponding asm_stub; without it,
  it's a dry run (temp verify only).
"""
import json,glob,os,re,sys,subprocess,tempfile

ROOT=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
idx=json.load(open(os.path.join(ROOT,'build/func_index.json')))

def canon(f):
    b=bytearray.fromhex(f['hex'])
    for off,sym in f['relocs']:
        for j in range(4):
            if off+j<len(b): b[off+j]=0
    return bytes(b).hex()

def find_real_c(name):
    for p in glob.glob(os.path.join(ROOT,'src/overlays/*/**/'+name+'.c'),recursive=True):
        if 'asm_stubs' not in p.replace('\\','/'): return p
    return None

def find_stub_c(name):
    for p in glob.glob(os.path.join(ROOT,'src/overlays/*/asm_stubs/**/'+name+'.c'),recursive=True):
        return p
    return None

def verify(cpath,name):
    r=subprocess.run([sys.executable,os.path.join(ROOT,'tools/verify_idx.py'),cpath,name,'--thumb'],
                     capture_output=True,text=True,cwd=ROOT)
    out=r.stdout+r.stderr
    return ('MATCH' in out and 'DIFIERE' not in out),out.strip().splitlines()[-1] if out.strip() else '(no output)'

def main():
    tname=sys.argv[1]
    write='--write' in sys.argv
    tf=idx[tname]
    tcanon=canon(tf)
    tc_path=find_real_c(tname)
    if not tc_path:
        print("template .c not found (must be verified/wired first):",tname); return
    tmpl=open(tc_path,encoding='utf-8').read()
    tsyms=[r[1] for r in tf['relocs']]
    tov=re.search(r'ov(\d+)',tname).group(1)
    taddr=tname.split('_')[-1]
    # find family members still stubbed
    members=[]
    for name,f in idx.items():
        if name==tname or f['mode']!='arm': continue
        if canon(f)!=tcanon: continue
        if not find_stub_c(name): continue
        members.append(name)
    members.sort()
    print(f"template {tname}: {len(members)} stubbed siblings")
    nmatch=0
    for name in members:
        f=idx[name]
        osyms=[r[1] for r in f['relocs']]
        if len(osyms)!=len(tsyms):
            print(f"  {name}: RELOC COUNT MISMATCH"); continue
        ov=re.search(r'ov(\d+)',name).group(1)
        addr=name.split('_')[-1]
        src=tmpl
        # positional symbol substitution (longest first to avoid partial overlap)
        pairs=sorted(zip(tsyms,osyms),key=lambda p:-len(p[0]))
        for a,b in pairs:
            if a!=b: src=src.replace(a,b)
        # rename the function symbol + any self-references
        src=src.replace(tname,name)
        # generic ovNNN tokens (data/func decls that used template ov but weren't relocs)
        # already handled by symbol subs; also fix bare ov tokens in extern names if any slipped
        hasrelocs=len(f['relocs'])>0
        sub='calls' if hasrelocs else 'auto'
        outdir=os.path.join(ROOT,f'src/overlays/{"ov"+ov}/{sub}')
        outp=os.path.join(outdir,name+'.c')
        if write:
            os.makedirs(outdir,exist_ok=True)
            with open(outp,'w',encoding='utf-8',newline='\n') as fh: fh.write(src)
            ok,msg=verify(outp,name)
            if ok:
                stub=find_stub_c(name)
                if stub: os.remove(stub)
                nmatch+=1
                print(f"  {name}: MATCH (wired)")
            else:
                os.remove(outp)
                print(f"  {name}: {msg}")
        else:
            with tempfile.NamedTemporaryFile('w',suffix='.c',delete=False,dir=os.path.join(ROOT,'tools')) as fh:
                fh.write(src); tmp=fh.name
            ok,msg=verify(tmp,name)
            os.remove(tmp)
            for g in glob.glob(tmp+'*'):
                try: os.remove(g)
                except: pass
            if ok: nmatch+=1
            print(f"  {name}: {'MATCH' if ok else msg}")
    print(f"== {nmatch}/{len(members)} siblings match ==")

if __name__=='__main__': main()
