extern int func_0201b44c();
extern int func_0201c008();
extern int func_0201b7e0();
int func_0201bcd0(unsigned int param_1, unsigned int param_2, int *param_3, int param_4, unsigned int *param_5)
{
    unsigned int *p = (unsigned int *)func_0201b44c(param_1);
    unsigned int v;
    if (p == 0)
        return 3;
    if ((param_2 & 8) != 0) {
        v = func_0201c008(*p, param_3, param_4);
        if (v == 0)
            return 7;
    } else {
        v = func_0201b7e0(*p);
    }
    if (param_5 != 0)
        *param_5 = v;
    return 0;
}
