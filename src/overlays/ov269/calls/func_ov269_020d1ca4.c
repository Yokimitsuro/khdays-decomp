extern void func_0203c7e8();
extern void func_ov107_020c9eac();
extern void func_0203d194();
extern void func_ov107_020c68ec();

struct row8 { int a, b; };

void func_ov269_020d1ca4(int this_) {
    int i;
    func_0203c7e8(*(int *)(this_ + 0x384));
    func_ov107_020c9eac(*(int *)(this_ + 0x3d0));
    for (i = 0; i < 3; i++)
        func_0203c7e8(((struct row8 *)*(int *)(this_ + 0x3d4))[i].a);
    func_0203d194(*(int *)(this_ + 0x3d4));
    func_ov107_020c68ec(this_);
}
