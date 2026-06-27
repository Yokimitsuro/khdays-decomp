extern unsigned short *GXx_SetMasterBrightness_(unsigned short *p, int v);

extern unsigned char data_027e0080;
extern unsigned char data_027e0084;

void func_0201e3cc(int brightness) {
    (&data_027e0084)[1] = (unsigned char)brightness;
    if (*(volatile unsigned short *)0x04000004 & 1) {
        GXx_SetMasterBrightness_((unsigned short *)0x0400106C, brightness);
        data_027e0080 &= ~2;
    } else {
        data_027e0080 |= 2;
    }
}
