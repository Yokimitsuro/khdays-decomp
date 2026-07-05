struct row8 { int a, b; };
extern void func_0203c7e8(int p);
extern void func_ov107_020c9eac(int p);
extern void func_0203d194(int p);
extern void func_ov107_020c68ec(int p);

void func_ov152_020d3acc(int this_) {
    int i;
    func_0203c7e8(*(int *)(this_ + 0x384));
    func_ov107_020c9eac(*(int *)(this_ + 0x3cc));
    for (i = 0; i < 5; i++) {
        func_0203c7e8(((struct row8 *)(*(int *)(this_ + 0x390)))[i].a);
    }
    func_0203d194(*(int *)(this_ + 0x390));
    func_0203d194(*(int *)(this_ + 0x3c8));
    func_ov107_020c68ec(this_);
}
