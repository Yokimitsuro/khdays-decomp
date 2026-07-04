void func_02024030(int a, int b, int c, int d)
{
    unsigned short h = *(volatile unsigned short *)0x400100e;
    *(volatile unsigned short *)0x400100e = (h & 0x43) | (a << 14) | (b << 7) | (c << 8) | (d << 2);
}
