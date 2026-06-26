void func_0201cdec(int *r0)
{
    int *p = (int *)r0[0x53];
    if (p != 0) {
        *p = 0;
        r0[0x53] = 0;
    }
    r0[0x110 / 4] &= ~1;
    r0[0x110 / 4] &= ~4;
    r0[0x110 / 4] &= ~2;
}
