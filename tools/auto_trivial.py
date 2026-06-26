#!/usr/bin/env python3
"""Decompila DETERMINISTAMENTE funciones por patrones (1-4 instrucciones) y
   verifica byte-exacto con match.py. match.py valida -> 0 falsos positivos.
   Coste LLM: ~0. Uso: python tools/auto_trivial.py"""
import json, re, subprocess, os
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
AUTO = os.path.join(ROOT, "src", "auto"); os.makedirs(AUTO, exist_ok=True)
cands = json.load(open(os.path.join(ROOT, "build", "candidates.json")))
DH = {c["name"]: c for c in cands}
md_a = Cs(CS_ARCH_ARM, CS_MODE_ARM); md_t = Cs(CS_ARCH_ARM, CS_MODE_THUMB)

def imm(s):
    m = re.search(r"#(-?(?:0x)?[0-9a-fA-F]+)", s)
    return int(m.group(1), 0) if m else None

def body(c):
    md = md_t if c["mode"] == "thumb" else md_a
    seq = [(i.mnemonic, i.op_str) for i in md.disasm(bytes.fromhex(c["hex"]), 0)]
    # debe terminar en 'bx lr'; lo quitamos
    if not seq or seq[-1] != ("bx", "lr"): return None
    return seq[:-1]

def M(ins, mns, pat):
    """match (mnemonic in mns) y op_str==regex pat -> tupla de grupos o None"""
    if ins[0] not in mns: return None
    m = re.fullmatch(pat, ins[1])
    return m.groups() if m else ()

