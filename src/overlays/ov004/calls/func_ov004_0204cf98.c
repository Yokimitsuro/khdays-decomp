/* Walk a count-prefixed variable-stride record list (param_2: u16 count, then records
 * each advanced by their own leading u16 size). For every record whose predicate
 * param_4(rec, param_3) is nonzero, build a node via func_ov004_0204cb74 and append it
 * to the list at param_1+0x18; return how many appended nodes had node[4]==0. */
extern int *func_ov004_0204cb74(unsigned short *rec, short *sub);
extern void NNS_FndAppendListObject(void *list, int *obj);
unsigned short func_ov004_0204cf98(int param_1, unsigned short *param_2, int param_3,
                                   int (*param_4)(unsigned short *, int)) {
    int i;
    unsigned short added = 0;
    int count = *param_2++;
    for (i = 0; i < count; i++) {
        if (param_4(param_2, param_3)) {
            int *node = func_ov004_0204cb74(param_2, (short *)(param_2 + 0x18));
            NNS_FndAppendListObject((void *)(param_1 + 0x18), node);
            if (node[4] == 0) {
                added++;
            }
        }
        param_2 = (unsigned short *)((char *)param_2 + *param_2);
    }
    return added;
}
