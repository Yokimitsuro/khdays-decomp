extern void func_0203c7e8();
extern void func_ov107_020c9eac();
extern void func_ov107_020c68ec();

struct row8 { int a, b; };

void func_ov188_020ce1f0(int this_) {
    int i;
    func_0203c7e8(*(int *)(this_ + 0x384));
    func_ov107_020c9eac(*(int *)(this_ + 0x3c0));
    for (i = 0; i < 4; i++)
        func_0203c7e8(((struct row8 *)this_)[i + 121].a);
    func_ov107_020c68ec(this_);
}
