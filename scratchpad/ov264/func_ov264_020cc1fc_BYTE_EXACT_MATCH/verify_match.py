#!/usr/bin/env python3
from pathlib import Path
import struct, subprocess, re, sys
root=Path(__file__).resolve().parent

def elf_sections(path):
    b=Path(path).read_bytes()
    shoff=struct.unpack_from('<I',b,0x20)[0]
    entsz=struct.unpack_from('<H',b,0x2e)[0]
    n=struct.unpack_from('<H',b,0x30)[0]
    shstrndx=struct.unpack_from('<H',b,0x32)[0]
    sh=[struct.unpack_from('<10I',b,shoff+i*entsz) for i in range(n)]
    names_sec=sh[shstrndx]
    names=b[names_sec[4]:names_sec[4]+names_sec[5]]
    d={}
    for s in sh:
        no=s[0]; end=names.find(b'\0',no)
        name=names[no:end].decode() if no < len(names) else ''
        d[name]=(s,b[s[4]:s[4]+s[5]])
    return b,d

def text_and_reloc_offsets(path):
    _,d=elf_sections(path)
    text=d['.text'][1]
    relname='.rela.text' if '.rela.text' in d else '.rel.text'
    rel=d[relname][1]
    step=12 if relname.startswith('.rela') else 8
    offs={struct.unpack_from('<I',rel,i)[0] for i in range(0,len(rel),step)}
    return text,offs

def rel_semantics(path):
    s=subprocess.check_output(['readelf','-rW',str(path)],text=True)
    out=[]
    for line in s.splitlines():
        m=re.match(r'\s*([0-9a-fA-F]{8})\s+[0-9a-fA-F]+\s+(R_ARM_\S+)\s+[0-9a-fA-F]+\s+(\S+)(?:\s+([+-])\s+(\S+))?',line)
        if not m: continue
        off=int(m.group(1),16); typ=m.group(2); sym=m.group(3)
        # GAS target uses R_ARM_CALL/REL, MWCC uses R_ARM_PC24/RELA(-8).
        # They are the same branch relocation semantics for these call sites.
        canon='ARM_CALL' if typ in ('R_ARM_CALL','R_ARM_PC24') else typ
        out.append((off,canon,sym))
    return out

target=root/'target.o'; matched=root/'matched.o'
t,tr=text_and_reloc_offsets(target); m,mr=text_and_reloc_offsets(matched)
allrel=tr|mr
real=[]
for off in range(0,max(len(t),len(m)),4):
    if off in allrel: continue
    if t[off:off+4] != m[off:off+4]: real.append(off)
rt,rm=rel_semantics(target),rel_semantics(matched)
print(f'target .text:  {len(t)} bytes')
print(f'matched .text: {len(m)} bytes')
print(f'non-relocation word differences: {len(real)}')
print(f'target relocations:  {len(rt)}')
print(f'matched relocations: {len(rm)}')
print(f'relocation offset/symbol semantics identical: {rt == rm}')
if real: print('different offsets:', ', '.join(hex(x) for x in real))
if len(t)!=len(m) or real or rt!=rm:
    sys.exit(1)
print('MATCH: byte-exact instruction/data stream after canonical relocation normalization')
