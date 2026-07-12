/* Enter reaction: raise flag 0x80 then clear flag 0 in the high byte at (*child)+0x60,
 * clear bit 0 in the low byte of [+8] of the child slot at (*child)+0x388, copy the const
 * offset vector into (child)+0xc, and register the handler. */
struct Vec3_020d3ebc { int x, y, z; };
extern const struct Vec3_020d3ebc data_02041dc8;
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov238_020d2cf4(int);
struct node60_020d3ebc { unsigned short lo : 8; unsigned short hi : 8; };
struct lo8_020d3ebc { unsigned f : 8; };
void func_ov238_020d2c44(int param_1) {
    int child = *(int *)(param_1 + 4);
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x80;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    ((struct node60_020d3ebc *)(*(int *)child + 0x60))->hi &= ~1;
    {
        int c = *(int *)(*(int *)child + 0x388);
        ((struct lo8_020d3ebc *)(c + 8))->f &= ~1;
    }
    *(struct Vec3_020d3ebc *)(child + 0xc) = data_02041dc8;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov238_020d2cf4);
}
