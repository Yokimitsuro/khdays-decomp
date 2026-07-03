import sys, os, json
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB
ROOT=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
cpath, name = sys.argv[1], sys.argv[2]
idx=json.load(open(os.path.join(ROOT,"build","func_index.json")))
orig=bytes.fromhex(idx[name]["hex"])
o=compile_c(cpath, True)
mine,_=text_relocs(o)
md=Cs(CS_ARCH_ARM, CS_MODE_THUMB)
def dis(b):
    return [i.mnemonic+" "+i.op_str for i in md.disasm(b,0)]
om=dis(orig); mm=dis(mine)
print("orig %d / mine %d"%(len(orig),len(mine)))
for i in range(max(len(om),len(mm))):
    a=om[i] if i<len(om) else "-"
    b=mm[i] if i<len(mm) else "-"
    print("%-34s | %-34s%s"%(a,b,"" if a==b else "  <<<"))
