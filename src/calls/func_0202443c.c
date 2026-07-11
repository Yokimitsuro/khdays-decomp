extern void func_020241f8(void *ptr);
extern char data_02041eec;

void func_0202443c(int arg0, int arg1, int arg2, int arg3) {
    volatile unsigned short *reg_bg3cnt = (volatile unsigned short *)0x0400000e;

    func_020241f8(&data_02041eec);
    *reg_bg3cnt = (*reg_bg3cnt & 0x43) | (arg0 << 14) | (arg1 << 7) | (arg2 << 8) | (arg3 << 2);
}
