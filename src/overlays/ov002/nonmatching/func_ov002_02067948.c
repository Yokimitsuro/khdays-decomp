/* PROVEN TIE (THUMB register coloring). Byte-identical logic to the ROM (dedup
 * twin of func_ov025_020b0818), but mwcc build 139 colors count/result/i/node to
 * r3/r6/r5/r4 where the ROM uses r6/r4/r3/r5; same size, only the low-register
 * assignment differs. Declaration reorder does not flip it. Kept here so the ov002
 * blob stays byte-exact. */
int func_ov002_02067948(int param_1, int param_2) {
    unsigned int count = *(unsigned int *)(param_1 + 0x10);
    int node = *(int *)(param_1 + 4);
    unsigned int i;
    int result = 0;
    for (i = 0; i < count; i++) {
        if (*(unsigned short *)(node + 0xc) == param_2) {
            *(int *)(param_1 + 8) = node;
            *(int *)(param_1 + 0xc) = node + *(int *)(node + 8);
            result = 1;
            break;
        }
        node += *(int *)node;
    }
    return result;
}
