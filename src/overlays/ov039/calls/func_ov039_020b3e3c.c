extern int data_ov039_020b5600;
extern void func_0202a7dc();
extern void func_ov039_020b445c();

void func_ov039_020b3e3c(int this_) {
    int i;
    char *p = (char *)(data_ov039_020b5600 + 0x2cf0);
    for (i = 0; i < 2; i++, p += 0x10c) {
        func_0202a7dc((int)p);
    }
    func_ov039_020b445c(this_);
}
