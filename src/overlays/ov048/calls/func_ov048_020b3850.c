extern char *data_ov048_020b4b80;
extern void func_ov048_020b3a5c(void *a, void *arg1, int arg2);
extern void func_ov048_020b3a94(void *a, void *arg1);

void func_ov048_020b3850(char *a) {
    char *base = data_ov048_020b4b80 + 0x2c;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov048_020b3a5c(a, arg1, arg2);
    func_ov048_020b3a94(a, arg1);
}
