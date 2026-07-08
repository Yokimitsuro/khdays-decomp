extern void func_01ff86fc();
unsigned int func_02010a94(unsigned int *param_1, int param_2, int param_3)
{
    unsigned int base = *param_1;
    unsigned int aligned = ~(param_3 - 1U) & ((param_3 - 1U) + base);
    unsigned int newtop = param_2 + aligned;
    unsigned int fill;
    if (newtop > param_1[1])
        return 0;
    fill = newtop - base;
    if (((unsigned char)param_1[-1] & 1) != 0)
        func_01ff86fc(0, base, fill);
    *param_1 = newtop;
    return aligned;
}
