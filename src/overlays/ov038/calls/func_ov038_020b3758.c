extern char *data_ov038_020b4ca0;
extern void func_ov038_020b399c(void *a, void *arg1, int arg2);
extern void func_ov038_020b3a6c(void *a, void *arg1);

void func_ov038_020b3758(char *a) {
    char *base = data_ov038_020b4ca0 + 0x2c;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov038_020b399c(a, arg1, arg2);
    func_ov038_020b3a6c(a, arg1);
}
