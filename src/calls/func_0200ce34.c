extern int func_0200ca7c();
extern void func_0200d138();
extern int data_020463cc[];
int func_0200ce34(unsigned int param_1, unsigned int param_2, int param_3, int param_4)
{
    if (func_0200ca7c() != 0) {
        *(int *)((char *)data_020463cc + 0x20) = param_3;
        *(int *)((char *)data_020463cc + 0x24) = param_4;
        func_0200d138((param_1 & 0xff) | 0x2006400);
        func_0200d138(0x1010000 | (param_2 & 0xffff));
        return 0;
    }
    return 1;
}
