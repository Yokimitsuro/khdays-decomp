extern void func_02024a6c();
extern void func_02024ae0();
extern void func_02024b04();
void func_02024b28(int param_1, int param_2, int param_3, int *param_4)
{
    if (param_4 != 0 && param_2 != 0)
        func_02024a6c(param_1, param_4, param_2, 0, *(int *)((char *)param_4 + 8));
    if (param_3 != 0)
        func_02024ae0(param_1, param_3, 0, *(int *)(param_3 + 0x10));
    if (param_2 != 0)
        func_02024b04(param_1, param_2, 0, *(int *)(param_2 + 8));
}
