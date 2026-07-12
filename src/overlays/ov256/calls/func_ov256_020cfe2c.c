/* Unless busy, if the +0x54 counter has caught up to obj+0x45c+1 latch sub-state +0x74+2,
 * else latch 0xc; either way dispatch. */
extern int func_0203c634(int, int, void *);
void func_ov256_020cfe2c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    int obj = *(int *)owner;
    if (*(int *)(owner + 0x54) == *(int *)(obj + 0x45c) + 1) {
        *(unsigned char *)(obj + 0x1c7) = *(int *)(owner + 0x74) + 2;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    } else {
        *(unsigned char *)(obj + 0x1c7) = 0xc;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    }
}
