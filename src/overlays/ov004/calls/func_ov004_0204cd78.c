extern int func_020235d0();

struct S {
    unsigned char b0;
    unsigned char b1;
    unsigned short h2;
    unsigned short h4;
    unsigned short h6;
    unsigned short h8;
    unsigned short ha;
    unsigned char pad[0x23 - 0xc];
    unsigned char b23;
};

int func_ov004_0204cd78(struct S *p, unsigned int flags)
{
    int r0;
    int r4;

    if (p->b23 == 0)
        return 0;
    if (p->h4 >= 0x384)
        return 0;
    if (p->ha != ((flags >> 8) & 0xff))
        return 0;
    if (flags & 8) {
        if (p->h2 == 0xa)
            return 1;
    }
    if (flags & 3) {
        r0 = func_020235d0(0x44e, 3);
        if (r0 >= 6) {
            r0 = 0x191;
        } else {
            r0 = func_020235d0(0, 9);
        }
        if ((int)p->h8 >= r0)
            return 0;
    }
    r4 = (flags & 0xf) & (1 << (p->b23 - 1));
    r0 = func_020235d0((p->h4 << 2) + 0x2b + 0x900, 4);
    if (r4 & r0)
        return 1;

    if (flags & 2) {
        if (p->b23 == 2) {
            int v = p->h4;
            if (v > 0x64) {
                int rem = v - (v / 100) * 100;
                if (rem < 0)
                    return 0;
                if (rem >= 0xc8)
                    return 0;
                r0 = func_020235d0((rem << 2) + 0x2b + 0x900, 4);
                if (r4 & r0)
                    return 1;
            }
        }
    }
    return 0;
}
