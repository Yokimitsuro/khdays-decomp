void G2x_SetBlendBrightness_(unsigned short *dst, unsigned int attr, int value)
{
    if (value < 0) {
        dst[0] = attr | 0xc0;
        dst[2] = -value;
    } else {
        dst[0] = attr | 0x80;
        dst[2] = value;
    }
}
