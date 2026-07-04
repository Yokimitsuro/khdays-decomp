extern void func_0202ba18();

void func_ov021_0207fb80(int this_) {
    int sub = *(int *)(this_ + 8);
    func_0202ba18(this_ + 0x2c);
    if (*(signed char *)(sub + 0x58) != 0) {
        func_0202ba18(this_ + 0x2c);
    }
    *(unsigned short *)(this_ + 0x12) &= ~4;
}
