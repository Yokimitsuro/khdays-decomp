extern void func_0202a7dc();
extern void func_0202ba18();

void func_ov021_02080600(int this_) {
    int sub = *(int *)(this_ + 8);
    if ((*(unsigned short *)(this_ + 0x12) & 4) == 0) return;
    if (*(signed char *)(sub + 0x58) != 0) {
        func_0202a7dc(this_ + 0x1c);
    }
    if (*(signed char *)(sub + 0x68) != 0) {
        func_0202ba18(this_ + 0x124);
    }
    *(unsigned short *)(this_ + 0x12) &= ~4;
}
