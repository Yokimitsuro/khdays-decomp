int func_0201a210(unsigned short *volatile *p)
{
    unsigned short *s;
    if (*p == 0)
        return -1;
    s = *p;
    if (s[0x34 / 2] != 1)
        return -1;
    return s[0x38 / 2];
}
