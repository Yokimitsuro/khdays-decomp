"""Last instruction: the ROM zeroes the tag between the list lookup and the
null test, not before the call, so the initialiser belongs after the lookup
rather than on the declaration.
"""
p = "build/try/func_ov002_0205bff4.c"
s = open(p).read()

OLD = """        u16 *pEntry;
        int nTag = 0;
        int nSlot;

        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nOld);
        if (pEntry != 0) {
"""
NEW = """        u16 *pEntry;
        int nTag;
        int nSlot;

        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nOld);
        nTag = 0;
        if (pEntry != 0) {
"""
assert OLD in s
open(p, "w").write(s.replace(OLD, NEW))
print("patched")
