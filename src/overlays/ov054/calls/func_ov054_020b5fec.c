extern char *data_ov054_020b74a0;
extern void func_ov054_020b6314(void *a, void *arg1, int arg2);
extern void func_ov054_020b6324(void *a, void *arg1);

void func_ov054_020b5fec(char *a) {
    char *base = data_ov054_020b74a0 + 0xa4;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov054_020b6314(a, arg1, arg2);
    func_ov054_020b6324(a, arg1);
}
