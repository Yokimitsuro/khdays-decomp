extern char *data_ov095_020bcba0;
extern void func_ov095_020bb42c(void *a, void *arg1, int arg2);
extern void func_ov095_020bb478(void *a, void *arg1);

void func_ov095_020bb074(char *a) {
    char *base = data_ov095_020bcba0 + 0xd4;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov095_020bb42c(a, arg1, arg2);
    func_ov095_020bb478(a, arg1);
}
