import json, os, sys
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB
ROOT=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
idx=json.load(open(os.path.join(ROOT,"build","func_index.json")))
name=sys.argv[1]
e=idx[name]
b=bytes.fromhex(e['hex'])
base=int(name.split('_')[-1],16)
print("size",len(b),"relocs:",e['relocs'])
md=Cs(CS_ARCH_ARM, CS_MODE_THUMB)
# print pool constants (non-reloc words in tail)
reloc_offs=set(o for o,_ in e['relocs'])
for i in md.disasm(b, base):
    print("  %04x  %-8s %s"%(i.address, i.mnemonic, i.op_str))
