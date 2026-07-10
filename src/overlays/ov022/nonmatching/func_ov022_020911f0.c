/*
 * [nonmatching: reloaded-base r0/r1 coloring on the *count+=1 RMW after the guard call (sibling of 02092320)]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted register
 * allocation / scheduling. Left uncarved (byte-exact in the blob).
 */
extern void func_02030cf8(int arg0, int arg1);
extern void MIi_CpuClearFast(int value, void *dest, int size);
extern int data_ov022_020b2ea8;
extern void func_ov022_02090a50(void);

void func_ov022_020911f0(unsigned int *arg0, unsigned int arg1, unsigned int arg2) {
    if (*(int *)&data_ov022_020b2ea8 == 0) {
        func_02030cf8(9, (int)func_ov022_02090a50);
    }
    *(int *)&data_ov022_020b2ea8 = *(int *)&data_ov022_020b2ea8 + 1;
    MIi_CpuClearFast(0, arg0, 0x30);
    arg0[0] = arg1;
    arg0[1] = arg2;
}
