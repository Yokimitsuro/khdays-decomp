import sys, os, json
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB
ROOT=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
cpath, name = sys.argv[1], sys.argv[2]
thumb="--thumb" in sys.argv
idx=json.load(open(os.path.join(ROOT,"build","func_index.json")))
orig=bytes.fromhex(idx[name]["hex"])
o=compile_c(cpath, thumb)
mine,mrel=text_relocs(o)
md=Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)
def dis(b):
    return [(i.address,i.size,i.mnemonic+" "+i.op_str) for i in md.disasm(b,0)]
# Raw bytes with every relocated word masked on both sides: a literal can disassemble to the same
# text with different bytes (0x991 and 0x2991 are both "muleq r0, r1, sb"), so compare bytes too.
rel=set(off for off,_ in idx[name]["relocs"])|set(mrel)
def masked(b):
    b=bytearray(b)
    for off in rel:
        b[off:off+4]=bytes(len(b[off:off+4]))
    return bytes(b)
ob=masked(orig); mb=masked(mine)
om=dis(orig); mm=dis(mine)
print("orig %d bytes / mine %d bytes"%(len(orig),len(mine)))
for i in range(max(len(om),len(mm))):
    a=om[i][2] if i<len(om) else "-"
    b=mm[i][2] if i<len(mm) else "-"
    raw=i<len(om) and i<len(mm) and om[i][0]==mm[i][0] and         ob[om[i][0]:om[i][0]+om[i][1]]!=mb[mm[i][0]:mm[i][0]+mm[i][1]]
    if a==b and raw:
        a+=" [%s]"%orig[om[i][0]:om[i][0]+om[i][1]].hex(); b+=" [%s]"%mine[mm[i][0]:mm[i][0]+mm[i][1]].hex()
    mark="" if a==b and not raw else "  <<<"
    print("%-40s | %-40s%s"%(a,b,mark))
