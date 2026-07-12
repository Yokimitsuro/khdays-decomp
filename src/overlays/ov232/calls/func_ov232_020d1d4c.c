/* Compute the offset vector (020cca74) into (child)+0x30 and scale it by 0x2000 or 0x4000
 * per the mode byte at (child)+0x49; unless the gate byte at *(child+0x10) is set, clear
 * bit 1 in the low byte of [+8] of the child slot at (*child)+0x3bc and, if 020ccfb8 approves,
 * dispatch. */
extern void func_ov232_020d06b4(void *out, int a, int b);
extern void func_01ffa724(int a, int b, int c);
extern int func_ov232_020d0bf8(int);
extern int func_0203c634(int a, int b, void *handler);
struct Vec3_020ce10c { int x, y, z; };
struct lo8_020ce10c { unsigned f : 8; };
void func_ov232_020d1d4c(int param_1) {
    int child = *(int *)(param_1 + 4);
    struct Vec3_020ce10c out;
    func_ov232_020d06b4(&out, param_1, *(int *)(*(int *)child + 0x388) + 0x2c);
    *(struct Vec3_020ce10c *)(child + 0x30) = out;
    if (*(unsigned char *)(child + 0x49) < 2) {
        func_01ffa724(0x2000, child + 0x30, child + 0x30);
    } else {
        func_01ffa724(0x4000, child + 0x30, child + 0x30);
    }
    if (*(unsigned char *)*(int *)(child + 0x10) != 0) return;
    {
        int c = *(int *)(*(int *)child + 0x3bc);
        ((struct lo8_020ce10c *)(c + 8))->f &= ~2;
    }
    if (func_ov232_020d0bf8(param_1) == 0) return;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
