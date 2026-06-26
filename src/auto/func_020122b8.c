void func_020122b8(int *r0, int r1, int r2)
{
    if (*r0 != 1)
        return;
    *(unsigned short *)((char *)r0 + 0x12) |= 8;
    *(unsigned short *)((char *)r0 + 0xc) = (unsigned short)r1;
    *(unsigned short *)((char *)r0 + 0xe) = (unsigned short)r2;
}
