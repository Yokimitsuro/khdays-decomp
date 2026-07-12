/* Raise flag 0 in the high byte at (*child)+0x60, set bit 0 in the low byte of [+8] of the
 * child slot at (*child)+0x388, clear +0x14 and register the handler. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov212_020d1f64(int);
struct lo8_020d1ef4 { unsigned f : 8; };
void func_ov212_020d1ef4(int param_1) {
    int child = *(int *)(param_1 + 4);
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 1;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    {
        int c = *(int *)(*(int *)child + 0x388);
        ((struct lo8_020d1ef4 *)(c + 8))->f |= 1;
    }
    *(signed char *)(child + 0x14) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov212_020d1f64);
}
