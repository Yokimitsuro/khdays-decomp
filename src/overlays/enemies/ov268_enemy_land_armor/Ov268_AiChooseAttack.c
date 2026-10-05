/* Ov268_AiChooseAttack -- ov268's move CHOOSER.
 *
 * Byte-identical to Ov208_AiChooseAttack modulo this overlay's own symbols; that is the rep of
 * the family and carries the analysis. See Ov206_DecisionTick for the chooser shape itself.
 *
 * A dispatcher reads the queued move at ctx[0]+0x1c7 and runs it; this decides what to queue there.
 * Every exit writes +0x1c7 and calls SetIndexedSlot with a NULL handler, i.e. "run what is queued".
 *
 * Both vectors are FLATTENED to the XZ plane (`[1] = 0`) -- this AI reasons purely in the ground
 * plane, so height never affects the choice. The facing vector is not normalised like ov206's:
 * after the transform its X and Z are overwritten straight from the sin/cos table, indexed by the
 * heading angle in ctx[0xc]. That already leaves it unit-length, which is why the dot product
 * against the (normalised) direction to the target is a valid cosine.
 *
 * With no target it queues move 2. Otherwise, unless the busy byte at *(ctx[1] + 0xad) is set, it
 * rolls a d100:
 *
 *   roll < 20        -> move 10
 *   roll < 60        -> move 5
 *   otherwise, close (gap < 0x5333): move 6 only if the target is ahead, else nothing
 *              far  (gap >= 0x5333): ahead -> move 5
 *                                    else  -> a second d100: <50 move 10, else move 9
 *
 * "Ahead" here is VEC_DotProduct(toTarget, forward) > 0x800: Q12's 1.0 is 0x1000, so 0.5 = a 60
 * degree cone -- tighter than ov206's 0x200. `gap` is the distance between the two collision radii
 * at +0x80.
 *
 * The second roll's comparison is UNSIGNED where the first is signed; both come straight from the
 * ROM's `bhi`/`blt` and are kept as-is.
 *
 * ctx[0x18] takes `*(int *)(*(int *)self + 0x2c) * 30 / 30` -- the two 30s cancel at runtime and
 * mwcc does not fold them (the multiply can overflow). See Ov206_DecisionTick.
 *
 * The angle -> sin/cos conversion is the documented Q12-radians form (codegen-cracks.md):
 * 0x28be60db9391 is 65536/(2*pi) in .32, the +0x800<<32 is rounding, and the (unsigned short) cast
 * is what makes the shifts come out as lsl#4/lsr#16/asr#4. */

#include "game/engine.h"

extern int Ov268_PickBestFacingNode(int obj, int kind);
extern void SetIndexedSlot(int self, int slot, void (*cb)(void));
extern void VEC_Subtract(const int *a, const int *b, int *dst);
extern int VEC_DotProduct(const int *a, const int *b);
extern int VEC_Normalize(const int *v, int *unit);
extern fx16 FX_Atan2(int x, int z);
extern int Ov107_ActionResource_GetOffsetAndScale(int a, int *out);
extern void ScaleVec3Fx12(int scale, const int *src, int *dst);
extern short data_0203d210[];

void Ov268_AiChooseAttack(int self) {
    int *ctx;
    int toTarget[3];
    int forward[3];
    int target;
    int tgt;
    int *owner;
    int gap;
    int scale;
    int roll;
    unsigned int idx;

    ctx = *(int **)(self + 4);
    ctx[0x18] = *(int *)(*(int *)self + 0x2c) * 30 / 30;

    target = Ov268_PickBestFacingNode(ctx[0], 0);
    ctx[4] = target;
    if (target == 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 2;
        SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    VEC_Subtract((const int *)(target + 0x190), (const int *)ctx[2], toTarget);
    toTarget[1] = 0;
    tgt = ctx[4];
    owner = (int *)ctx[0];
    gap = VEC_Normalize(toTarget, toTarget);
    gap -= owner[0x20] + *(int *)(tgt + 0x80);
    ctx[0xd] = FX_Atan2(toTarget[0], toTarget[2]);

    scale = Ov107_ActionResource_GetOffsetAndScale(*(int *)(ctx[0] + 0x3ac), forward);
    Vec3TransformViaTempMtx(&ctx[5], (const int *)(ctx[0] + 0xa0), forward);
    ScaleVec3Fx12(scale, &ctx[5], &ctx[5]);
    idx = (unsigned short)(((long long)ctx[0xc] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    forward[0] = data_0203d210[idx * 2];
    forward[1] = 0;
    forward[2] = data_0203d210[idx * 2 + 1];

    if (*(unsigned char *)(ctx[1] + 0xad) != 0) {
        return;
    }

    roll = RandNextScaled(100);
    if (roll < 0x14) {
        *(signed char *)(ctx[0] + 0x1c7) = 10;
        SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    if (roll < 0x3c) {
        *(signed char *)(ctx[0] + 0x1c7) = 5;
        SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (gap < 0x5333) {
        if (VEC_DotProduct(toTarget, forward) > 0x800) {
            *(signed char *)(ctx[0] + 0x1c7) = 6;
            SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
        }
        return;
    }

    if (VEC_DotProduct(toTarget, forward) > 0x800) {
        *(signed char *)(ctx[0] + 0x1c7) = 5;
        SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if ((unsigned int)RandNextScaled(100) < 0x32) {
        *(signed char *)(ctx[0] + 0x1c7) = 10;
        SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    *(signed char *)(ctx[0] + 0x1c7) = 9;
    SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
}
