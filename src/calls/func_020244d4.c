extern void func_020241f8(void *ptr);
extern char data_02041ecc;
extern int data_02047390;

void func_020244d4(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg = (volatile unsigned short *)0x0400000e;
    int arg3;

    func_020241f8(&data_02041ecc);
    arg3 = data_02047390;
    *reg = (*reg & 0x43) | (arg0 << 14) | (arg1 << 8) | (arg2 << 2) | (arg3 << 13);
}
