extern void func_0203c7e8();
extern void func_ov107_020c68ec();

struct row8 { int a, b; };

void func_ov245_020d2a40(int this_) {
    int i;
    func_0203c7e8(*(int *)(this_ + 0x384));
    for (i = 0; i < 3; i++) {
        func_0203c7e8(((struct row8 *)this_)[i + 114].b);
    }
    func_ov107_020c68ec(this_);
}
