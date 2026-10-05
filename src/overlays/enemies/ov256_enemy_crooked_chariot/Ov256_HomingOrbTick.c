/* Homing-orb tick: the +0x1c timer accumulates the frame rate. The nearest target (020cab14) becomes
 * +0x24; the orb heads for its +0x190 point raised by 1.0 from the +8 point (heading +0x18) at 1.13
 * less 1/32 per level of the owner's +0x398 +0x45c, kept in +0xc. After two ticks moving on all
 * three axes (+0x20), bit 7 of the actor's +0x61 byte clears. A 1.0 sphere at the actor's +0x74 point
 * sweeps the actor list on behalf of the +0x398 owner: the first entity whose +2 id bit is clear in
 * the +0x21 mask and that accepts a 0.5 push along the heading (kind 4) gets its bit set, the owner
 * spawns effect 4 at the +8 point and pose 0 is requested. The mask keeps only the entities still in
 * the sphere. Without a target, past 7.0, or once blocked/grounded (+0x17a bits 0, 1, 3) the orb
 * bursts the same way. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct { VecFx32 center; int nRadius; } Sphere;
typedef struct { u16 lo : 8; u16 hi : 8; } Hw60;
struct Bits17a { unsigned char b0 : 1, b1 : 1, b2 : 1, b3 : 1; };

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

extern const short data_0203d210[];
extern int Ov107_FindNearestObject(int obj, int kind);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int y, int x);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern int Ov107_CollectSphereOverlaps(int owner, Sphere *sphere, int *hits);
extern int Ov107_InvokeHitCallback(int hit, int owner, int item, int kind, VecFx32 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, VecFx32 at, int flag);
extern void SetIndexedSlot(int *node, int slot, void *cb);

void Ov256_HomingOrbTick(int *node)
{
    int *state = (int *)node[1];
    int n;
    int i;
    u8 seen = 0;
    VecFx32 d;
    VecFx32 aim;
    Sphere sphere;
    int hits[4];
    VecFx32 push;

    state[7] += *(int *)(node[0] + 0x2c);
    state[9] = Ov107_FindNearestObject(*state, 0);
    aim = *(VecFx32 *)(state[9] + 0x190);
    aim.y += 0x1000;
    VEC_Subtract(&aim, (void *)state[2], &d);
    VEC_Normalize(&d, &d);
    state[6] = FX_Atan2(d.x, d.z);
    ScaleVec3Fx12(0x480 - (*(int *)(*(int *)(*state + 0x398) + 0x45c) << 7), &d, &d);
    *(VecFx32 *)(state + 3) = d;
    if (state[5] != 0 && state[4] != 0 && state[3] != 0) {
        if (*((u8 *)state + 0x20) < 2) {
            *((u8 *)state + 0x20) += 1;
        }
    }
    if (*((u8 *)state + 0x20) == 2) {
        ((Hw60 *)(*state + 0x60))->hi &= ~0x80;
    }
    sphere.nRadius = 0x1000;
    sphere.center = *(VecFx32 *)(*state + 0x74);
    n = Ov107_CollectSphereOverlaps(*(int *)(*state + 0x398), &sphere, hits);
    for (i = 0; i < n; i++) {
        u8 bit = 1 << *(u16 *)(hits[i] + 2);

        seen |= bit;
        if ((*((u8 *)state + 0x21) & bit) != 0) {
            continue;
        }
        push.y = 0;
        push.x = data_0203d210[ANG2IDX(state[6]) * 2];
        push.z = data_0203d210[ANG2IDX(state[6]) * 2 + 1];
        ScaleVec3Fx12(0x800, &push, &push);
        if (Ov107_InvokeHitCallback(hits[i], *state, *(int *)(*state + 0x398), 4, &push, 0) == 0) {
            continue;
        }
        *((u8 *)state + 0x21) |= bit;
        func_ov107_020c0b90(*(int *)(*state + 0x398), 4, *(VecFx32 *)state[2], 0);
        *(u8 *)(*state + 0x1c7) = 0;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    *((u8 *)state + 0x21) &= seen;
    if (state[9] != 0 && state[7] < 0x7000 && ((struct Bits17a *)(*state + 0x17a))->b1 == 0
        && ((struct Bits17a *)(*state + 0x17a))->b0 == 0 && ((struct Bits17a *)(*state + 0x17a))->b3 == 0) {
        return;
    }
    func_ov107_020c0b90(*(int *)(*state + 0x398), 4, *(VecFx32 *)state[2], 0);
    *(u8 *)(*state + 0x1c7) = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
