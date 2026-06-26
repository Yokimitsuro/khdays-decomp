unsigned short func_020149b0(unsigned short **p)
{
    unsigned short *q = *p;
    unsigned short v = *q++;
    *p = q;
    return v;
}
