/* Decision tick of the ov194 enemy (x3: ov194/195/196): acquires the closest target (+8, with
 * its squared distance) -- none returns; the surface distance (root minus both +0x80 radii)
 * must be inside the actor's +0x2d8 range; the +0x10 heading turns to the target's +0x190
 * from the actor's +0xb0. A running +0x44 timer requests sub-state 4. Otherwise, while the
 * +0x34 timer runs: beyond 10.0 request 4; inside 1.0 the target ahead of the actor's forward
 * (dot > 0.5) requests 0xe, else the sign of the cross product picks 0xc (left) or 0xd
 * (right); inside 3.0 request 6; further out a 1/61 roll decides an attack: a 0..1 roll of 0
 * requests 0xa and of 1 requests 0xb, each with a 1..3 repeat count in +0x48. With the +0x34
 * timer expired: inside 3.0 request 6, else arm the +0x44 timer (1 if not positive) and
 * request 4. */

#include "nitro/fx_types.h"
#include "game/engine.h"

extern int Ov107_FindNearestObject(int actor, int *distOut);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int node, int slot, void *cb);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern const VecFx32 data_02042258;

void Ov194_DecideTick(int node)
{
    int *state = *(int **)(node + 4);
    int dist;
    VecFx32 d;
    VecFx32 fwd;
    int obj;
    int target;
    int roll;

    state[2] = Ov107_FindNearestObject(*state, &dist);
    target = state[2];
    if (target == 0) {
        return;
    }
    obj = *state;
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(obj + 0x80));
    if (dist > *(int *)(*state + 0x2d8)) {
        return;
    }
    VEC_Subtract((VecFx32 *)(state[2] + 0x190), (VecFx32 *)(*state + 0xb0), &d);
    state[4] = FX_Atan2(d.x, d.z);
    if (state[0x11] > 0) {
        *(unsigned char *)(*state + 0x1c7) = 4;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (state[0xd] <= 0) {
        if (dist < 0x3000) {
            *(unsigned char *)(*state + 0x1c7) = 6;
            SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
            return;
        }
        if (state[0x11] <= 0) {
            state[0x11] = 1;
        }
        *(unsigned char *)(*state + 0x1c7) = 4;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist > 0xa000) {
        *(unsigned char *)(*state + 0x1c7) = 4;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist < 0x1000) {
        VEC_Normalize(&d, &d);
        Vec3TransformViaTempMtx(&fwd, (void *)(*state + 0xa0), &data_02042258);
        if (VEC_DotProduct(&d, &fwd) > 0x800) {
            *(unsigned char *)(*state + 0x1c7) = 0xe;
            SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
            return;
        }
        if ((int)(((long long)d.x * fwd.z + 0x800) >> 12) - (int)(((long long)d.z * fwd.x + 0x800) >> 12) < 0) {
            *(unsigned char *)(*state + 0x1c7) = 0xc;
            SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 0xd;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist < 0x3000) {
        *(unsigned char *)(*state + 0x1c7) = 6;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (RandNextScaled(0x3d) + (dist - dist) != 0) {
        return;
    }
    roll = RandNextScaled(2) + (dist - dist);
    if (roll == 0) {
        state[0x12] = RandNextScaled(3) + 1;
        *(unsigned char *)(*state + 0x1c7) = 0xa;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (roll != 1) {
        return;
    }
    state[0x12] = RandNextScaled(3) + 1;
    *(unsigned char *)(*state + 0x1c7) = 0xb;
    SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
}
