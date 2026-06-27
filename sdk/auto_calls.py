#!/usr/bin/env python3
"""Auto-decomp determinista para funciones CON calls.

Patrones cubiertos (todos `arm`, mwcc 3.0 b139 -O4,p, args via r0..r3):
  A) push {r3|r4,lr}; bl X; pop {r3|r4,pc}                 -> void f(...) { X(...); }
  B) push {r3|r4,lr}; bl A; bl B [; bl C ...]; pop {.,pc}  -> void f(...) { A(); B(); ... }
  C) ...; mov r0,#K (final); pop {.,pc}                     -> int  f(...) { ...; return K; }
  D) push {r3,lr}; bl X; cmp r0,#0; ldmeqia sp!, {r3,pc};
     bl Y; pop {r3,pc}                                      -> int  f(...) { int r=X(); if(r) Y(); return r; }
  E) bl X (tail-call, no push)                              -> void f(...) { X(...); }

Verifier (NO usa tools/match.py): compila el C, extrae bytes del .o, enmascara
4 bytes en cada reloc-offset, compara contra func_index.json[func_X]. NO exige
que los nombres de callees coincidan (los delinks aun no estan regenerados con
los nuevos nombres SDK). Si la forma + relocs + bytes-enmascarados coinciden,
el wrapper es byte-exacto.

Output: src/calls/<NEW_NAME>.c + actualiza build/decompiled.txt.
"""
import json, os, re, sys, subprocess
from collections import Counter, defaultdict
from elftools.elf.elffile import ELFFile

ROOT  = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CALLS = json.load(open(os.path.join(ROOT, "build", "calls.json")))
INDEX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
NAMES = json.load(open(os.path.join(ROOT, "sdk", "build", "names.json")))
DONE  = set(open(os.path.join(ROOT, "build", "decompiled.txt")).read().split())
MWCC  = os.path.join(ROOT, "tools", "mwccarm", "3.0_patch4", "mwccarm.exe")
LIC   = os.path.join(ROOT, "tools", "mwccarm", "license.dat")
FLAGS = ["-O4,p","-proc","arm946e","-interworking","-lang","c99","-enum","int",
         "-char","signed","-inline","on,noauto","-Cpp_exceptions","off","-gccext,on"]
ENV   = dict(os.environ, LM_LICENSE_FILE=LIC)
OUTDIR= os.path.join(ROOT, "src", "calls")
MANIFEST = os.path.join(ROOT, "build", "decompiled.txt")

# ---------- name mapping (replay apply_names rules) ----------
def build_src_final():
    counts=Counter(NAMES.values()); by_name=defaultdict(list)
    for k,v in NAMES.items():
        m=re.match(r"^func_(ov\d+_)?([0-9a-f]{8})$", k)
        if not m: continue
        addr=int(m.group(2),16); info=INDEX.get(k,{})
        sz=info.get("size",0); rl=info.get("relocs",[])
        if counts[v]>1 and sz<=16 and not rl: continue
        by_name[v].append((addr,k))
    out={}
    for sdk,lst in by_name.items():
        lst.sort(); out[lst[0][1]]=sdk
        for addr,k in lst[1:]: out[k]="%s_0x%08x"%(sdk,addr)
    return out

SRC_FINAL = build_src_final()  # func_X -> renamed
def display(fname):
    return SRC_FINAL.get(fname, fname)

# ---------- patterns ----------
INSTR_RE = re.compile(r"\s*;\s*")
def split_asm(asm):
    # Drop literal pools / labels (lines after `.L_` or `.word`)
    return [i.strip() for i in INSTR_RE.split(asm) if i.strip()]

def is_push_pop(i, mn, regs):
    """match 'stmdb sp!, {<regs>, lr}' or 'push {<regs>, lr}' for push;
    'ldmia sp!, {<regs>, pc}' or 'pop {<regs>, pc}' for pop."""
    if mn == "push":
        return i in ("stmdb sp!, {%s, lr}" % regs, "push {%s, lr}" % regs)
    else:
        return i in ("ldmia sp!, {%s, pc}" % regs, "pop {%s, pc}" % regs)

CALL_RE = re.compile(r"^bl(?:x)?\s+(func_(?:ov\d+_)?[0-9a-f]{8})$")
def call_target(i):
    m=CALL_RE.match(i.strip())
    return m.group(1) if m else None

