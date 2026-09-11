/* Save DISPCNT's display-mode/VRAM-block field (bits 16-17) into data_020446d0,
 * clear the pending-request flag data_020422b4, and clear that field in DISPCNT. */
extern unsigned short data_020422b4;
extern unsigned short data_020446d0;

void func_02005630(void) {
    volatile unsigned int *reg_dispcnt = (volatile unsigned int *)0x04000000;
    unsigned int disp = *reg_dispcnt;
    data_020422b4 = 0;
    data_020446d0 = (unsigned short)((disp & 0x30000) >> 0x10);
    *reg_dispcnt = disp & ~0x30000u;
}
