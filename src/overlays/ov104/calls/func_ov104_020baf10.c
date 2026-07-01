extern char *data_ov104_020bc2a0;
extern void func_ov104_020bb14c(void *a, void *arg1, int arg2);
extern void func_ov104_020bb3a0(void *a, void *arg1);

void func_ov104_020baf10(char *a) {
    char *base = data_ov104_020bc2a0 + 0xfc;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov104_020bb14c(a, arg1, arg2);
    func_ov104_020bb3a0(a, arg1);
}
