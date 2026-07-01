extern char *data_ov076_020b9d00;
extern void func_ov076_020b9240(void *a, void *arg1, int arg2);
extern void func_ov076_020b943c(void *a, void *arg1);

void func_ov076_020b8610(char *a) {
    char *base = data_ov076_020b9d00 + 0x2c;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov076_020b9240(a, arg1, arg2);
    func_ov076_020b943c(a, arg1);
}
