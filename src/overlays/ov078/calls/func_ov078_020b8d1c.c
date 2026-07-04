extern int data_ov078_020ba4e0;
extern void func_0202a7dc();
extern void func_ov078_020b933c();

void func_ov078_020b8d1c(int this_) {
    int i;
    char *p = (char *)(data_ov078_020ba4e0 + 0x2cf0);
    for (i = 0; i < 2; i++, p += 0x10c) {
        func_0202a7dc((int)p);
    }
    func_ov078_020b933c(this_);
}
