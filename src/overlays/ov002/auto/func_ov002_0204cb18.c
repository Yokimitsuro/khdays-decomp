int func_ov002_0204cb18(int p)
{
    if (p == -1)
        return 0;
    if (*(int *)(p + 0x20) != 0)
        return *(int *)(*(int *)(p + 0x20) + 0x38) & 1;
    return 0;
}
