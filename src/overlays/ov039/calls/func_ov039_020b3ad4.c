extern char *data_ov039_020b5600;
extern void func_ov039_020b3e8c(void *a, void *arg1, int arg2);
extern void func_ov039_020b3ed8(void *a, void *arg1);

void func_ov039_020b3ad4(char *a) {
    char *base = data_ov039_020b5600 + 0xd4;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov039_020b3e8c(a, arg1, arg2);
    func_ov039_020b3ed8(a, arg1);
}
