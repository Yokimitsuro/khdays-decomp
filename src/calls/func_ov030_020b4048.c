extern int func_01fff774();
extern int func_02014dc4();
extern int func_0202accc();

void func_ov030_020b4048(int r0, int r1) {
    int i;
    for (i = 0; i < 5; i++) {
        if (((int *)r0)[i + 3] != 0) {
            func_02014dc4(r0 + 0x20);
            ((int *)r0)[i + 3] = 0;
        }
        func_0202accc(r0, i, r0 + 0x108, (short)r1);
        func_01fff774(r0, i, 0);
    }
}
