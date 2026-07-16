/* func_ov249_020d1c1c -- pick the reaction for the current stance, or fall through to steering.
 *
 * func_ov249_020d10b4 returning negative aborts to a plain c634 re-entry.
 *
 * When the flag at ctx[1]+0xad is SET the function is just the Y-rotation steering tail shared
 * with func_ov228_020d01e8: build a MtxFx33 from the heading at +0x40 and rotate the owner's
 * offset vector into ctx+0x10. (See codegen-cracks.md for the Q12-radians -> sin/cos conversion.)
 *
 * When it is clear, the stance at +0x5c selects a (mode, arg) pair to fire -- 0 -> (3, 2),
 * 2 -> (9, 7), 3 -> (6, 5) -- and then continues into func_ov249_020d1da0. Any other stance
 * parks 2 in ctx[0]+0x1c7 and re-enters with no callback, i.e. gives up. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int m[9];
} MtxFx33;

extern int func_ov249_020d10b4(int self);
extern void func_0203c634(int self, int action, void *cb);
extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_ov249_020d10a0(int owner, int a);
extern void func_ov249_020d1da0(void);
extern void MTX_RotY33_(MtxFx33 *mtx, int sinVal, int cosVal);
extern void MTX_MultVec33(const VecFx32 *v, const MtxFx33 *m, VecFx32 *dst);
extern short data_0203d210[];

void func_ov249_020d1c1c(int self) {
    int *ctx;
    MtxFx33 mtx;
    int idx;

    ctx = *(int **)(self + 4);
    if (func_ov249_020d10b4(self) < 0) {
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (*(unsigned char *)(ctx[1] + 0xad) == 0) {
        switch (ctx[0x17]) {
        case 0:
            func_ov107_020c9264(ctx[0], 3, 0);
            func_ov249_020d10a0(ctx[0], 2);
            break;
        case 2:
            func_ov107_020c9264(ctx[0], 9, 0);
            func_ov249_020d10a0(ctx[0], 7);
            break;
        case 3:
            func_ov107_020c9264(ctx[0], 6, 0);
            func_ov249_020d10a0(ctx[0], 5);
            break;
        default:
            *(unsigned char *)(ctx[0] + 0x1c7) = 2;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
        func_0203c634(self, *(signed char *)(self + 0x20), func_ov249_020d1da0);
        return;
    }

    idx = (unsigned short)(((long long)ctx[0x10] * 0x28be60db9391LL + 0x80000000000LL) >> 44)
          >> 4;
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((const VecFx32 *)(*(int *)(ctx[0] + 0x490) + 0x2c), &mtx,
                  (VecFx32 *)((char *)ctx + 0x10));
}
