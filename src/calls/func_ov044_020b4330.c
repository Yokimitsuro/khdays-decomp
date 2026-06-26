extern int func_0202accc();
extern int func_01fff774();

void func_ov044_020b4330(int *r0) {
    char *p = (char *)r0;
    *(int *)(p + 0x124) = 1;
    func_0202accc(p + 0x128, 0, p + 0x208, 0);
    func_0202accc(p + 0x128, 2, p + 0x208, 0);
    func_0202accc(p + 0x128, 1, p + 0x208, 0);
    func_01fff774(p + 0x128, 0, 0);
    func_01fff774(p + 0x128, 2, 0);
    func_01fff774(p + 0x128, 1, 0);
}
