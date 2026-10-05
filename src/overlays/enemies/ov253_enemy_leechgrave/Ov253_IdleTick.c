/* Ov253_IdleTick -- idle tick: the +0x18 speed follows twice the frame step (30 / 15);
 * the scene's +0xa8 list is searched for the nearest visible entity ahead of the actor's +0xa0
 * frame (dot with the forward axis at least 0.25; distance from the +4 anchor minus the
 * entity's +0x80 radius plus 2.0) and the +0x14 heading turns towards it; when it is within
 * 4.0 and well ahead (dot 0.5) a 1/61 chance picks sub-state 7 (60 %) or 5 and releases the
 * slot. Otherwise the +0x1c timer runs down; expired -- or with an empty +0x21a stock -- the
 * +0x38c item's +0xa8 flag clears and, once the +8 item's animation is free, sub-state 4 is
 * requested and the slot released. Codegen: `+ (v - v)` is the documented random copy artifact. */

#include "nitro/fx_types.h"

struct hw60 { unsigned short lo : 8, hi : 8; };
struct w40 { int b0 : 1, b1 : 1; };

extern void Vec3TransformViaTempMtx(VecFx32 *out, void *rotation, const VecFx32 *in);
extern int List_First(int list);
extern int List_Next(int list);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx16 FX_Atan2(int y, int x);
extern int RandNextScaled(int scale);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const VecFx32 data_02042258;

void Ov253_IdleTick(int *node) {
    int *state = (int *)node[1];
    int bestnode = 0;
    int best = 0x7fffffff;
    int scene = *(int *)(*state + 4);
    VecFx32 bestv;
    VecFx32 fwd;
    VecFx32 v;
    int it;
    int hit;
    int dist;
    int v_;

    state[6] = *(int *)(node[0] + 0x2c) * 0x1e / 0xf;
    Vec3TransformViaTempMtx(&fwd, (void *)(*state + 0xa0), &data_02042258);
    it = List_First(scene + 0xa8);
    hit = it == 0 ? 0 : *(int *)it;
    while (hit != 0) {
        if (((struct w40 *)(hit + 0x40))->b1 != 0 && (((struct hw60 *)(hit + 0x60))->lo & 1) != 0) {
            VEC_Subtract((VecFx32 *)(hit + 0x74), (VecFx32 *)state[1], &v);
            v.y = 0;
            dist = VEC_Normalize(&v, &v);
            if (VEC_DotProduct(&fwd, &v) >= 0x400) {
                dist -= *(int *)(hit + 0x80) + 0x2000;
                if (dist < 0) {
                    dist = 0;
                }
                if (dist < best) {
                    bestv = v;
                    best = dist;
                    bestnode = hit;
                }
            }
        }
        it = List_Next(scene + 0xa8);
        hit = it == 0 ? 0 : *(int *)it;
    }
    if (bestnode != 0) {
        state[5] = FX_Atan2(bestv.x, bestv.z);
        if (best < 0x4000) {
            if (VEC_DotProduct(&fwd, &bestv) >= 0x800) {
                if (RandNextScaled(0x3d) + (v_ - v_) == 0) {
                    if (RandNextScaled(0x65) + (v_ - v_) < 0x3c) {
                        *(unsigned char *)(*state + 0x1c7) = 7;
                    } else {
                        *(unsigned char *)(*state + 0x1c7) = 5;
                    }
                    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
                    return;
                }
            }
        }
    }
    state[7] -= *(int *)(node[0] + 0x2c);
    if (state[7] > 0 && *(short *)(*state + 0x200 + 0x1a) != 0) {
        return;
    }
    *(unsigned char *)(*(int *)(*state + 0x38c) + 0xa8) = 0;
    if (*(unsigned char *)state[2] != 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 4;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
