extern char *data_ov058_020b7e00;
extern void func_ov058_020b668c(void *a, void *arg1, int arg2);
extern void func_ov058_020b66d8(void *a, void *arg1);

void func_ov058_020b62d4(char *a) {
    char *base = data_ov058_020b7e00 + 0xd4;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov058_020b668c(a, arg1, arg2);
    func_ov058_020b66d8(a, arg1);
}
