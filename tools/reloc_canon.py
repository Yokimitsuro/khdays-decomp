import subprocess, sys, re, os, glob
f=sys.argv[1]
out=subprocess.run(['python','tools/getcand.py',f],capture_output=True,text=True).stdout
# build addr->canonical name map from ALL symbols.txt
def canon(addr):
    addr=addr.lower().lstrip('0'); pat=re.compile(r'^(\S+)\s+kind:\S+\s+addr:0x0*'+addr+r'\b')
    for p in glob.glob('config/arm9/**/symbols.txt', recursive=True):
        for line in open(p):
            m=pat.match(line)
            if m: return m.group(1)
    return None
dis=[l for l in out.split('\n') if l.strip().startswith('disasm:')]
print(dis[0] if dis else '(no disasm)')
print("--- relocs (canonical) ---")
for m in re.finditer(r'\+0x[0-9a-f]+ -> func_ov\d+_([0-9a-f]{8})', out):
    addr=m.group(1); c=canon(addr)
    tag = '' if (c is None or c==f'func_{addr}' or re.match(r'func_ov\d+_'+addr,c or '')) else f'  <== CANON: {c}'
    print(m.group(0)+tag)
# also main-region relocs
for m in re.finditer(r'\+0x[0-9a-f]+ -> (func_[0-9a-f]{8}|data_[0-9a-f]{8})', out):
    print(m.group(0))
