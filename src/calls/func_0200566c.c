/* Update DISPCNT's display-mode/VRAM-block field (bits 16-17) from a pending value:
 * flag the request as consumed (data_020422b4 = 1); if a mode was queued
 * (data_020446d0 != 0) write it into bits 16-17, otherwise just set bit 16. */
extern unsigned short data_020446d0;
extern short data_020422b4;
void func_0200566c(void) {
    volatile unsigned int *reg_dispcnt = (volatile unsigned int *)0x04000000;
    unsigned short v;
    data_020422b4 = 1;
    v = data_020446d0;
    if (v != 0) {
        *reg_dispcnt = *reg_dispcnt & 0xfffcffff | (unsigned int)v << 0x10;
        return;
    }
    *reg_dispcnt = *reg_dispcnt | 0x10000;
}
