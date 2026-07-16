/* func_ov233_020cf398 -- the wind-up: hold, then emit along the heading during a timing window.
 *
 * Bit 7 of the byte at +0x61 marks "wound up". Until it is set the timer at +0x4c just runs, and
 * at 0x110 the wind-up fires once: set the bit, reset the timer, kick modes 0x12/0xc.
 *
 * After that, the timer keeps running and the emit happens only inside the window
 * [0x990, 0xf68] -- outside it this tick does nothing but the ending below.
 *
 * The emit takes the anchor at ctx[0]+0x494 (a VecFx32 plus a trailing word at +0x4a0, which is
 * what func_01ffa724 wants), builds the ground-plane direction {sin, 0, cos} from the Q12-radians
 * heading at +0x40 (see codegen-cracks.md), transforms it, adds it onto the anchor position and
 * hands the anchor to func_ov233_020cd028.
 *
 * The ending is the family's usual pair: a set ctx[1]+0xad means "not ready", which degenerates
 * into the Y-rotation steering tail; otherwise park 2 in ctx[0]+0x1c7 and re-enter with no
 * callback.
 *
 * Stack 0x40 = vec(0xc) at sp+0, anchor(0x10) at sp+0xc, MtxFx33(0x24) at sp+0x1c. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int m[9];
} MtxFx33;

typedef struct {
    VecFx32 pos;
    int xform;
} Anchor;

extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_ov233_020cd49c(int owner, int a);
extern void func_01ffa724(int xform, VecFx32 *v, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
/* Slots 3 and 4 are used one-or-the-other across this family: func_ov228_020d193c calls it as
 * (ctx, 2, 0, &params) with a 0x38-byte block in the last slot, this one as (ctx, 1, &anchor, 0). */
extern void func_ov233_020cd028(int *ctx, int kind, void *a, void *b);
extern void func_0203c634(int self, int action, void *cb);
extern void MTX_RotY33_(MtxFx33 *mtx, int sinVal, int cosVal);
extern void MTX_MultVec33(const VecFx32 *v, const MtxFx33 *m, VecFx32 *dst);
extern short data_0203d210[];

void func_ov233_020cf398(int self) {
    int *ctx;
    /* Declared in reverse of their stack order -- mwcc lays struct locals out back-to-front, so
     * this puts vec at sp+0, anchor at sp+0xc and mtx at sp+0x1c. */
    MtxFx33 mtx;
    Anchor anchor;
    VecFx32 vec;
    int idx;

    ctx = *(int **)(self + 4);
    ctx[0x13] += *(int *)(*(int *)self + 0x2c);

    if ((*(unsigned char *)((char *)ctx + 0x61) & 0x80) == 0) {
        if (ctx[0x13] < 0x110) {
            return;
        }
        *(unsigned char *)((char *)ctx + 0x61) |= 0x80;
        ctx[0x13] = 0;
        func_ov107_020c9264(ctx[0], 0x12, 0);
        func_ov233_020cd49c(ctx[0], 0xc);
        return;
    }

    if (ctx[0x13] >= 0x990 && ctx[0x13] <= 0xf68) {
        anchor = *(Anchor *)(ctx[0] + 0x494);

        idx = (unsigned short)(((long long)ctx[0x10] * 0x28be60db9391LL + 0x80000000000LL) >> 44)
              >> 4;
        vec.x = data_0203d210[idx * 2];
        vec.y = 0;
        vec.z = data_0203d210[idx * 2 + 1];

        func_01ffa724(anchor.xform, &vec, &vec);
        VEC_Add(&vec, &anchor.pos, &anchor.pos);
        func_ov233_020cd028(ctx, 1, &anchor, 0);
    }

    /* Tested == 0 so the give-up ending is the fall-through and the steering tail is the branch
     * target, matching the ROM's block order (the != 0 form inlines the tail and inverts it). */
    if (*(unsigned char *)(ctx[1] + 0xad) == 0) {
        *(unsigned char *)(ctx[0] + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    idx = (unsigned short)(((long long)ctx[0x10] * 0x28be60db9391LL + 0x80000000000LL) >> 44)
          >> 4;
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((const VecFx32 *)(*(int *)(ctx[0] + 0x490) + 0x2c), &mtx,
                  (VecFx32 *)((char *)ctx + 0x10));
}
