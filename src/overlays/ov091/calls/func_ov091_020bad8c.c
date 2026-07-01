extern char *data_ov091_020bc240;
extern void func_ov091_020bb0b4(void *a, void *arg1, int arg2);
extern void func_ov091_020bb0c4(void *a, void *arg1);

void func_ov091_020bad8c(char *a) {
    char *base = data_ov091_020bc240 + 0xa4;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov091_020bb0b4(a, arg1, arg2);
    func_ov091_020bb0c4(a, arg1);
}
