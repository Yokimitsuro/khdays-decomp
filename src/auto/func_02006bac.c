void func_02006bac(unsigned short *r0, int r1, int r2)
{
    if (r2 < 0) {
        r0[0] = (unsigned short)(r1 | 0xc0);
        r0[2] = (unsigned short)(-r2);
        return;
    }
    r0[0] = (unsigned short)(r1 | 0x80);
    r0[2] = (unsigned short)r2;
}
