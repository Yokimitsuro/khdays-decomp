struct row8 { int a, b; };
extern void func_0203d194(int p);
extern void func_0203c7e8(int p);
extern void func_ov107_020c68ec(int p);

void func_ov157_020ce154(int this_) {
    int i;
    func_0203d194(*(int *)(this_ + 0x3a4));
    func_0203c7e8(*(int *)(this_ + 0x384));
    for (i = 0; i < 4; i++) {
        func_0203c7e8(((struct row8 *)(*(int *)(this_ + 0x3a0)))[i].a);
    }
    func_0203d194(*(int *)(this_ + 0x3a0));
    func_ov107_020c68ec(this_);
}
