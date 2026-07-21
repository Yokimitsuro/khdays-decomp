extern void G2x_SetBlendBrightness_(void *reg, int planeMask, int brightness);
void func_ov008_0206fe08(int bEnable) {
    volatile unsigned int *pDispcntB = (volatile unsigned int *)0x04001000;
    int brightness = bEnable != 0 ? -8 : 0;
    G2x_SetBlendBrightness_((void *)0x04000050, 1, brightness);
    G2x_SetBlendBrightness_((char *)pDispcntB + 0x50, (*pDispcntB & 0x1f00) >> 8, brightness);
}
