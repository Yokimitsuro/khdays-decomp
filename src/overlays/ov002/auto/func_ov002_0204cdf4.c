void func_ov002_0204cdf4(int p, int cond, int v)
{
    int base = *(int *)(p + 0x20);
    *(int *)(base + 0xb0) = v;
    if (cond)
        *(int *)(base + 0x38) |= 0x2000000;
    else
        *(int *)(base + 0x38) &= ~0x2000000;
}
