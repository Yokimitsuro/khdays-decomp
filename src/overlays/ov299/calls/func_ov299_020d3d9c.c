extern int func_0203d15c();
extern void func_ov107_020c6624();
extern void func_ov299_020d3dd8();

int func_ov299_020d3d9c(int this_) {
    int obj = func_0203d15c(0x3ac);
    *(int *)(obj + 0x390) = this_;
    *(unsigned char *)(obj + 0x19c) = 0x73;
    *(int *)(obj + 0x18c) = (int)&func_ov299_020d3dd8;
    func_ov107_020c6624(obj, 0);
    return obj;
}
