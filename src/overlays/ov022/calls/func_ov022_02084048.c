/* Reset the ov022 block held on the current root heap and, on a cold start
 * (mode 0), rebuild it from the sequence archive: register the archive, take
 * its list, and hand that list to the two sub-builders at +0x3c and +0xe8.
 * The mode is remembered at +0x2c. Returns the module's entry point. */
extern int data_ov022_020b28e8;

extern int *NNSi_FndGetCurrentRootHeap(void);
extern void *SND_RegisterSeq(void *archive, int id);
extern void func_0201f390(int phase);
extern void *func_0201f634(void *seq, int a);
extern int func_020255bc(void *list, int a);
extern void func_ov022_02086318(void *dst, void *list);
extern void func_ov022_02085f9c(void *dst, void *list);
extern void func_0201f5ac(void *seq);
extern void func_ov022_020840e0(void);

void *func_ov022_02084048(int mode) {
    int *ctx = NNSi_FndGetCurrentRootHeap();

    ctx[0] = 0x2a;
    ctx[1] = 0;
    ctx[0x30 / 4] = 0;
    ctx[0x34 / 4] = 0;
    ctx[0x38 / 4] = 0;

    if (mode == 0) {
        void *seq = SND_RegisterSeq(&data_ov022_020b28e8, 0xf);
        void *list;

        func_0201f390(0);
        list = func_0201f634(seq, 1);
        func_0201f390(1);
        func_020255bc(list, 7);
        func_ov022_02086318((char *)ctx + 0x3c, list);
        func_ov022_02085f9c((char *)ctx + 0xe8, list);
        func_0201f5ac(seq);
    }

    ctx[0x2c / 4] = (mode != 0) ? 1 : 0;
    ctx[0x230 / 4] = 0;
    return (void *)&func_ov022_020840e0;
}
