char *func_02017078(char *p)
{
    unsigned short off = *(unsigned short *)(p + 0xc);
    return p + *(int *)(p + off);
}
