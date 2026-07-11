extern void func_0202423c(void *ptr);
extern char data_02041f4c;

void func_02024674(int arg0, int arg1, int arg2, int arg3) {
    volatile unsigned short *reg_bg2cnt_b = (volatile unsigned short *)0x0400100c;

    func_0202423c(&data_02041f4c);
    *reg_bg2cnt_b = (*reg_bg2cnt_b & 0x43) | (arg0 << 14) | (arg1 << 7) | (arg2 << 8) | (arg3 << 2);
}
