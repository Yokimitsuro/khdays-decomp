int func_ov024_02085878(int p)
{
    if (*(int *)(p + 0x20) == 0)
        return 0;
    if (*(int *)(p + 0x28) != 0)
        return 0x80;
    return 0x100;
}
