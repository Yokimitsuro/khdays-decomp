extern char *data_ov056_020b7620;
extern void func_ov056_020b6b60(void *a, void *arg1, int arg2);
extern void func_ov056_020b6d5c(void *a, void *arg1);

void func_ov056_020b5f30(char *a) {
    char *base = data_ov056_020b7620 + 0x2c;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov056_020b6b60(a, arg1, arg2);
    func_ov056_020b6d5c(a, arg1);
}
