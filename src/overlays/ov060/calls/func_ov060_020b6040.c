extern void func_0202a7dc(int p);

void func_ov060_020b6040(int this_) {
    char *base = (char *)(this_ + 0x2c84);
    int i;
    char *p = base + 0x334;
    for (i = 0; i < 3; i++) {
        func_0202a7dc((int)p);
        p += 0x110;
    }
    func_0202a7dc((int)(base + 4));
    func_0202a7dc((int)(base + 0x114));
    func_0202a7dc((int)(base + 0x224));
}
