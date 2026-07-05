extern void func_0203c7e8(int p);
extern void func_ov107_020c9eac(int p);
extern void func_0203d194(int p);
extern void func_ov107_020c68ec(int p);

void func_ov241_020d0024(int this_) {
    int i;
    func_0203c7e8(*(int *)(this_ + 0x384));
    func_ov107_020c9eac(*(int *)(this_ + 0x39c));
    func_0203c7e8(*(int *)(this_ + 0x388));
    func_0203c7e8(*(int *)(this_ + 0x3a0));
    for (i = 0; i < 3; i++) {
        func_0203c7e8(((int *)this_)[0xe3 + i]);
    }
    if (*(int *)(this_ + 0x3a4) != 0) {
        func_0203d194(*(int *)(this_ + 0x3a4));
        *(int *)(this_ + 0x3a4) = 0;
    }
    func_ov107_020c68ec(this_);
}
