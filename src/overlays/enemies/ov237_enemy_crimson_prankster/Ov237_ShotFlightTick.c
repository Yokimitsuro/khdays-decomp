/* Flight tick of the ov237 shot: unless the owner (+0x390) holds (+0x4c0) or is in move 3, its sphere
 * (+0x74) pushes the first target it hits flat away at 0.5 (kind 1) with effect 1 1.25 above the shot and
 * the shot dies. While homing (+0x17a bit 0) it bends its +0x18 heading toward the nearest target when
 * they roughly agree (random spread) and trails effect 7 (up to five per owner, +0x49c). The +0xc
 * velocity is the heading at the +0x24 speed; homing re-arms the climb (+0x10 1.14 to 1.87, speed easing
 * to 1/16) with sound 0x12d variant 9, otherwise the climb falls off at the frame rate. The shot then
 * moves from its +0x2c point probing the floor (0x300): a floor hit ends it with effect 1 and the sound;
 * after 32.0 of travel (or on a +0x17a bit-1 contact, which also clears the owner's +0x38c) it pops with
 * effect 1. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { u8 b0 : 1; u8 b1 : 1; } Bits;

extern int Ov107_CollectSphereOverlaps(int owner, void *sphere, int *hits);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern int Ov107_InvokeHitCallback(int hit, int owner, int item, int kind, VecFx32 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, VecFx32 at, int flag);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern int Ov107_FindNearestObject(int actor, int kind);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern int FX_Div(int value, int denom);
extern void Ov107_BuildAndSendUpdate(int actor, int bank, int variant, int at);
extern int Collision_CastSphereEx(int collision, VecFx32 *origin, VecFx32 *dir, int radius, void *ignore);
extern int VEC_Mag(const VecFx32 *v);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void Ov237_ShotFlightTick(int *node)
{
    char *shot;
    int *state = (int *)node[1];
    int world;
    VecFx32 probe;
    int hits[4];
    VecFx32 push;
    VecFx32 fx;
    VecFx32 pos;
    VecFx32 to;
    VecFx32 dir;
    VecFx32 sum;
    int hit;

    shot = (char *)*state;
    world = *(int *)(shot + 4);
    if (*(int *)(*(int *)(shot + 0x390) + 0x4c0) == 0 && *(signed char *)(*(int *)(shot + 0x390) + 0x1c6) != 3) {
        long i;
        long n = Ov107_CollectSphereOverlaps(*(int *)(shot + 0x390), shot + 0x74, hits);

        for (i = 0; i < n; i++) {
            VEC_Subtract((VecFx32 *)(hits[i] + 0x74), (VecFx32 *)(shot + 0x74), &push);
            push.y = 0;
            VEC_Normalize(&push, &push);
            ScaleVec3Fx12(0x800, &push, &push);
            if (Ov107_InvokeHitCallback(hits[i], *state, *(int *)(*state + 0x390), 1, &push, 0) != 0) {
                fx = *(VecFx32 *)(*state + 0xb0);
                fx.y += 0x1400;
                func_ov107_020c0b90(*(int *)(*state + 0x390), 1, fx, 0);
                *(signed char *)(*state + 0x1c7) = 0;
                *(int *)(*state + 0x38c) = 0;
                SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
        }
    }
    if (((Bits *)(*state + 0x17a))->b0) {
        int target;

        pos = *(VecFx32 *)(*state + 0xb0);
        target = Ov107_FindNearestObject(*state, 0);
        if (target != 0) {
            VEC_Subtract((VecFx32 *)(target + 0x74), (VecFx32 *)(shot + 0x74), &to);
            to.y = 0;
            dir = *(VecFx32 *)(state + 6);
            dir.y = 0;
            VEC_Normalize(&to, &to);
            VEC_Normalize(&dir, &dir);
            if (VEC_DotProduct(&to, &dir) > 0x800) {
                int spread;
                int ang;

                VEC_Add(&to, &dir, &sum);
                spread = RandNextScaled(0x10c1) - 0x860;
                ang = FX_Atan2(sum.x, sum.z);
                ang += spread;
                {
                    int idx = ANG2IDX(ang) * 2;

                    state[6] = data_0203d210[idx];
                    state[8] = data_0203d210[idx + 1];
                }
            }
        }
        pos.y -= 0x600;
        if (*(signed char *)(*(int *)(*state + 0x390) + 0x49c) < 5) {
            func_ov107_020c0b90(*(int *)(*state + 0x390), 7, pos, 0);
            (*(signed char *)(*(int *)(*state + 0x390) + 0x49c))++;
        }
    }
    state[3] = FX_MUL(state[6], state[9]);
    state[5] = FX_MUL(state[8], state[9]);
    if (!((Bits *)(*state + 0x17a))->b0) {
        state[4] -= FX_MUL(FX_Div(*(int *)(node[0] + 0x2c), 0x88), 0x100);
    } else {
        Ov107_BuildAndSendUpdate(*(int *)(*state + 0x390), 0x12d, 9, state[2]);
        state[4] = RandNextScaled(0x301) + 0x900;
        state[9] += (0x100 - state[9]) / 20;
    }
    VEC_Subtract((VecFx32 *)state[2], (VecFx32 *)(state + 0xb), &probe);
    *(VecFx32 *)(state + 0xb) = *(VecFx32 *)state[2];
    hit = Collision_CastSphereEx(*(int *)(world + 0x7c), (VecFx32 *)state[2], &probe, 0x300, 0);
    if (hit != 0 && *(int *)(hit + 8) == 0) {
        func_ov107_020c0b90(*(int *)(*state + 0x390), 1, *(VecFx32 *)(*state + 0xb0), 0);
        Ov107_BuildAndSendUpdate(*(int *)(*state + 0x390), 0x12d, 9, state[2]);
        *(int *)(*state + 0x38c) = 0;
        *(signed char *)(*state + 0x1c7) = 0;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0xa] += VEC_Mag(&probe);
    if (state[0xa] < 0x20000 && !((Bits *)(*state + 0x17a))->b1) {
        return;
    }
    func_ov107_020c0b90(*(int *)(*state + 0x390), 1, *(VecFx32 *)(*state + 0xb0), 0);
    if (((Bits *)(*state + 0x17a))->b1) {
        *(int *)(*state + 0x38c) = 0;
    }
    *(signed char *)(*state + 0x1c7) = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
