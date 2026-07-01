void func_ov008_02081544(void) {
    volatile int *a = (volatile int *)0x4000000;
    volatile int *b = (volatile int *)0x4001000;
    *a = (*a & ~0x1f00) | 0x800;
    *b = (*b & ~0x1f00) | 0x800;
}
