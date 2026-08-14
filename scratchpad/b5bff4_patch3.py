"""Case 3: the ROM tests the entry for null twice, once to decide the tag and
once to decide the slot, and it zeroes the tag only at the start rather than
before each entry. The candidate merged both tests into one if/else.
"""
p = "build/try/func_ov002_0205bff4.c"
s = open(p).read()

OLD = """        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nOld);
        if (pEntry == 0) {
            nSlot = -1;
        } else {
            nTag = func_ov002_0206dc10(pEntry[1] & 0xff);
            nSlot = func_ov002_0205a540(*pEntry);
        }
        func_ov002_0205b0dc(s->listEntries, nSlot, nFrom, nOld, 1, 1, 0, nTag);

        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nNew);
        if (pEntry == 0) {
            nSlot = -1;
        } else {
            nTag = func_ov002_0206dc10(pEntry[1] & 0xff);
            nSlot = func_ov002_0205a540(*pEntry);
        }
"""
NEW = """        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nOld);
        if (pEntry != 0) {
            nTag = func_ov002_0206dc10(pEntry[1] & 0xff);
        }
        if (pEntry == 0) {
            nSlot = -1;
        } else {
            nSlot = func_ov002_0205a540(*pEntry);
        }
        func_ov002_0205b0dc(s->listEntries, nSlot, nFrom, nOld, 1, 1, 0, nTag);

        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nNew);
        if (pEntry != 0) {
            nTag = func_ov002_0206dc10(pEntry[1] & 0xff);
        }
        if (pEntry == 0) {
            nSlot = -1;
        } else {
            nSlot = func_ov002_0205a540(*pEntry);
        }
"""
assert OLD in s
open(p, "w").write(s.replace(OLD, NEW))
print("patched")
