extern void func_020293c4();
extern unsigned int func_0202a818();
unsigned int func_0202b3f0(int param_1, unsigned int *param_2, int param_3)
{
    unsigned int r = 0;
    if (param_1 != 0 && (*param_2 & 0x10) == 0)
        func_020293c4(**(int **)(param_1 + 4), param_2 + 0x44);
    if ((*param_2 & 0x20) == 0 && (*param_2 & 0x40) == 0)
        r = func_0202a818((unsigned short *)(param_2 + 1), param_3);
    return r;
}
