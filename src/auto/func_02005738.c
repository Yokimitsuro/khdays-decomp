void func_02005738(unsigned short *dst, int value)
{
    if (value == 0) {
        *dst = 0;
    } else if (value > 0) {
        *dst = value | 0x4000;
    } else {
        *dst = -value | 0x8000;
    }
}
