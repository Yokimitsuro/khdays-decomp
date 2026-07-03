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
mine,_=text_relocs(o)
md=Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)
def dis(b):
    return [(i.address,i.mnemonic+" "+i.op_str) for i in md.disasm(b,0)]
om=dis(orig); mm=dis(mine)
print("orig %d bytes / mine %d bytes"%(len(orig),len(mine)))
for i in range(max(len(om),len(mm))):
    a=om[i][1] if i<len(om) else "-"
    b=mm[i][1] if i<len(mm) else "-"
    mark="" if a==b else "  <<<"
    print("%-40s | %-40s%s"%(a,b,mark))
