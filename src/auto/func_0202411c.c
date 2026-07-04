void func_0202411c(int a, int b, int c, int d)
{
    unsigned short h = *(volatile unsigned short *)0x400000c;
    *(volatile unsigned short *)0x400000c = (h & 0x43) | (a << 14) | (b << 7) | (c << 8) | (d << 2);
}
