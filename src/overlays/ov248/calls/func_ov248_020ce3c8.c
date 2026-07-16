/* func_ov248_020ce3c8 -- steer toward the target: rotate the owner's offset vector by the stored
 * heading and store the result as the object's own offset (+0x10).
 *
 * Two early exits dispatch back through c634 with no callback (a plain re-entry):
 *   - func_ov248_020cd524 returning negative (nothing to steer toward);
 *   - the flag at ctx[1]+0xad being clear, which also parks 2 in ctx[0]+0x1c7.
 * A non-zero ctx+0x5c returns outright without dispatching at all.
 *
 * The heading at +0x40 is Q12 RADIANS, converted to a 12-bit table index; see
 * codegen-cracks.md ("Q12 radians -> 16-bit angle -> sin/cos table") for why each shift is what
 * it is. data_0203d210 is sin/cos interleaved, so [idx*2] is the sine and [idx*2+1] the cosine --
 * exactly the (sinVal, cosVal) pair MTX_RotY33_ wants. The 0x24-byte stack slot is the MtxFx33 it
 * builds there.
 *
 * NitroSDK's vector-first argument order (v, m, dst) is what makes the tail read sensibly: take
 * the vector at *(ctx[0]+0x490)+0x2c, rotate it about Y, land it in ctx+0x10. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int m[9];
} MtxFx33;

extern int func_ov248_020cd524(int self);
extern void func_0203c634(int self, int action, void *cb);
extern void MTX_RotY33_(MtxFx33 *mtx, int sinVal, int cosVal);
extern void MTX_MultVec33(const VecFx32 *v, const MtxFx33 *m, VecFx32 *dst);
extern short data_0203d210[];

void func_ov248_020ce3c8(int self) {
    int *ctx;
    MtxFx33 mtx;
    int idx;

    ctx = *(int **)(self + 4);
    if (func_ov248_020cd524(self) < 0) {
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (*(unsigned char *)(ctx[1] + 0xad) == 0) {
        *(unsigned char *)(ctx[0] + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (ctx[0x17] != 0) {
        return;
    }

    idx = (unsigned short)(((long long)ctx[0x10] * 0x28be60db9391LL + 0x80000000000LL) >> 44)
          >> 4;
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((const VecFx32 *)(*(int *)(ctx[0] + 0x490) + 0x2c), &mtx,
                  (VecFx32 *)((char *)ctx + 0x10));
}
