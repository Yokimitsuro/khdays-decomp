extern void func_0202423c(void *ptr);
extern char data_02041ecc;
extern int data_02047390;

void func_02024754(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg = (volatile unsigned short *)0x0400100e;
    int arg3;

    func_0202423c(&data_02041ecc);
    arg3 = data_02047390;
    *reg = (*reg & 0x43) | (arg0 << 14) | (arg1 << 8) | (arg2 << 2) | (arg3 << 13);
}
