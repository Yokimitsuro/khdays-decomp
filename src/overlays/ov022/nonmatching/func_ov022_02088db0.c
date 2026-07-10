/*
 * [nonmatching: 6-bit-field count re-read each iteration + 0x114 stride: mwcc computes the *(heap+0xc) base into a held reg where the original uses an immediate offset (4B over)]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted register
 * allocation / scheduling. Left uncarved (byte-exact in the blob).
 */
extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_0202a7dc(int arg0);
extern void NNSi_FndFreeFromDefaultHeap(int arg0);

void func_ov022_02088db0(int arg0, int arg1, int arg2, int arg3) {
    int h = NNSi_FndGetCurrentRootHeap();
    int i = 0;
    if ((int)(((unsigned int)(*(unsigned char *)h << 0x18)) >> 0x1a) > 0) {
        int off = 0;
        do {
            func_0202a7dc(*(int *)(h + 0xc) + off + 4);
            i = i + 1;
            off = off + 0x114;
        } while (i < (int)(((unsigned int)(*(unsigned char *)h << 0x18)) >> 0x1a));
    }
    NNSi_FndFreeFromDefaultHeap(*(int *)(h + 0xc));
}
