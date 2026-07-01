extern char *data_ov073_020ba540;
extern void func_ov073_020ba1fc(void *a, void *arg1, int arg2);
extern void func_ov073_020ba370(void *a, void *arg1);

void func_ov073_020b8b50(char *a) {
    char *base = data_ov073_020ba540 + 0xe4;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov073_020ba1fc(a, arg1, arg2);
    func_ov073_020ba370(a, arg1);
}
