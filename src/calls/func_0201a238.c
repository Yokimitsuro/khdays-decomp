extern int func_02008d1c();
int func_0201a238(int *param_1, int param_2, short *param_3)
{
    int obj;
    if (*param_1 == 0)
        return 0;
    obj = *(volatile int *)param_1;
    if (*(unsigned char *)(obj + 0x2d) == 0) {
        *param_3 = -1;
        return 1;
    }
    *param_3 = (short)func_02008d1c(*(unsigned char *)(obj + 0x3c), param_2);
    return 1;
}
