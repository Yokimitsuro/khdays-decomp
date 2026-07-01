extern char *data_ov037_020b4e20;
extern void func_ov037_020b4360(void *a, void *arg1, int arg2);
extern void func_ov037_020b455c(void *a, void *arg1);

void func_ov037_020b3730(char *a) {
    char *base = data_ov037_020b4e20 + 0x2c;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov037_020b4360(a, arg1, arg2);
    func_ov037_020b455c(a, arg1);
}
