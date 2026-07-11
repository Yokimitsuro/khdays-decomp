/* Set display mode (DISPCNT bits 8-12) to mode 0x800 on both 2D engines. */
void func_ov006_020557d4(void) {
    volatile int *reg_dispcnt_a = (volatile int *)0x04000000;
    volatile int *reg_dispcnt_b = (volatile int *)0x04001000;
    *reg_dispcnt_a = (*reg_dispcnt_a & ~0x1f00) | 0x800;
    *reg_dispcnt_b = (*reg_dispcnt_b & ~0x1f00) | 0x800;
}
