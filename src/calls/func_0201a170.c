extern int func_02008180(unsigned int a0, int a1, int a2);
extern short data_02041488[];

int func_0201a170(unsigned char *volatile *arg0, int arg1, int arg2)
{
    if (*arg0 == 0) return (int)arg0;
    return func_02008180((*arg0)[0x3c], arg1, data_02041488[arg2]);
}
