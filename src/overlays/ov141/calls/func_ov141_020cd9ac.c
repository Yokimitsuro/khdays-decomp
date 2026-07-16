extern int func_0203d15c();
extern void func_ov107_020c6624();
extern void func_ov141_020cd9e0();

int func_ov141_020cd9ac(int this_) {
    int obj = func_0203d15c(0x3a0);
    *(int *)(obj + 0x398) = this_;
    *(int *)(obj + 0x18c) = (int)&func_ov141_020cd9e0;
    func_ov107_020c6624(obj, 0, (int)&func_ov141_020cd9e0);
    return obj;
}
