extern void func_020301c8(int base, int x, int y, int z, unsigned int flags, int arg);

void func_ov008_020782dc(int param_1, int param_2, int param_3, int param_4, unsigned char param_5, int param_6) {
    unsigned int flags;
    switch (param_6) {
    case 2: flags = 0x821; break;
    case 1: flags = 0x411; break;
    default: flags = 0x209; break;
    }
    func_020301c8(param_1, param_3 + 1, param_4 + 1, param_5 - 1, flags, param_2);
    func_020301c8(param_1, param_3, param_4, param_5, flags, param_2);
}
