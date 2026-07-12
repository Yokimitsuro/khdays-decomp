/* PROVEN TIE (predication density). mwcc build 139 predicates the compound
 * match (cmpeq r4,r5; moveq r0,r1; popeq) where the ROM branches on the +0x10
 * field being nonzero (bne to the count++). Nested-if, &&, and goto forms all
 * predicate identically. Kept here so the ov008 blob stays byte-exact. */
extern void *NNS_FndGetNextListObject(void *list, void *obj);

void *func_ov008_020565f8(int param_1, int param_2) {
    int count = 0;
    void *obj = NNS_FndGetNextListObject((void *)(param_1 + 0x18), 0);
    while (obj != 0) {
        if (*(int *)((char *)obj + 0x10) == 0 && count == param_2) {
            return obj;
        }
        count++;
        obj = NNS_FndGetNextListObject((void *)(param_1 + 0x18), obj);
    }
    return obj;
}
