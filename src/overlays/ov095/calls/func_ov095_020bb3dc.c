extern int data_ov095_020bcba0;
extern void func_0202a7dc();
extern void func_ov095_020bb9fc();

void func_ov095_020bb3dc(int this_) {
    int i;
    char *p = (char *)(data_ov095_020bcba0 + 0x2cf0);
    for (i = 0; i < 2; i++, p += 0x10c) {
        func_0202a7dc((int)p);
    }
    func_ov095_020bb9fc(this_);
}
