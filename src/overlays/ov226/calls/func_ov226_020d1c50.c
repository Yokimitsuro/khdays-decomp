/* Enter the reaction state: clear the busy counter (+0x78), raise flags 0xc0 then
 * 0x0e in the high byte at (*child)+0x60, set bit 0 of the halfword at (*child)+0x1ae,
 * clear bit 0 in the low byte of [+8] across the 5 child slots at (*child)+0x3ac, run
 * the ov107 effect, reset the timer (+0x5c) and register the per-actor handler. */
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov226_020d1d2c(int);
struct lo8_020d1c4c { unsigned f : 8; };
void func_ov226_020d1c50(int param_1) {
    int child = *(int *)(param_1 + 4);
    int i;
    *(int *)(child + 0x78) = 0;
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0xc0;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0xe;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    *(unsigned short *)(*(int *)child + 0x1ae) |= 1;
    for (i = 0; i < 5; i++) {
        int c = ((int *)*(int *)child)[i + 0xeb];
        ((struct lo8_020d1c4c *)(c + 8))->f &= ~1;
    }
    func_ov107_020c5af8(*(int *)child, 0, 0x48, *(int *)(child + 8));
    *(int *)(child + 0x5c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov226_020d1d2c);
}
