extern char *data_ov077_020b9b80;
extern void func_ov077_020b887c(void *a, void *arg1, int arg2);
extern void func_ov077_020b894c(void *a, void *arg1);

void func_ov077_020b8638(char *a) {
    char *base = data_ov077_020b9b80 + 0x2c;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov077_020b887c(a, arg1, arg2);
    func_ov077_020b894c(a, arg1);
}
