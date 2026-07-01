extern char *data_ov090_020bcc00;
extern void func_ov090_020bc8bc(void *a, void *arg1, int arg2);
extern void func_ov090_020bca30(void *a, void *arg1);

void func_ov090_020bb210(char *a) {
    char *base = data_ov090_020bcc00 + 0xe4;
    char *arg1 = base + 0x2c00;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov090_020bc8bc(a, arg1, arg2);
    func_ov090_020bca30(a, arg1);
}
