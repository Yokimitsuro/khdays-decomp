void GXx_SetMasterBrightness_(unsigned short *dst, int value)
{
    if (value == 0) {
        *dst = 0;
    } else if (value > 0) {
        *dst = value | 0x4000;
    } else {
        *dst = -value | 0x8000;
    }
}
