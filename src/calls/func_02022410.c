extern int func_02033cc8(void);
extern void func_020335ec(unsigned a);
extern unsigned char data_020425e8;

int func_02022410(int param_1, int param_2) {
    if (func_02033cc8() == 0) {
        data_020425e8 = param_2;
        func_020335ec(param_2 & 0xff);
        return 1;
    }
    return 0;
}
