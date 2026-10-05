/* Ov276_AiWalkToTargetTick -- face the target and close in, unless it is already too near.
 *
 * Takes the vector from the target (+0xc) to the owner's position (ctx[0]+0x190), turns it into a
 * heading with FX_Atan2(dx, dz) -- an atan2, since the result is fed to the Q12-radians
 * conversion below -- and parks that heading at +0x44.
 *
 * VEC_Normalize is handed the SAME vector twice, so it reads as a self dot-product (squared
 * magnitude). Subtracting ctx[0]+0x480 from it and comparing against 0x2000 is the range test:
 * inside the threshold the move is abandoned (2 parked in ctx[0]+0x1c7, c634 re-entered with no
 * callback).
 *
 * Beyond the threshold, a clear flag at ctx[1]+0xad ends the move a different way (mode 3 +
 * Ov276_startAnim). Otherwise the tail is the same Y-rotation steering as
 * Ov228_AiStanceMoveFinish: build a MtxFx33 from the heading's sin/cos and rotate the owner's offset
 * vector into ctx+0x10. See codegen-cracks.md for the radians->index conversion.
 *
 * Stack: 0x30 = the 0x24-byte MtxFx33 at sp+0 plus the 0xc-byte VecFx32 at sp+0x24. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

typedef struct {
    int m[9];
} MtxFx33;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int dx, int dz);
extern int VEC_Normalize(const VecFx32 *a, const VecFx32 *b);
extern void SetIndexedSlot(int self, int action, void *cb);
extern void Ov276_startAnim(int owner, int a);
extern void MTX_RotY33_(MtxFx33 *mtx, int sinVal, int cosVal);
extern void MTX_MultVec33(const VecFx32 *v, const MtxFx33 *m, VecFx32 *dst);
extern short data_0203d210[];

void Ov276_AiWalkToTargetTick(int self) {
    int *ctx;
    /* Declared in reverse of their stack order: mwcc lays the stack locals out back-to-front, so
     * `d` first puts `mtx` at sp+0 and `d` at sp+0x24, which is what the ROM does. */
    VecFx32 d;
    MtxFx33 mtx;
    int idx;

    ctx = *(int **)(self + 4);
    VEC_Subtract((const VecFx32 *)(ctx[0] + 0x190), (const VecFx32 *)ctx[3], &d);
    ctx[0x11] = FX_Atan2(d.x, d.z);

    if (VEC_Normalize(&d, &d) - *(int *)(ctx[0] + 0x480) < 0x2000) {
        *(unsigned char *)(ctx[0] + 0x1c7) = 2;
        SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (*(unsigned char *)(ctx[1] + 0xad) == 0) {
        Ov107_PostTagUpdate((Actor *)ctx[0], 3, 0);
        Ov276_startAnim(ctx[0], 2);
        return;
    }

    idx = (unsigned short)(((long long)ctx[0x11] * 0x28be60db9391LL + 0x80000000000LL) >> 44)
          >> 4;
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((const VecFx32 *)(*(int *)(ctx[0] + 0x470) + 0x2c), &mtx,
                  (VecFx32 *)((char *)ctx + 0x10));
}
