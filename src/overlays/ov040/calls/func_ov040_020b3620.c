extern char *data_ov040_020b4b20;
extern void func_ov040_020b39c0(void *a, void *arg1, int arg2);
extern void func_ov040_020b39fc(void *a, void *arg1);

void func_ov040_020b3620(char *a) {
    char *base = data_ov040_020b4b20 + 0xc50;
    char *arg1 = base + 0x2000;
    int arg2 = *(short *)(a + 0x2aba);
    func_ov040_020b39c0(a, arg1, arg2);
    func_ov040_020b39fc(a, arg1);
}
