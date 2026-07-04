void func_020240f0(int a, int b, int c, int d)
{
    unsigned short h = *(volatile unsigned short *)0x400000e;
    *(volatile unsigned short *)0x400000e = (h & 0x43) | (a << 14) | (b << 7) | (c << 8) | (d << 2);
}
