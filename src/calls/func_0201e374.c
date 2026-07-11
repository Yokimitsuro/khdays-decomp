extern unsigned short *GXx_SetMasterBrightness_(unsigned short *p, int v);
extern unsigned char data_027e0080;
extern unsigned char data_027e0084;

/* Main-engine master brightness: apply now if DISPSTAT says we are in V-blank,
 * else stash it and flag a deferred update (data_027e0080 bit 0). */
void func_0201e374(int brightness) {
    data_027e0084 = (unsigned char)brightness;
    {
        volatile unsigned short *reg_dispstat = (volatile unsigned short *)0x04000004;
        if (*reg_dispstat & 1) {
            GXx_SetMasterBrightness_((unsigned short *)0x0400006C, brightness); /* MASTER_BRIGHT (main) */
            data_027e0080 &= ~1;
        } else {
            data_027e0080 |= 1;
        }
    }
}
