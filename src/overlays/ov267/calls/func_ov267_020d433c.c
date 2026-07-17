/* Enter the wind-up/telegraph state (x3: ov212/266/267). Raise flags 0x46 on the
 * hw60 hi byte and flag 1 on the owner's +0x1ae word, release the 3 tracked
 * sub-objects, spawn the telegraph effect at the owner's cached point (+0x508),
 * kick the 0x49 animation, reset the phase timer and advance state.
 *
 * Sibling of func_ov212_020d0620; note this hw60 write has NO lsl#0x10/lsr#0x10
 * trunc pair, so it takes the explicit extract/reassemble form. The vec3 goes to
 * ov107_020c0b90 BY VALUE (r2, r3 and [sp+0]), with the flag at [sp+4]. */
struct vec3 { int x, y, z; };
struct b8 { unsigned f : 8; };

extern void func_ov107_020c0b90(int obj, int cmd, struct vec3 v, int flag);
extern void func_ov107_020c5af8(int a, int b, int c, void *d);
extern void func_0203c634(void *self, int idx, void *cb);
extern void func_ov267_020d4428(void);

void func_ov267_020d433c(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    int i = 0;
    unsigned short v;

    v = *(unsigned short *)(*ctx + 0x60);
    *(unsigned short *)(*ctx + 0x60) =
        (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x46) << 0x18) >> 0x10));
    *(unsigned short *)(*ctx + 0x1ae) |= 1;
    for (; i < 3; i++) {
        ((struct b8 *)(((int *)*ctx)[i + 0x133] + 8))->f &= ~1;
    }
    func_ov107_020c0b90(*ctx, 1, *(struct vec3 *)(*ctx + 0x508), 0);
    func_ov107_020c5af8(*ctx, 0, 0x49, (void *)(*ctx + 0x74));
    ctx[0x10] = 0;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), func_ov267_020d4428);
}
