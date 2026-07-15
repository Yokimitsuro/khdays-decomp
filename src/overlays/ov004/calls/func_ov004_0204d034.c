/* Walk the same count-prefixed variable-stride record list, pick the best record whose
 * [rec[3],rec[4]] range contains param_3+1 (or that starts above param_3), preferring the
 * smallest rec[3]; if one is found, build a node via func_ov004_0204cb74 and append it to
 * the list at param_1+0x18. Returns whether a record was appended. */
extern int *func_ov004_0204cb74(unsigned short *rec, short *sub);
extern void NNS_FndAppendListObject(void *list, int *obj);
int func_ov004_0204d034(int param_1, unsigned short *param_2, unsigned int param_3, unsigned int param_4) {
    int i;
    int found = 0;
    short *bestSub = 0;
    unsigned short *best = 0;
    int count = *param_2++;
    for (i = 0; i < count; i++) {
        unsigned int lo = param_2[3];
        if ((lo <= param_3 + 1 && param_3 + 1 <= param_2[4]) || param_3 < lo) {
            if (best == 0 || lo < best[3]) {
                best = param_2;
                bestSub = (short *)(param_2 + 0x18);
            }
        }
        param_2 = (unsigned short *)((char *)param_2 + *param_2);
    }
    if (best != 0) {
        int *node = func_ov004_0204cb74(best, bestSub);
        NNS_FndAppendListObject((void *)(param_1 + 0x18), node);
        found = 1;
    }
    return found;
}
