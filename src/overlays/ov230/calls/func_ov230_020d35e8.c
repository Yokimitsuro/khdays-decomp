/* c634 handler: set owner hw60 hi bit 0x40, arm func_ov230_020d3028(owner,0), then set hi
 * bits 0x80 and 0xe, set bit0 of owner+0x1ae, clear bit0 of the low byte at *(owner+0x3ac)+8,
 * clear obj[0x13], and dispatch into func_ov230_020d36c8. */
extern void func_ov230_020d3028(int owner, int a);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov230_020d36c8(void);
struct b8 { unsigned int b:8; };
static inline void hw60_or(int base, unsigned int k) {
    unsigned short v = *(unsigned short *)(base + 0x60);
    *(unsigned short *)(base + 0x60) =
        (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | k) << 0x18) >> 0x10));
}
void func_ov230_020d35e8(int self) {
    int *obj = *(int **)(self + 4);
    hw60_or(*obj, 0x40);
    func_ov230_020d3028(*obj, 0);
    hw60_or(*obj, 0x80);
    hw60_or(*obj, 0xe);
    *(unsigned short *)(*obj + 0x1ae) |= 1;
    ((struct b8 *)(*(int *)(*obj + 0x3ac) + 8))->b &= ~1;
    obj[0x13] = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov230_020d36c8);
}
