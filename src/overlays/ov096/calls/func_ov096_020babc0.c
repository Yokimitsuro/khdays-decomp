extern char *data_ov096_020bc0c0;
extern void func_ov096_020baf60(void *a, void *arg1, int arg2);
extern void func_ov096_020baf9c(void *a, void *arg1);

void func_ov096_020babc0(char *a) {
    char *base = data_ov096_020bc0c0 + 0xc50;
    char *arg1 = base + 0x2000;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov096_020baf60(a, arg1, arg2);
    func_ov096_020baf9c(a, arg1);
}
