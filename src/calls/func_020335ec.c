extern int data_0204c234;
extern unsigned char *func_02032cbc(int a);
extern void func_02032be8(int a, int b, int c);

int func_020335ec(int param_1) {
    int base = data_0204c234;
    if (*(short *)(base + 0xb46f6) != param_1 ||
        *(unsigned char *)(base + 0xb479e) == 1) {
        unsigned char *p = func_02032cbc(0);
        if (p == 0 || *p != 2) {
            func_02032be8(2, param_1, 0);
        } else {
            p[1] = (unsigned char)param_1;
        }
    }
    return 1;
}
