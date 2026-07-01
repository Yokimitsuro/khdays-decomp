extern char *data_ov035_020b4ca0;
extern void func_ov035_020b3b14(void *a, void *arg1, int arg2);
extern void func_ov035_020b3b24(void *a, void *arg1);

void func_ov035_020b37ec(char *a) {
    char *base = data_ov035_020b4ca0 + 0xa4;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov035_020b3b14(a, arg1, arg2);
    func_ov035_020b3b24(a, arg1);
}
