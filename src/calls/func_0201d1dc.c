extern int func_0201a9b8();
int func_0201d1dc(int param_1, int param_2, int param_3)
{
    if (*(int *)(param_1 + 0x120) == 0 && func_0201a9b8(param_1, param_2, param_3) == 0)
        return 0;
    *(int *)(param_1 + 0x120) += 1;
    return 1;
}
