"""Recoge TODOS los parks cuya unica diferencia es una PERMUTACION DE REGISTROS:
   mismo numero de instrucciones, mismos mnemonicos, misma estructura de operandos,
   y solo cambian los numeros de registro. Luego extrae la biyeccion ROM->mwcc de
   cada uno para buscar una regla.
"""
import json, os, re, sys, glob
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor

ROOT = r"E:\KH 3582\decomp"
sys.path.insert(0, os.path.join(ROOT, "tools"))
import _argprobe as P
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

REG = re.compile(r"\b(r\d+|sl|sb|fp|ip|lr|sp|pc)\b")


def norm(ins):
    """instruccion con los registros sustituidos por # (para comparar la forma)"""
    return REG.sub("#", ins)


def regs_of(ins):
    return REG.findall(ins)


def analyse(case):
    name, cpath, mode = case
    th = (mode == "thumb")
    base = P.build(cpath, name, th, 980)
    if not base:
        return None
    mine = base[0]
    e = P.IDX[name]
    orig = bytearray.fromhex(e["hex"])
    if len(mine) != len(orig):
        return None
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if th else CS_MODE_ARM)
    o = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(orig), 0)]
    m = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(mine), 0)]
    if len(o) != len(m) or not o:
        return None
    # misma forma en TODAS las instrucciones?
    if any(norm(a) != norm(b) for a, b in zip(o, m)):
        return None
    # extrae la biyeccion
    pairs = set()
    diff = 0
    for a, b in zip(o, m):
        ra, rb = regs_of(a), regs_of(b)
        if len(ra) != len(rb):
            return None
        for x, y in zip(ra, rb):
            if x != y:
                diff += 1
            pairs.add((x, y))
    if diff == 0:
        return None
    mapping = defaultdict(set)
    for x, y in pairs:
        mapping[x].add(y)
    consistent = all(len(v) == 1 for v in mapping.values())
    return (name, mode, len(o), diff, consistent,
            {k: list(v)[0] for k, v in sorted(mapping.items()) if list(v)[0] != k})


rank = json.load(open(os.path.join(ROOT, "build", "try", "rank.json")))
cases = [(x[0], x[1], x[2]) for x in rank if os.path.exists(x[1])]
print("parks a examinar:", len(cases))
hits = []
with ThreadPoolExecutor(max_workers=10) as ex:
    for r in ex.map(analyse, cases):
        if r:
            hits.append(r)

print("parks que son PURA permutacion de registros:", len(hits))
print()
hits.sort(key=lambda r: r[2])
for name, mode, ni, diff, cons, mp in hits:
    print("  %-32s %s %3d instr  %2d campos  biyectiva=%s" % (name, mode, ni, diff, cons))
    print("        ROM->mias: %s" % mp)

print()
print("=== estadistica de los mapeos ===")
c = Counter()
for _n, _m, _i, _d, _c, mp in hits:
    for k, v in mp.items():
        c[(k, v)] += 1
for (k, v), n in c.most_common(20):
    print("   %-4s -> %-4s  x%d" % (k, v, n))
