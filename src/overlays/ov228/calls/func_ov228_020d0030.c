/* func_ov228_020d0030 -- the wait loop of the approach: hold the stance for a few ticks, then
 * commit. This is the other half of func_ov228_020cfeac, which enters here; from here the object
 * either loops back into 020cfeac or moves on to func_ov228_020d01e8.
 *
 * func_ov228_020cf344 returns the current range (negative aborts). Inside 0x1000 there is a 45%
 * chance per tick of breaking off early: stance 1, 4 parked in ctx[0]+0x1c7, no callback.
 *
 * Otherwise the retry counter at +0x50 ticks down; while it is still positive the object
 * re-enters 020cfeac and the loop goes round again. When it runs out, the stance at +0x5c picks a
 * parting mode -- 0 -> (4, 3), 2 -> 0xa, 3 -> 7, anything else nothing -- and the object commits
 * to func_ov228_020d01e8.
 *
 * As everywhere in this family, a set ctx[1]+0xad flag means "not ready yet" and the whole tick
 * degenerates into the Y-rotation steering tail (see codegen-cracks.md for the Q12-radians
 * conversion). */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int m[9];
} MtxFx33;

extern int func_ov228_020cf344(int self);
extern void func_0203c634(int self, int action, void *cb);
extern int func_02023eb4(int n);
extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_ov228_020cf330(int owner, int a);
extern void func_ov228_020cfeac(void);
extern void func_ov228_020d01e8(void);
extern void MTX_RotY33_(MtxFx33 *mtx, int sinVal, int cosVal);
extern void MTX_MultVec33(const VecFx32 *v, const MtxFx33 *m, VecFx32 *dst);
extern short data_0203d210[];

void func_ov228_020d0030(int self) {
    int *ctx;
    MtxFx33 mtx;
    int range;
    int idx;

    ctx = *(int **)(self + 4);
    range = func_ov228_020cf344(self);
    if (range < 0) {
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (*(unsigned char *)(ctx[1] + 0xad) == 0) {
        if (range < 0x1000 && (unsigned int)func_02023eb4(100) < 0x2d) {
            ctx[0x17] = 1;
            *(unsigned char *)(ctx[0] + 0x1c7) = 4;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }

        if (--ctx[0x14] > 0) {
            func_0203c634(self, *(signed char *)(self + 0x20), func_ov228_020cfeac);
            return;
        }

        switch (ctx[0x17]) {
        case 0:
            func_ov107_020c9264(ctx[0], 4, 0);
            func_ov228_020cf330(ctx[0], 3);
            break;
        case 2:
            func_ov107_020c9264(ctx[0], 0xa, 0);
            break;
        case 3:
            func_ov107_020c9264(ctx[0], 7, 0);
            break;
        }

        func_0203c634(self, *(signed char *)(self + 0x20), func_ov228_020d01e8);
        return;
    }

    idx = (unsigned short)(((long long)ctx[0x10] * 0x28be60db9391LL + 0x80000000000LL) >> 44)
          >> 4;
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((const VecFx32 *)(*(int *)(ctx[0] + 0x490) + 0x2c), &mtx,
                  (VecFx32 *)((char *)ctx + 0x10));
}
