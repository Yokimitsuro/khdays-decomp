#!/usr/bin/env python3
"""Scan still-stubbed ARM funcs, group by reloc-masked canonical hex, rank families by size."""
import json, os,os,sys
ROOT=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
idx=json.load(open(os.path.join(ROOT,'build/func_index.json')))

# Pre-index all stub files once by walking asm_stubs dirs
stubbed=set()
ovroot=os.path.join(ROOT,'src/overlays')
for ov in os.listdir(ovroot):
    sd=os.path.join(ovroot,ov,'asm_stubs')
    if not os.path.isdir(sd): continue
    for sub in os.listdir(sd):
        subd=os.path.join(sd,sub)
        if not os.path.isdir(subd): continue
        for fn in os.listdir(subd):
            if fn.endswith('.c'): stubbed.add(fn[:-2])

def canon(f):
    b=bytearray.fromhex(f['hex'])
    for off,sym in f['relocs']:
        for j in range(4):
            if off+j<len(b): b[off+j]=0
    return bytes(b).hex()

def looks_thumb(f):
    if f['mode']=='thumb': return True
    for off,sym in f['relocs']:
        if off%4!=0: return True
    return False

want_thumb='--thumb' in sys.argv
groups={}
for name,f in idx.items():
    t=looks_thumb(f)
    if want_thumb:
        if not t: continue
    else:
        if f['mode']!='arm' or t: continue
    if name not in stubbed: continue
    c=canon(f)
    groups.setdefault(c,[]).append(name)

ranked=sorted(groups.items(),key=lambda kv:-len(kv[1]))
args=[a for a in sys.argv[1:] if not a.startswith('--')]
minsize=int(args[0]) if args else 3
sz=lambda c: len(c)//2
print("== %s stubbed families (masked-hex dedup), size>=%d =="%('THUMB' if want_thumb else 'ARM',minsize))
n=0
for c,names in ranked:
    if len(names)<minsize: break
    names.sort()
    n+=1
    print("[%2d] count=%3d bytes=%3d  repr=%s"%(n,len(names),sz(c),names[0]))
    if n<=50:
        print("      members:", " ".join(names[:10]) + (" ..." if len(names)>10 else ""))
print("total families shown:",n,"| total stubbed(this mode):",sum(len(v) for v in groups.values()))
