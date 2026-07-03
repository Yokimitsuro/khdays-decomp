import json,glob,sys,os
ROOT=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
# usage: namefam_multi.py <newname> <plate> <tmpl1> <tmpl2> ...
idx=json.load(open(os.path.join(ROOT,'build','func_index.json')))
newname=sys.argv[1]; plate=sys.argv[2]; tmpls=sys.argv[3:]
def canon(f):
    b=bytearray.fromhex(f['hex'])
    for off,s in f['relocs']:
        for j in range(4):
            if off+j<len(b): b[off+j]=0
    return bytes(b).hex()
mem=[]
seen=set()
for t in tmpls:
    target=canon(idx[t])
    for name,f in idx.items():
        if canon(f)!=target: continue
        if any('asm_stubs' not in p for p in glob.glob(os.path.join(ROOT,'src/overlays/*/*/%s.c'%name))):
            m=name.split('_')
            key=(m[1][2:],m[2])
            if key in seen: continue
            seen.add(key); mem.append(key)
mem.sort()
pl=plate.replace('"','\\"')
L=["from ghidra.program.model.symbol import SourceType","from ghidra.program.model.listing import CodeUnit",
"p=currentProgram; fm=p.getFunctionManager(); af=p.getAddressFactory(); lst=p.getListing()",
'from ghidra.program.model.address import AddressSet',
'PL="%s"'%pl,"NM='%s'"%newname,"DATA=["]
for ov,ad in mem: L.append('  ("arm9_ov%s","%s"),'%(ov,ad))
L+=["]","ok=0;miss=[]","for sp,ad in DATA:","    a=af.getAddressSpace(sp).getAddress(long(int(ad,16)))",
"    f=fm.getFunctionAt(a)",
"    if f is None:",
"        try: f=fm.createFunction('ov'+sp.split('_ov')[1]+'_'+NM, a, AddressSet(a), SourceType.USER_DEFINED)",
"        except: f=None",
"    if f is None: miss.append(sp+ad); continue",
"    f.setName('ov'+sp.split('_ov')[1]+'_'+NM, SourceType.USER_DEFINED)",
"    cu=lst.getCodeUnitAt(a)","    if cu is not None: cu.setComment(CodeUnit.PLATE_COMMENT, PL)","    ok+=1",
"print('named=%d missing=%s'%(ok,miss))","ti=p.getCurrentTransactionInfo()","if ti is not None:",
"    lf=ti.getClass().getDeclaredField('list'); lf.setAccessible(True); Ls=lf.get(ti)",
"    bf=ti.getClass().getDeclaredField('baseId'); bf.setAccessible(True); base=bf.get(ti)",
"    for i in range(Ls.size()):","        e=Ls.get(i); s=e.getClass().getDeclaredField('status'); s.setAccessible(True)",
"        if str(s.get(e))=='NOT_DONE':","            try: p.endTransaction(base+i,True)","            except: pass",
"try: p.getDomainFile().save(monitor); print('SAVED_OK')","except:","    import sys; print('FAIL'+str(sys.exc_info()[1]))"]
_gsdir=os.environ.get("GHIDRA_SCRIPTS_DIR",os.path.expanduser("~/ghidra_scripts"))
os.makedirs(_gsdir,exist_ok=True)
open(os.path.join(_gsdir,"NameFam.py"),"w",newline="\n").write("\n".join(L)+"\n")
print("members:",len(mem))
