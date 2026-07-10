/*
 * [nonmatching: table pointer / counter r4<->r6 coloring swap around the indirect call; structurally byte-identical]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted register
 * allocation / scheduling. Left uncarved (byte-exact in the blob).
 */
extern void func_0202a7dc(int arg0);
extern void NNSi_FndFreeFromDefaultHeap(int arg0);
extern int data_ov022_020b2ad4;

void func_ov022_02090198(unsigned short *arg0, int arg1, int arg2, int arg3) {
    if ((*arg0 & 1) != 0) {
        int *tbl = &data_ov022_020b2ad4;
        int i = 0;
        do {
            if (*(int *)((char *)arg0 + 0x18) != 0) {
                void (*fn)(void) = (void (*)(void))*tbl;
                if (fn != 0) fn();
                func_0202a7dc(*(int *)((char *)arg0 + 0x18) + 8);
                NNSi_FndFreeFromDefaultHeap(*(int *)((char *)arg0 + 0x18));
            }
            i = i + 1;
            arg0 = arg0 + 2;
            tbl = tbl + 1;
        } while (i < 0xf);
    }
}
