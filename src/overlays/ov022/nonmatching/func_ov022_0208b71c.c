/*
 * [nonmatching: the original spills param_4 to the pushed-r3 scratch slot and reloads it; mwcc keeps it in a callee-saved reg (4B short)]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted register
 * allocation / scheduling. Left uncarved (byte-exact in the blob).
 */
extern int NNSi_FndAllocFromDefaultExpHeap(int arg0);

int func_ov022_0208b71c(int arg0, int arg1, unsigned char arg2, unsigned char arg3, int arg4) {
    int slot = arg0 + 0x18;
    int idx = arg1 * 4;
    unsigned char *p;
    int k = 0x112;
    *(int *)(slot + idx) = NNSi_FndAllocFromDefaultExpHeap(arg4);
    p = *(unsigned char **)(slot + idx);
    p[0] = (char)arg1;
    p[2] = 0;
    p[k] = arg2;
    p[k - 1] = arg3;
    *(short *)(p + k + 2) = (short)0xffff;
    return *(int *)(slot + idx);
}