def gen(name, b):
    n = name
    L = len(b)
    # ---- 1 instruccion ----
    if L == 1:
        i = b[0]
        if i[0] in ("mov","movs") and re.fullmatch(r"r0, #-?\w+", i[1]):
            return f"int {n}(void){{ return {imm(i[1])}; }}"
        if i[0] in ("mvn","mvns") and re.fullmatch(r"r0, #\w+", i[1]):
            return f"int {n}(void){{ return {~imm(i[1])}; }}"
        if i[0]=="add" and (g:=M(i,{"add"},r"r0, r0, #(\w+)")) is not None and g:
            return f"int {n}(int r0){{ return r0 + {imm(i[1])}; }}"
        if i[0]=="ldr" and re.fullmatch(r"r0, \[r0(, #\w+)?\]", i[1]):
            o=imm(i[1]) or 0
            if o%4==0: return f"int {n}(int *p){{ return p[{o//4}]; }}"
        if i[0]=="ldrh" and re.fullmatch(r"r0, \[r0(, #\w+)?\]", i[1]):
            o=imm(i[1]) or 0
            if o%2==0: return f"unsigned short {n}(unsigned short *p){{ return p[{o//2}]; }}"
        if i[0]=="ldrb" and re.fullmatch(r"r0, \[r0(, #\w+)?\]", i[1]):
            return f"unsigned char {n}(unsigned char *p){{ return p[{imm(i[1]) or 0}]; }}"
        if i[0]=="str" and re.fullmatch(r"r1, \[r0(, #\w+)?\]", i[1]):
            o=imm(i[1]) or 0
            if o%4==0: return f"void {n}(int *p, int v){{ p[{o//4}] = v; }}"
        if i[0]=="str" and i[1]=="r0, [r1]":
            return f"void {n}(int v, int *p){{ *p = v; }}"
        if i[0]=="ldr" and i[1]=="r0, [r0, r1, lsl #2]":
            return f"int {n}(int *a, int i){{ return a[i]; }}"
        if i[0]=="str" and i[1]=="r2, [r0, r1, lsl #2]":
            return f"void {n}(int *a, int i, int v){{ a[i] = v; }}"
        if i[0]=="clz" and i[1]=="r0, r0":
            return f"int {n}(unsigned int x){{ int r; __asm {{ clz r, x }} return r; }}"
    # ---- 2 instrucciones ----
    if L == 2:
        a,c = b
        # *p = 0
        if a[0] in ("mov","movs") and re.fullmatch(r"(r\d+), #0", a[1]) and \
           c[0]=="str" and c[1]==f"{a[1].split(',')[0]}, [r0]":
            return f"void {n}(int *p){{ *p = 0; }}"
        # mov r0,#0 ; str r0,[r2,#N]  -> setter que devuelve 0
        if a==("mov","r0, #0") and (g:=M(c,{"str"},r"r0, \[r2, #(\w+)\]")):
            o=imm(c[1])
            if o%4==0: return f"int {n}(int a, int b, int *p){{ p[{o//4}] = 0; return 0; }}"
        # abs
        if a==("cmp","r0, #0") and c==("rsblt","r0, r0, #0"):
            return f"int {n}(int x){{ if (x < 0) x = -x; return x; }}"
        # *p & N  / return
        if a==("ldr","r0, [r0]") and (g:=M(c,{"and"},r"r0, r0, #(\w+)")):
            return f"int {n}(int *p){{ return *p & {imm(c[1])}; }}"
        # double deref: ldr r0,[r0,#N] ; ldr r0,[r0]
        if (g:=M(a,{"ldr"},r"r0, \[r0(?:, #(\w+))?\]")) is not None and c==("ldr","r0, [r0]"):
            o=imm(a[1]) or 0
            if o%4==0: return f"int {n}(int **p){{ return *p[{o//4}]; }}"
        # add r0,r0,r1,lsl #2 ; str r2,[r0,#N]
        if a==("add","r0, r0, r1, lsl #2") and (g:=M(c,{"str"},r"r2, \[r0, #(\w+)\]")):
            o=imm(c[1])
            if o%4==0: return f"void {n}(int *a, int i, int v){{ (a + i)[{o//4}] = v; }}"
        # add r0,r0,r1 ; strb r2,[r0,#N]
        if a==("add","r0, r0, r1") and (g:=M(c,{"strb"},r"r2, \[r0, #(\w+)\]")):
            return f"void {n}(unsigned char *p, int i, unsigned char v){{ p[i + {imm(c[1])}] = v; }}"
    # ---- 3 instrucciones ----
    if L == 3:
        a,c,d = b
        # ldrh ; orr|bic #N ; strh  -> *p |= / &= ~
        if a==("ldrh","r1, [r0]") and d==("strh","r1, [r0]"):
            if (g:=M(c,{"orr"},r"r1, r1, #(\w+)")): return f"void {n}(unsigned short *p){{ *p |= {imm(c[1])}; }}"
            if (g:=M(c,{"bic"},r"r1, r1, #(\w+)")): return f"void {n}(unsigned short *p){{ *p &= ~{imm(c[1])}; }}"
        # field += base : ldr r1,[r0,#N] ; add r1,r1,r0 ; str r1,[r0,#N]
        if (g:=M(a,{"ldr"},r"r1, \[r0(?:, #(\w+))?\]")) is not None and c==("add","r1, r1, r0"):
            o=imm(a[1]) or 0
            if d==("str", a[1].replace("r1","r1",1)) and o%4==0:
                return f"void {n}(int *p){{ p[{o//4}] = p[{o//4}] + (int)p; }}"
    # ---- 4 instrucciones: ==K test ----
    if L == 4:
        a,c,d,e = b
        if (g:=M(a,{"ldr"},r"r0, \[r0(?:, #(\w+))?\]")) is not None and \
           (h:=M(c,{"cmp"},r"r0, #(\w+)")) and d==("moveq","r0, #1") and e==("movne","r0, #0"):
            o=imm(a[1]) or 0
            if o%4==0: return f"int {n}(int *p){{ return p[{o//4}] == {imm(c[1])}; }}"
        if (g:=M(a,{"ldrh"},r"r0, \[r0(?:, #(\w+))?\]")) is not None and \
           c==("cmp","r0, #0") and d==("moveq","r0, #1") and e==("movne","r0, #0"):
            o=imm(a[1]) or 0
            if o%2==0: return f"int {n}(unsigned short *p){{ return p[{o//2}] == 0; }}"
    # ---- patron generico: addr calculado (lsl + adds) + ldr/str ----
    if 2 <= L <= 4 and b[0][0]=="lsl" and (g:=M(b[0],{"lsl"},r"r0, r0, #(\d+)")):
        sh=int(g[0]); base=0; ok=True; k=1
        while k<L-1 and b[k][0]=="add" and (gg:=M(b[k],{"add"},r"r0, r0, #(\w+)")):
            base+=imm(b[k][1]); k+=1
        last=b[-1]
        if k==L-1:
            if (gg:=M(last,{"ldr"},r"r0, \[r0(?:, #(\w+))?\]")) is not None:
                z=imm(last[1]) or 0
                return f"int {n}(int i){{ return *(int *)(0x{base:x} + (i << {sh}) + {z}); }}"
            if (gg:=M(last,{"str"},r"r1, \[r0(?:, #(\w+))?\]")) is not None:
                z=imm(last[1]) or 0
                return f"void {n}(int i, int v){{ *(int *)(0x{base:x} + (i << {sh}) + {z}) = v; }}"
    return None

def verify(name, code, thumb):
    cf = os.path.join(AUTO, name + ".c"); open(cf,"w").write(code+"\n")
    a = ["python", os.path.join(ROOT,"tools","match.py"), cf, DH[name]["hex"]] + (["--thumb"] if thumb else [])
    if ">>> MATCH <<<" in subprocess.run(a,capture_output=True,text=True).stdout: return True
    os.remove(cf); return False

done=set(open(os.path.join(ROOT,"build","decompiled.txt")).read().split()) if os.path.exists(os.path.join(ROOT,"build","decompiled.txt")) else set()
new=0; total_ok=0
for c in cands:
    if os.path.exists(os.path.join(AUTO,c["name"]+".c")): total_ok+=1; continue
    bd = body(c)
    if bd is None: continue
    code = gen(c["name"], bd)
    if code and verify(c["name"], code, c["mode"]=="thumb"):
        new+=1; total_ok+=1
print("NUEVAS deterministas: %d  | total en src/auto: %d / 193 ultra-limpias"%(new, total_ok))
remaining=[c["name"] for c in cands if not os.path.exists(os.path.join(AUTO,c["name"]+".c"))]
json.dump(remaining, open(os.path.join(ROOT,"build","need_agents.json"),"w"))
print("restantes (para agentes):", len(remaining))
