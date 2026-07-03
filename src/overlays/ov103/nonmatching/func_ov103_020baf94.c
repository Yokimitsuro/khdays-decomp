extern void *data_ov103_020bc120;
extern void func_0202a7dc(void *p);

void func_ov103_020baf94(void) {
    char *base = (char *)data_ov103_020bc120 + 0x2e78;
    func_0202a7dc(base);
    func_0202a7dc(base - 0x240);
    func_0202a7dc(base - 0x12c);
}
