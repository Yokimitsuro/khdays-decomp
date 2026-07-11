extern void func_020241f8(void *ptr);
extern char data_02041f0c;
extern int data_02047390;

void func_02024524(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg_bg2cnt = (volatile unsigned short *)0x0400000c;
    int arg3;

    func_020241f8(&data_02041f0c);
    arg3 = data_02047390;
    *reg_bg2cnt = (*reg_bg2cnt & 0x43) | (arg0 << 14) | (arg2 << 2) | (arg1 << 8) | (arg3 << 13);
}
