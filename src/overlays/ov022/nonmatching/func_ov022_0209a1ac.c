/*
 * [nonmatching: predicate-vs-branch structural: the bit-flag OR-accumulator (5 guarded r|=K) is predicated inline by mwcc (112B) where the original branches each guard out of line (184B)]
 *
 * Equivalent C; mwcc 3.0/139 diverges only in the noted codegen. Left uncarved.
 */
void func_ov022_0209a1ac(unsigned int *arg0) {
    unsigned int v = arg0[0x119];
    unsigned int r = (v & 0x20) != 0;
    if ((v & 0x40000000) != 0) {
        r = r | 2;
    }
    if ((*arg0 & 0x80000) != 0 || 0 < (int)arg0[0x12d]) {
        r = r | 0x20;
    }
    if ((v & 0x8000000) != 0 || (v & 0x10000000) != 0) {
        r = r | 4;
    }
    if ((arg0[9] & 4) != 0) {
        r = r | 8;
    }
    if (r != 0) {
        *(unsigned int *)(arg0[0x13b] + 0x1e4) = *(unsigned int *)(arg0[0x13b] + 0x1e4) | r;
    }
}