def pat_pure_wrapper(ins, c):
    """A/B: push {r3|r4,lr}; bl C1; bl C2; ... bl CN; pop {r3|r4,pc}"""
    if len(ins) < 3: return None
    for reg in ("r3","r4"):
        if not (("stmdb sp!, {%s, lr}"%reg) in ins[0] or ("push {%s, lr}"%reg) in ins[0]): continue
        if not (("ldmia sp!, {%s, pc}"%reg) in ins[-1] or ("pop {%s, pc}"%reg) in ins[-1]): continue
        mid = ins[1:-1]
        callees=[]
        for m in mid:
            t = call_target(m)
            if not t: return None
            callees.append(t)
        if not callees: return None
        body = "\n    ".join("%s();" % display(c) for c in callees)
        decls = "\n".join("extern void %s();" % display(c) for c in set(callees))
        name = display(c["name"])
        return decls + "\n\nvoid %s(void)\n{\n    %s\n}\n" % (name, body)
    return None

def pat_pure_wrapper_const_return(ins, c):
    """C: push {r3|r4,lr}; bl C1; ... ; mov r0,#K; pop {.,pc}   (returns K)"""
    if len(ins) < 4: return None
    for reg in ("r3","r4"):
        if not (("stmdb sp!, {%s, lr}"%reg) in ins[0] or ("push {%s, lr}"%reg) in ins[0]): continue
        if not (("ldmia sp!, {%s, pc}"%reg) in ins[-1] or ("pop {%s, pc}"%reg) in ins[-1]): continue
        # last instr before pop must be mov r0,#K
        mret = re.fullmatch(r"mov r0, #(-?(?:0x)?[0-9a-fA-F]+)", ins[-2])
        if not mret: return None
        K = int(mret.group(1), 0)
        # middle must be all bl <func_X>
        callees=[]
        for m in ins[1:-2]:
            t = call_target(m)
            if not t: return None
            callees.append(t)
        if not callees: return None
        body = "\n    ".join("%s();" % display(c) for c in callees) + "\n    return %d;" % K
        decls = "\n".join("extern void %s();" % display(c) for c in set(callees))
        name = display(c["name"])
        return decls + "\n\nint %s(void)\n{\n    %s\n}\n" % (name, body)
    return None

def pat_tail_call(ins, c):
    """E: single 'b func_X' (4-byte tail call). NOT bl."""
    if len(ins)!=1: return None
    m = re.fullmatch(r"b\s+(func_(?:ov\d+_)?[0-9a-f]{8})", ins[0].strip())
    if not m: return None
    t = m.group(1)
    name = display(c["name"])
    return "extern void %s();\n\nvoid %s(void)\n{\n    %s();\n}\n" % (display(t), name, display(t))

def pat_cond_skip_call(ins, c):
    """D: push {r3,lr}; bl A; cmp r0,#0; pop-eq; bl B; pop
       -> void f(...){ if (A(...)) B(); }   (A returns int, return discarded)"""
    if len(ins) != 6: return None
    if ins[0] not in ("stmdb sp!, {r3, lr}", "push {r3, lr}"): return None
    if ins[-1] not in ("ldmia sp!, {r3, pc}", "pop {r3, pc}"): return None
    A = call_target(ins[1])
    if not A: return None
    if ins[2] != "cmp r0, #0x0": return None
    if ins[3] not in ("ldmeqia sp!, {r3, pc}", "popeq {r3, pc}"): return None
    B = call_target(ins[4])
    if not B: return None
    name = display(c["name"])
    return ("extern int %s();\nextern void %s();\n\nvoid %s(void)\n{\n    if (%s()) %s();\n}\n"
            % (display(A), display(B), name, display(A), display(B)))

def pat_save_two_args_two_calls(ins, c):
    """B': push {r3,r4,r5,lr}; mov r5,r0; mov r4,r1; bl A; mov r0,r5; mov r1,r4; bl B; pop
       -> void f(int a, int b){ A(a,b); B(a,b); }   (8 instructions)"""
    if len(ins) != 8: return None
    if ins[0] not in ("stmdb sp!, {r3, r4, r5, lr}", "push {r3, r4, r5, lr}"): return None
    if ins[-1] not in ("ldmia sp!, {r3, r4, r5, pc}", "pop {r3, r4, r5, pc}"): return None
    if ins[1] != "mov r5, r0" or ins[2] != "mov r4, r1": return None
    A = call_target(ins[3])
    if not A: return None
    if ins[4] != "mov r0, r5" or ins[5] != "mov r1, r4": return None
    B = call_target(ins[6])
    if not B: return None
    name = display(c["name"])
    decls = set([display(A), display(B)])
    decls_s = "\n".join("extern void %s(int, int);" % d for d in decls)
    return decls_s + ("\n\nvoid %s(int a, int b)\n{\n    %s(a, b);\n    %s(a, b);\n}\n"
                      % (name, display(A), display(B)))

