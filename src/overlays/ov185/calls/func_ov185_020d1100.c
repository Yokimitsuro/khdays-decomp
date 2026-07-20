/* Kick off the tumble: pick a random axis, derive a spin from it, and arm the timer.
 *
 * Sets bit 1 and 2 of the owner's hw60 high byte, arms the countdown at ctx[0xa] from the
 * template's +0x2c, then rolls three independent components in [-0x1000, +0x1000], keeps
 * them as a vector at ctx+0x78 and normalises it.  Two cross products against the constant
 * at data_02042264 turn that axis into a perpendicular spin at ctx+0x84, which is then
 * scaled by a random magnitude in [0x500, 0xa00].
 *
 * THREE CODEGEN POINTS, and the first two are a matched pair worth remembering together:
 *  - `hi |= 6` on the hw60 halfword needs the EXPLICIT extract/reassemble spelling; the
 *    `struct hw60` bitfield adds an lsl#0x10/lsr#0x10 truncation pair and costs 8 bytes.
 *    `hi &= ~x` is the opposite -- the bitfield is what that one wants.  Both forms appear
 *    within a few functions of each other in this overlay, so neither is "the" spelling.
 *  - the three rolls are held in LOCALS and stored afterwards.  Assigning each directly
 *    into the vector emits the stores interleaved with the calls; the ROM keeps all three
 *    live and stores them together, which only happens with intermediates.
 *  - those locals must be declared with `z` before `y` (the assignment order), or the two
 *    callee-saved registers come out swapped.
 */
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern int func_02023eb4();
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *dst);
extern void func_01ffa724(int t, const Vec3 *a, Vec3 *b);
extern void func_0203c634(int *self, int action, void *cb);
extern Vec3 data_02042264;
extern void func_ov185_020d11f4(void);

void func_ov185_020d1100(int *self) {
    int *ctx = (int *)self[1];
    Vec3 *axis = (Vec3 *)((char *)ctx + 0x78);
    Vec3 *spin = (Vec3 *)((char *)ctx + 0x84);
    int z, y, x;

    {
        unsigned short hw60 = *(unsigned short *)(*ctx + 0x60);
        *(unsigned short *)(*ctx + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    }
    ctx[0xa] = *(int *)(self[0] + 0x2c) * 0x1e;

    z = func_02023eb4(0x2001) - 0x1000;
    y = func_02023eb4(0x2001) - 0x1000;
    x = func_02023eb4(0x2001) - 0x1000;
    axis->x = x;
    axis->y = y;
    axis->z = z;
    func_01ff8d18(axis, axis);

    VEC_CrossProduct(axis, &data_02042264, spin);
    VEC_CrossProduct(axis, spin, spin);
    func_01ffa724(func_02023eb4(0x501) + 0x500, spin, spin);

    ctx[0x18] = 0;
    ctx[0x24] = *(int *)(ctx[0x1d] + 0x18c);
    ctx[0xe] = 0;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), &func_ov185_020d11f4);
}
