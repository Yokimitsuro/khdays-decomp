extern void func_020350b0();
extern void func_020236ac();
int func_02035028(int *param_1)
{
    short *p = (short *)*param_1;
    if (p == 0)
        return 0;
    if (*(int *)(p + 2) != 0)
        func_020350b0((int *)(p + 2), (int)*p);
    p = (short *)*param_1;
    if (*(int *)(p + 4) != 0)
        func_020350b0((int *)(p + 4), (int)*p);
    if (*(short *)*param_1 >= 0) {
        func_020236ac((short *)*param_1);
        *param_1 = 0;
    }
    return 1;
}
