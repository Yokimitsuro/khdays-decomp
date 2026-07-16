/* func_ov228_020d0cb0 -- aim the pending shot along the stored heading, then re-arm.
 * Only does the aiming work while a pending target is held at +0x8; the retune and dispatch at
 * the end happen either way.
 *
 * The heading at +0x40 is Q12 RADIANS. It is converted to a 16-bit angle index and turned into a
 * ground-plane direction vector {sin, 0, cos}, which is transformed by the owner's matrix
 * (+0x4a0), offset from the target's position (+0x190) and handed to func_ov107_020c5c54. The
 * pending target is then cleared.
 *
 * The radians->index conversion, spelled out (it appears identically in func_ov137_020cd2d8 and
 * func_ov228_020d01e8):
 *   0x28be60db9391 is 65536/(2*pi) in .32 fixed point (= 10430.3784), so the 64-bit product is
 *   the heading scaled to a full turn; adding 0x800 << 32 rounds it; >> 44 then lands the 16-bit
 *   angle. The (unsigned short) cast is what produces the `lsl #4 ; lsr #16` pair, and the
 *   following >> 4 is an `asr` because a u16 promotes to signed int -- that gives the 12-bit
 *   index into the 4096-entry table.
 * data_0203d210 holds sin and cos interleaved: sin at [idx*2], cos at [idx*2+1].
 *
 * NONMATCHING: 260/260 bytes, first diff at 0x4d -- a register permutation (r2/r3 and ip/r3) in
 * the table lookup, plus mwcc hoisting `add r1,sp,#0` one slot later than the ROM. Hoisting the
 * vector's address into its own local does not move it (that fix worked on func_ov137_020cdac4;
 * not here).
 *
 * ★ The conversion itself is BYTE-EXACT -- the whole umull/mla/mla + rounding + lsl/lsr/asr
 * sequence at 0x14..0x48 matches. That derivation is the valuable part and is now written up in
 * codegen-cracks.md; it unlocks func_ov137_020cd2d8 (7 members) and func_ov228_020d01e8 (6),
 * which carry the identical idiom. Use those first -- this one is only held up by the register
 * pair. */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern void func_01ffa724(int mtx, Vec3 *v, Vec3 *out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c5c54(int owner, Vec3 *v);
extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_ov228_020cf330(int owner, int a);
extern void func_0203c634(int self, int action, void (*cb)(void));
extern void func_ov228_020d0db4(void);
extern short data_0203d210[];

void func_ov228_020d0cb0(int self) {
    int *ctx;
    Vec3 dir;
    Vec3 *p;
    int idx;

    ctx = *(int **)(self + 4);
    if (ctx[2] != 0) {
        idx = (unsigned short)(((long long)ctx[0x10] * 0x28be60db9391LL + 0x80000000000LL) >> 44)
              >> 4;
        dir.y = 0;
        p = &dir;
        dir.x = data_0203d210[idx * 2];
        dir.z = data_0203d210[idx * 2 + 1];

        func_01ffa724(*(int *)(ctx[0] + 0x4a0), p, p);
        VEC_Subtract((const Vec3 *)(ctx[2] + 0x190), p, p);
        func_ov107_020c5c54(ctx[0], p);
        ctx[2] = 0;
    }

    func_ov107_020c9264(ctx[0], 0x13, 0);
    func_ov228_020cf330(ctx[0], 0xd);
    ctx[0x13] = 0;
    *(unsigned char *)((char *)ctx + 0x61) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), func_ov228_020d0db4);
}
