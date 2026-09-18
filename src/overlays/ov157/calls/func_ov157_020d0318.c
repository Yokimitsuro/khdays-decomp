/* Dash entry of the ov156 enemy (and its byte-identical twin): clears the +0x28 timer, sets bit
 * 0 of the owner's +0x60 high byte and then clears bits 0x8c of it, sets bit 0 of the byte at
 * *(owner+0x388)+8, copies the owner's +0x394 facing into +0x18 and scales it by 0x500 into the
 * +0xc velocity, clears bit 0 of the +0x24 flags and the +0x2c timer, then hands off to ce5d4. */
struct hw60 { unsigned short lo:8, hi:8; };
struct b8 { unsigned int b:8; };
struct vec { int x, y, z; };
extern void func_01ffa724(int scale, int *v, unsigned int *out);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov157_020d03f4(void);
void func_ov157_020d0318(int self) {
    int *obj = *(int **)(self + 4);
    int *dst = obj + 6;
    obj[10] = 0;
    {
        unsigned short v = *(unsigned short *)(*obj + 0x60);
        *(unsigned short *)(*obj + 0x60) =
            (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));
    }
    ((struct hw60 *)(*obj + 0x60))->hi &= ~0x8c;
    ((struct b8 *)(*(int *)(*obj + 0x388) + 8))->b |= 1;
    *(struct vec *)(obj + 6) = *(struct vec *)(*obj + 0x394);
    func_01ffa724(0x500, dst, (unsigned int *)(obj + 3));
    *(unsigned char *)(obj + 9) &= ~1;
    obj[11] = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov157_020d03f4);
}
