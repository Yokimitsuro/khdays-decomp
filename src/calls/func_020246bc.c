extern void func_0202423c(void *ptr);
extern char data_02041eec;

void func_020246bc(int arg0, int arg1, int arg2, int arg3) {
    volatile unsigned short *reg = (volatile unsigned short *)0x0400100e;

    func_0202423c(&data_02041eec);
    *reg = (*reg & 0x43) | (arg0 << 14) | (arg1 << 7) | (arg2 << 8) | (arg3 << 2);
}
