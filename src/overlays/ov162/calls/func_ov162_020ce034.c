extern void func_0203c7e8();
extern void func_ov107_020c9eac();
extern void func_0203d194();
extern void func_ov107_020c68ec();

struct row8 { int a, b; };

void func_ov162_020ce034(int this_) {
    int i;
    func_0203c7e8(*(int *)(this_ + 0x384));
    func_ov107_020c9eac(*(int *)(this_ + 0x3c8));
    for (i = 0; i < 6; i++)
        func_0203c7e8(((struct row8 *)*(int *)(this_ + 0x3c4))[i].a);
    func_0203d194(*(int *)(this_ + 0x3c4));
    func_ov107_020c68ec(this_);
}
