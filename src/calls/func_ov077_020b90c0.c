extern int func_0202accc(int, unsigned short, int, short);
extern int func_01fff774(int, unsigned short, int);

void func_ov077_020b90c0(int r0, int r1) {
    int i;
    for (i = 0; i < 5; i++) {
        func_0202accc(r0 + 4, i, r0 + 0xe4, (short)r1);
        func_01fff774(r0 + 4, i, 0);
    }
}
