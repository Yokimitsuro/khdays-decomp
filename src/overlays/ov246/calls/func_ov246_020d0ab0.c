/* c634 handler: set owner hw60 hi bits 0x86, clear bit0 of the low byte at *(owner+0x384)+8,
 * and dispatch via func_0203c634. */
struct b8 { unsigned int b : 8; };
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov246_020d0b18(void);
void func_ov246_020d0ab0(int self) {
    int *obj = *(int **)(self + 4);
    {
        unsigned short v = *(unsigned short *)(*obj + 0x60);
        *(unsigned short *)(*obj + 0x60) =
            (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10));
    }
    ((struct b8 *)(*(int *)(*obj + 0x384) + 8))->b &= ~1;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov246_020d0b18);
}
