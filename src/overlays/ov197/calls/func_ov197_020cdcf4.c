extern int func_0203d15c();
extern void func_ov107_020c6624();
extern void func_ov197_020cdd28();

int func_ov197_020cdcf4(int this_) {
    int obj = func_0203d15c(0x3a4);
    *(int *)(obj + 0x390) = this_;
    *(int *)(obj + 0x18c) = (int)&func_ov197_020cdd28;
    func_ov107_020c6624(obj, 0, (int)&func_ov197_020cdd28);
    return obj;
}
