void func_020327e0(int p, int v)
{
    if (v > 0x10)
        v = 0x10;
    else if (v < 0)
        v = 0;
    *(int *)(p + 0x4628) = v;
}
