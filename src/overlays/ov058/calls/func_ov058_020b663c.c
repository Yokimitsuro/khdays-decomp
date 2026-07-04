extern int data_ov058_020b7e00;
extern void func_0202a7dc();
extern void func_ov058_020b6c5c();

void func_ov058_020b663c(int this_) {
    int i;
    char *p = (char *)(data_ov058_020b7e00 + 0x2cf0);
    for (i = 0; i < 2; i++, p += 0x10c) {
        func_0202a7dc((int)p);
    }
    func_ov058_020b6c5c(this_);
}
