extern void func_0203c7e8();
extern void func_0203d194();
extern void func_ov107_020c68ec();

struct row8 { int a, b; };

void func_ov284_020cc37c(int this_) {
    int i;
    func_0203c7e8(*(int *)(this_ + 0x384));
    func_0203c7e8(*(int *)(this_ + 0x3ac));
    for (i = 0; i < 4; i++)
        func_0203c7e8(((struct row8 *)*(int *)(this_ + 0x3b0))[i].a);
    func_0203d194(*(int *)(this_ + 0x3b0));
    func_ov107_020c68ec(this_);
}
