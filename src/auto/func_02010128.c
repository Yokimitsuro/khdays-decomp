int func_02010128(int *r0, int r1)
{
    if (r1 == 0)
        return *r0;
    return *(int *)(r1 + *(unsigned short *)((char *)r0 + 0xa) + 4);
}
