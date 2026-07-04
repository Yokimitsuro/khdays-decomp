void func_ov022_020848bc(int p, int mask)
{
    int v = *(int *)p;
    if (v & mask)
        *(int *)p = v & ~mask;
    *(int *)(p + 4) = 0;
    *(int *)(p + 8) = 0;
    *(int *)(p + 0x10) = 0;
    *(int *)(p + 0x14) = 0;
    *(int *)(p + 0x18) = 0;
}
