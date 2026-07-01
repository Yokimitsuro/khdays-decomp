extern char *data_ov059_020b7320;
extern void func_ov059_020b61c0(void *a, void *arg1, int arg2);
extern void func_ov059_020b61fc(void *a, void *arg1);

void func_ov059_020b5e20(char *a) {
    char *base = data_ov059_020b7320 + 0xc50;
    char *arg1 = base + 0x2000;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov059_020b61c0(a, arg1, arg2);
    func_ov059_020b61fc(a, arg1);
}
