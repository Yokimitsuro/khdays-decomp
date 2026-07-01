extern char *data_ov103_020bc120;
extern void func_ov103_020baffc(void *a, void *arg1, int arg2);
extern void func_ov103_020bb034(void *a, void *arg1);

void func_ov103_020badf0(char *a) {
    char *base = data_ov103_020bc120 + 0x2c;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov103_020baffc(a, arg1, arg2);
    func_ov103_020bb034(a, arg1);
}
