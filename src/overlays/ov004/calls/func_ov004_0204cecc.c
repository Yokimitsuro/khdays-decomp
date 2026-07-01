extern int func_020235d0();

int func_ov004_0204cecc(unsigned char *p, unsigned short n)
{
    unsigned char v;
    int b;

    if (p[0x23] != 0) {
        return 0;
    }
    if (*(unsigned short *)(p + 6) > n) {
        return 0;
    }
    if (*(unsigned short *)(p + 8) < n) {
        return 0;
    }
    v = p[0x15];
    if (v != 0) {
        b = func_020235d0((unsigned short)(v - 1) * 2 + 0x379f, 2) >= 1;
        if (b == 0) {
            return 0;
        }
    }
    return 1;
}
