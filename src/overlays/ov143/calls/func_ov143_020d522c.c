extern int func_0203d15c();
extern void func_ov107_020c6624();
extern void func_ov143_020d5260();

int func_ov143_020d522c(int this_) {
    int obj = func_0203d15c(0x3a0);
    *(int *)(obj + 0x398) = this_;
    *(int *)(obj + 0x18c) = (int)&func_ov143_020d5260;
    func_ov107_020c6624(obj, 0, (int)&func_ov143_020d5260);
    return obj;
}
