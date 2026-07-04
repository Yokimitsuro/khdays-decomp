int func_02017150(int p, unsigned int i)
{
    if (p == 0)
        goto zero;
    if (i >= *(unsigned char *)(p + 7))
        goto zero;
    return p + *(unsigned short *)(p + 10) + i * 0x10;
zero:
    return 0;
}
