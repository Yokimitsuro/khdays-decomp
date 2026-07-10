/*
 * [nonmatching: nested-loop coloring + guard branch-sense tie: outer walk / inner counter register allocation and the ldrb+ble entry test do not both reproduce]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted
 * register allocation / block layout. Left uncarved (byte-exact in the blob).
 */
extern void func_ov002_02050cf4(int arg0);
extern void NNSi_FndFreeFromDefaultHeap(int arg0);
extern int data_ov022_020b2ec0;

void func_ov022_020b1fc4(char *arg0) {
    char *pc = arg0;
    int outer = 0;
    do {
        int i = 0;
        if ((int)*(unsigned char *)(arg0 + 1) > 0) {
            int off = 0;
            do {
                func_ov002_02050cf4(*(int *)(pc + 0xc) + off);
                i = i + 1;
                off = off + 0x30;
            } while (i < *(unsigned char *)(arg0 + 1));
        }
        NNSi_FndFreeFromDefaultHeap(*(int *)(pc + 0xc));
        pc = pc + 0xc;
        outer = outer + 1;
    } while (outer < 4);
    if (*arg0 == 0) {
        *(int *)&data_ov022_020b2ec0 = 0;
    } else if (*arg0 == 1) {
        ((int *)&data_ov022_020b2ec0)[1] = 0;
    }
}
