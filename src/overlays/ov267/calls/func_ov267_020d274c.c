/* Enter the recovery-and-retreat state (x3: ov212/266/267). Raise flags 0x82 on the
 * hw60 hi byte, then drop flags 0xc on that SAME byte, raise flag 1 on the owner's
 * +0x1ae word, release the 3 tracked sub-objects, spawn effect 7 at the anchor point
 * (ctx[2]), reset the phase timer and chain to the wind-up wait (020cec2c).
 *
 * The two hw60 writes need OPPOSITE forms and the disassembly says which: `|= 0x82` at
 * +0x018 has NO lsl#0x10/lsr#0x10 trunc pair -> explicit extract/reassemble; `&= ~0xc`
 * at +0x03c HAS it -> bitfield. The vec3 goes to ov107_020c0b90 BY VALUE (r2, r3, [sp+0])
 * with the flag at [sp+4]. */
struct vec3 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned f : 8; };

extern void func_ov107_020c0b90(int obj, int cmd, struct vec3 v, int flag);
extern void func_0203c634(void *self, int idx, void *cb);
extern void func_ov267_020d2848(void);

void func_ov267_020d274c(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    int i = 0;
    unsigned short v;

    v = *(unsigned short *)(*ctx + 0x60);
    *(unsigned short *)(*ctx + 0x60) =
        (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x82) << 0x18) >> 0x10));
    ((struct hw60 *)(*ctx + 0x60))->hi &= ~0xc;
    *(unsigned short *)(*ctx + 0x1ae) |= 1;
    for (; i < 3; i++) {
        ((struct b8 *)(((int *)*ctx)[i + 0x133] + 8))->f &= ~1;
    }
    func_ov107_020c0b90(*ctx, 7, *(struct vec3 *)ctx[2], 0);
    ctx[0x10] = 0;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), func_ov267_020d2848);
}
