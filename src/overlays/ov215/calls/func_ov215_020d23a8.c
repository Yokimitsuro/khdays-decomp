/* Enter the grounded state: flag the owner, drop the sub-node's active bit, and spawn the
 * landing effect at the owner's position.
 *
 * The position at owner+0x74 is passed BY VALUE to the spawn call.  That is what the ROM's
 * `sub r3, sp, #8` is doing before the ldm/stm pair: a 12-byte struct argument straddles
 * r2, r3 and the first outgoing stack word, so mwcc lays it out at sp-8 and the third
 * component lands at sp+0 on its own.  Written as three int arguments it does not match.
 *
 * Both hw60 sets use the EXPLICIT extract/reassemble spelling (the bitfield form adds a
 * truncation pair on `|=`), while the sub-node's low-byte clear at +8 uses the bitfield --
 * the two idioms sit four statements apart here.
 */
typedef struct { int x, y, z; } Vec3;
struct LowByteFlags { unsigned bits : 8; };

extern void func_ov107_020c0b90(int owner, int a, Vec3 v, int b);
extern void func_ov107_020c5af8(int owner, int a, int kind, const Vec3 *v);
extern void func_0203c634(int *self, int action, void *cb);
extern void func_ov215_020d24a0(void);

void func_ov215_020d23a8(int *self) {
    int *ctx = (int *)self[1];

    {
        unsigned short hw60 = *(unsigned short *)(*ctx + 0x60);
        *(unsigned short *)(*ctx + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    }
    *(unsigned short *)(*ctx + 0x1ae) |= 1;
    ((struct LowByteFlags *)(*(int *)(*ctx + 0x3ac) + 8))->bits &= ~1;
    {
        unsigned short hw60 = *(unsigned short *)(*ctx + 0x60);
        *(unsigned short *)(*ctx + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    }

    func_ov107_020c0b90(*ctx, 0, *(Vec3 *)((char *)*ctx + 0x74), 0);
    func_ov107_020c5af8(*ctx, 0, 0x49, (const Vec3 *)((char *)*ctx + 0x74));
    ctx[0x14] = 0;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), &func_ov215_020d24a0);
}
