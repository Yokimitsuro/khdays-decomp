void func_0202405c(int a, int b, int c, int d)
{
    unsigned short h = *(volatile unsigned short *)0x400100c;
    *(volatile unsigned short *)0x400100c = (h & 0x43) | (a << 14) | (b << 7) | (c << 8) | (d << 2);
}
