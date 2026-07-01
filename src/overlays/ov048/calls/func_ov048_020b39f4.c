extern void *data_ov048_020b4b80;
extern void func_0202a7dc(void *p);

void func_ov048_020b39f4(void) {
    char *base = (char *)data_ov048_020b4b80 + 0x2e78;
    func_0202a7dc(base);
    func_0202a7dc(base - 0x240);
    func_0202a7dc(base - 0x12c);
}
