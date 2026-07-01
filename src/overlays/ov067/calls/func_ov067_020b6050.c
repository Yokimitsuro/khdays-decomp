extern char *data_ov067_020b7380;
extern void func_ov067_020b625c(void *a, void *arg1, int arg2);
extern void func_ov067_020b6294(void *a, void *arg1);

void func_ov067_020b6050(char *a) {
    char *base = data_ov067_020b7380 + 0x2c;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov067_020b625c(a, arg1, arg2);
    func_ov067_020b6294(a, arg1);
}