PATTERNS = [
    ("tail", pat_tail_call),
    ("cond_skip_call", pat_cond_skip_call),
    ("save_two_args_two_calls", pat_save_two_args_two_calls),
    ("pure_wrapper_const_ret", pat_pure_wrapper_const_return),
    ("pure_wrapper", pat_pure_wrapper),
]

# ---------- compile + verify ----------
def compile_c(cpath):
    o = cpath + ".o"
    r = subprocess.run([MWCC, "-c", *FLAGS, "-o", o, cpath],
                       capture_output=True, text=True, env=ENV)
    return o, r.returncode, (r.stdout+r.stderr).strip()

def text_relocs(opath, sym_name):
    e = ELFFile(open(opath, "rb"))
    secs = list(e.iter_sections()); st = e.get_section_by_name(".symtab")
    bytes_=None; shndx=None
    for sym in st.iter_symbols():
        if sym.name==sym_name and sym["st_info"]["type"]=="STT_FUNC" and sym["st_size"]>0:
            sh=sym["st_shndx"]
            bytes_=bytes(secs[sh].data()[sym["st_value"]:sym["st_value"]+sym["st_size"]])
            shndx=sh; break
    if bytes_ is None: return None, None
    offs=set()
    for s in e.iter_sections():
        if s.name.startswith(".rel") and s["sh_info"]==shndx:
            for rr in s.iter_relocations(): offs.add(rr["r_offset"])
    return bytes_, offs

def verify(cpath, sym_name, orig_key):
    o, rc, msg = compile_c(cpath)
    if rc != 0: return False, "compile fail: "+msg[:200]
    mb, my_offs = text_relocs(o, sym_name)
    if mb is None: return False, "sym %s missing in .o" % sym_name
    orig = INDEX[orig_key]
    ob = bytes.fromhex(orig["hex"]); orig_offs={off for off,_ in orig["relocs"]}
    sz = len(ob)
    if len(mb)<sz: return False, "compiled shorter (%d<%d)" % (len(mb),sz)
    mb=bytearray(mb[:sz]); ob=bytearray(ob)
    for off in my_offs|orig_offs:
        for k in range(4):
            if off+k<sz: mb[off+k]=0; ob[off+k]=0
    if bytes(mb)!=bytes(ob): return False, "byte diff after mask"
    if my_offs!=orig_offs: return False, "reloc offsets differ %s vs %s" % (sorted(my_offs), sorted(orig_offs))
    return True, "ok"

# ---------- main ----------
def main():
    candidates=[]
    for c in CALLS:
        fn=c["name"]
        if display(fn) in DONE: continue
        candidates.append(c)
    print("undecompiled call-funcs:", len(candidates))

    new_done = []
    by_pat = Counter(); fail_by_pat = Counter()
    for c in candidates:
        ins = split_asm(c["asm"])
        # strip literal-pool tails / label lines
        ins = [i for i in ins if not i.startswith(".L_") and not i.startswith(".word")]
        for pat_name, fn in PATTERNS:
            src = fn(ins, c)
            if src is None: continue
            sym_name = display(c["name"])
            cpath = os.path.join(OUTDIR, sym_name + ".c")
            if os.path.exists(cpath):
                break  # already exists, skip
            # write tentatively
            with open(cpath, "w") as f: f.write(src)
            ok, msg = verify(cpath, sym_name, c["name"])
            if ok:
                by_pat[pat_name] += 1
                new_done.append(sym_name)
                # cleanup .o
                try: os.remove(cpath + ".o")
                except OSError: pass
                break
            else:
                # revert tentative file on fail
                fail_by_pat[pat_name] += 1
                try:
                    os.remove(cpath)
                    os.remove(cpath + ".o")
                except OSError: pass
                continue

    print("\n== matches per pattern ==")
    for p,n in by_pat.most_common():
        print("  %-25s %d  (%d fail)" % (p, n, fail_by_pat.get(p,0)))
    print("\nTOTAL new decompiled (byte-exact verified): %d" % len(new_done))

    if new_done:
        with open(MANIFEST, "a") as f:
            f.write("\n".join(new_done) + "\n")
        print("appended %d names to build/decompiled.txt" % len(new_done))

if __name__ == "__main__":
    main()
