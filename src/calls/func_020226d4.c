extern int func_0201eea8();
extern void func_0202b984();
int func_020226d4(int param_1, unsigned int param_2)
{
    if (func_0201eea8(*(int *)(*(int *)(*(int *)(param_1 + 0x128) + 0x28) + 0xc)) != 0) {
        func_0202b984(param_2 & 0xffff, *(int *)(*(int *)(param_1 + 0x128) + 0x28), 1, 0);
        return 1;
    }
    return 0;
}
