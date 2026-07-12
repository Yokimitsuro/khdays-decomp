/* Enter reaction (single-slot variant): raise flag 6 then flag 0x40 in the high byte
 * at (*child)+0x60, set bit 0 of the halfword at (*child)+0x1ae, clear bit 0 in the low
 * byte of [+8] of the child slot at (*child)+0x3ac, run the ov107 effect (mode 0x49,
 * data at (*child)+0x494), reset the timer (+0x4c) and register the handler. */
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov249_020d3b38(int);
struct lo8_020d1d30 { unsigned f : 8; };
void func_ov249_020d3a70(int param_1) {
    int child = *(int *)(param_1 + 4);
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 6;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    *(unsigned short *)(*(int *)child + 0x1ae) |= 1;
    {
        int c = *(int *)(*(int *)child + 0x3ac);
        ((struct lo8_020d1d30 *)(c + 8))->f &= ~1;
    }
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x40;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    func_ov107_020c5af8(*(int *)child, 0, 0x49, *(int *)child + 0x494);
    *(int *)(child + 0x4c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov249_020d3b38);
}
