extern char *data_ov079_020b9a00;
extern void func_ov079_020b88a0(void *a, void *arg1, int arg2);
extern void func_ov079_020b88dc(void *a, void *arg1);

void func_ov079_020b8500(char *a) {
    char *base = data_ov079_020b9a00 + 0xc50;
    char *arg1 = base + 0x2000;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov079_020b88a0(a, arg1, arg2);
    func_ov079_020b88dc(a, arg1);
}
