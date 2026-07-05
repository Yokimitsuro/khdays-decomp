extern void func_ov015_02080c00(int a, int b, int c, int d);
extern void func_0203d194(int p);
extern void func_0203c7e8(int p);
extern void func_ov107_020c68ec(int p);

void func_ov262_020d3aec(int this_) {
    if (*(int *)(this_ + 0x3a4) != 0 &&
        *(int *)(this_ + 0x3a8) != 0 &&
        *(signed char *)(this_ + 0x1c6) != 2 &&
        *(int *)(*(int *)(this_ + 0x3a0)) != 0) {
        int e = *(unsigned char *)(this_ + 0x3ad);
        int flag = 0;
        if ((unsigned short)*(int *)(*(int *)(this_ + 0x3a0) + e * 0x24 + 0x18) == 1)
            flag = 1;
        func_ov015_02080c00(*(int *)(*(int *)(this_ + 0x3a0)), e, flag, 1);
    }
    if (*(int *)(this_ + 0x3a0) != 0) {
        func_0203d194(*(int *)(this_ + 0x3a0));
    }
    func_0203c7e8(*(int *)(this_ + 0x384));
    func_0203c7e8(*(int *)(this_ + 0x388));
    func_0203c7e8(*(int *)(this_ + 0x38c));
    func_ov107_020c68ec(this_);
}
