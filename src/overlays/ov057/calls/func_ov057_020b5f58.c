extern char *data_ov057_020b74a0;
extern void func_ov057_020b619c(void *a, void *arg1, int arg2);
extern void func_ov057_020b626c(void *a, void *arg1);

void func_ov057_020b5f58(char *a) {
    char *base = data_ov057_020b74a0 + 0x2c;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov057_020b619c(a, arg1, arg2);
    func_ov057_020b626c(a, arg1);
}
