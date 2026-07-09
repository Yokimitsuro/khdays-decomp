extern int func_0203d15c();
extern void func_ov107_020c6624();
extern void func_ov179_020d41f0();

int func_ov179_020d41bc(int this_) {
    int obj = func_0203d15c(0x390);
    *(int *)(obj + 0x388) = this_;
    *(int *)(obj + 0x18c) = (int)&func_ov179_020d41f0;
    func_ov107_020c6624(obj, 0, (int)&func_ov179_020d41f0);
    return obj;
}
