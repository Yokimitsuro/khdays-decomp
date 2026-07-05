import subprocess, sys, re
f = sys.argv[1]
out = subprocess.run(['python','tools/getcand.py',f], capture_output=True, text=True).stdout
dis = [l for l in out.split('\n') if l.strip().startswith('disasm:')][0][len('disasm:'):]
ins = [x.strip() for x in dis.split(';')]
sw = next(i for i,x in enumerate(ins) if x.startswith('addls pc'))
ncases = int(re.search(r'#(0x[0-9a-f]+|\d+)', ins[sw-1]).group(1),0)+1
table = ins[sw+2:sw+2+ncases]
casetgt = [(i,int(re.search(r'#(0x[0-9a-f]+)',t).group(1),16)) for i,t in enumerate(table)]
order = sorted(casetgt, key=lambda c:c[1])
relocs = re.findall(r'\+0x[0-9a-f]+ -> (func_\w+)', out)
cbs = [r for r in relocs if not r.endswith('0203c634')]
hdr = ins[:sw]
# preamble: ov156-style  ldrb #0x1c4; tst #2; movne #5; strbne #0x1c7  (at very top)
pre = None
htxt=' ; '.join(hdr)
mm=re.search(r'ldrb r\d+, \[r\d+, #0x1c4\] ; tst r\d+, #2 ; movne r\d+, #5 ; strbne', htxt)
if mm: pre='flag2set5'
# strip the preamble instrs from consideration for bl-check
core = hdr
if pre:
    # remove up to the strbne #0x1c7
    k = next((i for i,x in enumerate(hdr) if 'strbne' in x and '#0x1c7' in x), None)
    if k is not None: core = hdr[k+1:]
if any(x.startswith('bl ') or x.startswith('blx') for x in core): print("// BAIL: extra call"); sys.exit(1)
mir = next((i for i,x in enumerate(hdr) if 'strb' in x and '#0x1c6' in x and 'strbne' not in x), None)
if mir is None: print("// BAIL: no mirror"); sys.exit(1)
popeq = any('popeq' in x for x in hdr[:14])
mbot = any('ldrsb' in hdr[j] and '#0xc7' in hdr[j] for j in (mir-1,mir-2) if j>=0) and mir>7
# flag ops in header order (supports multiple hw60)
body_ops=[]
for i,x in enumerate(hdr):
    if '#0x60' in x and x.startswith('ldrh'):
        blk=' '.join(hdr[i:i+9])
        # first bic/orr that is NOT the 0xff00 high-byte-clear mask = the real op (decimal or hex imm)
        cand=[(op,int(v,0)) for op,v in re.findall(r'(bic|orr) (?:r\d+|ip|lr), (?:r\d+|ip|lr), #(0x[0-9a-f]+|\d+)', blk) if int(v,0)!=0xff00]
        if cand: body_ops.append(('hw60', cand[0][0], cand[0][1]))
    elif '#0xae' in x and x.startswith('ldrh'):
        blk=' '.join(hdr[i:i+3]); mm=re.search(r'bic (?:r\d+|ip|lr), (?:r\d+|ip|lr), #(0x[0-9a-f]+|\d+)', blk)
        if mm: body_ops.append(('ae', int(mm.group(1),0)))
    else:
        # base/dest regs may be ip or lr, not just rN (mwcc uses ip for the 0x388 slot load)
        mo=re.match(r'ldr (r\d+|ip|lr), \[r\d+, #(0x3[0-9a-f][0-9a-f])\]$', x)
        if mo and i+1<len(hdr) and re.match(r'ldr (?:r\d+|ip|lr), \['+re.escape(mo.group(1))+r', #8\]$', hdr[i+1]):
            blk=' '.join(hdr[i:i+9])
            # the real op is right after `lsr rV,rV,#0x18` (index i+4): orr rV,rV,#K (|=K) or bic rV,rV,#K (&=~K)
            opins = hdr[i+4] if i+4 < len(hdr) else ''
            m_orr = re.match(r'orr (?:r\d+|ip|lr), (?:r\d+|ip|lr), #(0x[0-9a-f]+|\d+)$', opins)
            m_bic = re.match(r'bic (?:r\d+|ip|lr), (?:r\d+|ip|lr), #(0x[0-9a-f]+|\d+)$', opins)
            if m_orr: op = f'|= {hex(int(m_orr.group(1),0))}'
            elif m_bic: op = f'&= ~{hex(int(m_bic.group(1),0))}'
            else: op = '|= 1' if re.search(r'orr r\d+, r\d+, #1\b',blk) else '&= ~1'
            body_ops.append(('bf', mo.group(2), op))
L=["struct bf { unsigned b : 8; };","struct hw60 { unsigned short lo : 8, hi : 8; };",
   "extern void func_0203c634(void *obj, int idx, void *value);"]
for cb in cbs: L.append(f"extern void {cb}(void);")
L.append(f"\nvoid {f}(int *node) {{"); L.append("    int *state = (int *)node[1];")
def op_line(o, ind):
    if o[0]=='hw60':
        if o[1]=='bic': return f"{ind}((struct hw60 *)(*state + 0x60))->hi &= ~{hex(o[2])};"
        else: return (f"{ind}{{ unsigned short *p = (unsigned short *)(*state + 0x60); unsigned int u = *p;\n"
                      f"{ind}  *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | {hex(o[2])}) << 0x18) >> 0x10)); }}")
    if o[0]=='ae': return f"{ind}*(unsigned short *)(*state + 0x1ae) &= ~{hex(o[1])};"
    if o[0]=='bf': return f"{ind}((struct bf *)(*(int *)(*state + {o[1]}) + 8))->b {o[2]};"
def emit(ind):
    if not mbot: L.append(f"{ind}*(signed char *)(*state + 0x1c6) = (signed char)c;")
    for o in body_ops: L.append(op_line(o, ind))
    if mbot: L.append(f"{ind}*(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);")
    L.append(f"{ind}switch (*(signed char *)(*state + 0x1c6)) {{")
    for (ci,addr),cb in zip(order,cbs):
        L.append(f"{ind}case {hex(ci) if ci>9 else ci}:"); L.append(f"{ind}    func_0203c634(node, 1, {cb});"); L.append(f"{ind}    break;")
    L.append(f"{ind}}}")
if pre=='flag2set5':
    L.append("    if (*(unsigned char *)(*state + 0x1c4) & 2)"); L.append("        *(signed char *)(*state + 0x1c7) = 5;")
L.append("    int c = *(signed char *)(*state + 0x1c7);")
if popeq:
    L.append("    if (c == -1) return;"); emit("    ")
else:
    L.append("    if (c != -1) {"); emit("        "); L.append("    }")
L.append("    *(signed char *)(*state + 0x1c7) = -1;"); L.append("}")
print('\n'.join(L))
