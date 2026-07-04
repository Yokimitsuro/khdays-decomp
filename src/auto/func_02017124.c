int func_02017124(int p, unsigned int i)
{
    if (p == 0)
        goto zero;
    if (i >= *(unsigned char *)(p + 6))
        goto zero;
    return p + *(unsigned short *)(p + 8) + i * 0x10;
zero:
    return 0;
}
