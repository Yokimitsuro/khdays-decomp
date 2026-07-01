extern char *data_ov074_020b9b80;
extern void func_ov074_020b89f4(void *a, void *arg1, int arg2);
extern void func_ov074_020b8a04(void *a, void *arg1);

void func_ov074_020b86cc(char *a) {
    char *base = data_ov074_020b9b80 + 0xa4;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov074_020b89f4(a, arg1, arg2);
    func_ov074_020b8a04(a, arg1);
}
