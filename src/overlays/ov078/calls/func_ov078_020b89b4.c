extern char *data_ov078_020ba4e0;
extern void func_ov078_020b8d6c(void *a, void *arg1, int arg2);
extern void func_ov078_020b8db8(void *a, void *arg1);

void func_ov078_020b89b4(char *a) {
    char *base = data_ov078_020ba4e0 + 0xd4;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov078_020b8d6c(a, arg1, arg2);
    func_ov078_020b8db8(a, arg1);
}
