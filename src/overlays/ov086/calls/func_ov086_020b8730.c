extern char *data_ov086_020b9a60;
extern void func_ov086_020b893c(void *a, void *arg1, int arg2);
extern void func_ov086_020b8974(void *a, void *arg1);

void func_ov086_020b8730(char *a) {
    char *base = data_ov086_020b9a60 + 0x2c;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov086_020b893c(a, arg1, arg2);
    func_ov086_020b8974(a, arg1);
}
