extern int func_0203d15c();
extern void func_ov107_020c6624();
extern void func_ov198_020d1968();

int func_ov198_020d1934(int this_) {
    int obj = func_0203d15c(0x3a4);
    *(int *)(obj + 0x390) = this_;
    *(int *)(obj + 0x18c) = (int)&func_ov198_020d1968;
    func_ov107_020c6624(obj, 0, (int)&func_ov198_020d1968);
    return obj;
}
