import subprocess, sys, re, os, glob
ROOT=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
f=sys.argv[1]
r=subprocess.run([sys.executable,os.path.join(ROOT,'tools','getcand.py'),f],capture_output=True,text=True)
if r.returncode!=0:
    raise SystemExit((r.stdout+r.stderr).strip())
out=r.stdout
# build addr->canonical name map from ALL symbols.txt
def canon(addr):
    addr=addr.lower().lstrip('0'); pat=re.compile(r'^(\S+)\s+kind:\S+\s+addr:0x0*'+addr+r'\b')
    for p in glob.glob(os.path.join(ROOT,'config','arm9','**','symbols.txt'), recursive=True):
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
