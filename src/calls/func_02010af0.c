extern void func_01ff86fc();
void *func_02010af0(unsigned int *param_1, int param_2, int param_3)
{
    unsigned int p = ~(param_3 - 1U) & (param_1[1] - param_2);
    unsigned int fill;
    if (p < *param_1)
        return (void *)0;
    fill = param_1[1] - p;
    if (((unsigned char)param_1[-1] & 1) != 0)
        func_01ff86fc(0, p, fill);
    param_1[1] = p;
    return (void *)p;
}
