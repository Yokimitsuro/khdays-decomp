/* Raise flag 0x86 in the high byte at (*child)+0x60, clear bit 0 in the low byte of [+8] of
 * the two child slots at (*child)+0x3b8/+0x3b4, then register the handler. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov209_020d3460(int);
struct lo8_020d15b0 { unsigned f : 8; };
void func_ov209_020d33d0(int param_1) {
    int child = *(int *)(param_1 + 4);
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x86;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    {
        int c = *(int *)(*(int *)child + 0x3b8);
        ((struct lo8_020d15b0 *)(c + 8))->f &= ~1;
    }
    {
        int c = *(int *)(*(int *)child + 0x3b4);
        ((struct lo8_020d15b0 *)(c + 8))->f &= ~1;
    }
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov209_020d3460);
}
