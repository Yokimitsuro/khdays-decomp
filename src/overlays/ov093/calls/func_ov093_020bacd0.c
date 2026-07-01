extern char *data_ov093_020bc3c0;
extern void func_ov093_020bb900(void *a, void *arg1, int arg2);
extern void func_ov093_020bbafc(void *a, void *arg1);

void func_ov093_020bacd0(char *a) {
    char *base = data_ov093_020bc3c0 + 0x2c;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov093_020bb900(a, arg1, arg2);
    func_ov093_020bbafc(a, arg1);
}
