extern char *data_ov087_020b9be0;
extern void func_ov087_020b8a8c(void *a, void *arg1, int arg2);
extern void func_ov087_020b8ce0(void *a, void *arg1);

void func_ov087_020b8850(char *a) {
    char *base = data_ov087_020b9be0 + 0xfc;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov087_020b8a8c(a, arg1, arg2);
    func_ov087_020b8ce0(a, arg1);
}
