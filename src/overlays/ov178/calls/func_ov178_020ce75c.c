extern int func_0203d15c();
extern void func_ov107_020c6624();
extern void func_ov178_020ce790();

int func_ov178_020ce75c(int this_) {
    int obj = func_0203d15c(0x390);
    *(int *)(obj + 0x388) = this_;
    *(int *)(obj + 0x18c) = (int)&func_ov178_020ce790;
    func_ov107_020c6624(obj, 0, (int)&func_ov178_020ce790);
    return obj;
}
