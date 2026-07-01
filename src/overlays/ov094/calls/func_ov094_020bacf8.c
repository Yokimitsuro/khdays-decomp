extern char *data_ov094_020bc240;
extern void func_ov094_020baf3c(void *a, void *arg1, int arg2);
extern void func_ov094_020bb00c(void *a, void *arg1);

void func_ov094_020bacf8(char *a) {
    char *base = data_ov094_020bc240 + 0x2c;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov094_020baf3c(a, arg1, arg2);
    func_ov094_020bb00c(a, arg1);
}
