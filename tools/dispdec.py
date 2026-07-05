import subprocess, sys, re
f = sys.argv[1]
out = subprocess.run(['python','tools/getcand.py',f], capture_output=True, text=True).stdout
dis = [l for l in out.split('\n') if l.strip().startswith('disasm:')]
dis = dis[0][len('disasm:'):] if dis else ''
ins = [x.strip() for x in dis.split(';')]
# header = instrs up to (and including) the switch dispatch
# find the switch: 'cmp rN, #M' then 'addls pc, pc, rN, lsl #2'
sw = None
for i,x in enumerate(ins):
    if x.startswith('addls pc'):
        sw = i; break
mcmp = ins[sw-1]  # cmp rN, #M
m = re.search(r'#(0x[0-9a-f]+|\d+)', mcmp)
ncases = int(m.group(1),0)+1
# jump table: ins[sw+1] = b #default, then ins[sw+2..sw+1+ncases] = case bodies
default = ins[sw+1]
table = ins[sw+2:sw+2+ncases]  # case i -> target addr
casetgt = []
for i,t in enumerate(table):
    mm = re.search(r'#(0x[0-9a-f]+)', t)
    casetgt.append((i, int(mm.group(1),16)))
# source order = cases sorted by body address
order = sorted(casetgt, key=lambda c:c[1])
# callbacks from relocs (in pool order = body-address order); parse reloc lines
relocs = re.findall(r'\+0x[0-9a-f]+ -> (func_ov\w+)', out)
# filter out non-callback (func_0203c634); callbacks are the ov-local ones after the c634 block
cbs = [r for r in relocs if not r.endswith('0203c634')]
print("=== HEADER (first %d instrs) ===" % sw)
for x in ins[:sw]: print("  ", x)
print("=== ncases=%d, source order (case->callback) ===" % ncases)
for (ci,addr),cb in zip(order, cbs):
    print(f"  case {ci}: {cb}")
if len(cbs)!=len(order): print("!! callback count", len(cbs), "!= body count", len(order))
