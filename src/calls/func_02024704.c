extern void func_0202423c(void *ptr);
extern char data_02041f2c;
extern int data_02047390;

void func_02024704(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg_bg2cnt_b = (volatile unsigned short *)0x0400100c;
    int arg3;

    func_0202423c(&data_02041f2c);
    arg3 = data_02047390;
    *reg_bg2cnt_b = (*reg_bg2cnt_b & 0x43) | (arg0 << 14) | (arg1 << 8) | (arg2 << 2) | (arg3 << 13);
}
