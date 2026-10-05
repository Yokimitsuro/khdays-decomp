/* Spin tick of the ov253 enemy: the +0x14 speed is six times the frame rate; a target (020cab14) is
 * kept in +0x24 and faced (+0x10 heading from the +8 point). Between 0.17 and 1.13 of the +0x1c clock
 * both +0x3a0 capsules sweep a 2.0 sphere around their +0x14 point: each entity the body accepts
 * (020cceb0) is pushed 0.5 away on the plane and, when the kind-0 hit lands, gets the overlay's
 * data_ov253_020d4900 message with its packed position (through the owner's +0x24 message hook) and
 * reaction 0 mode 0x4e at it. Past 0.73 reaction 0x16b mode 4 fires once (+0x38) at the +0x398 bone.
 * Once the +4 rig is idle, +0x30 rerolls within the owner's +0x224..+0x228 range and move 2 follows. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { VecFx32 pos; int radius; } Sphere;
typedef struct { int value; } Fx32;
struct Msg14 { u16 h[7]; };
struct HitPacket40 {
    int nKind;
    VecFx32 vNormal;
    int nPower;
    int w[5];
};
struct Ov253Actor {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov253Actor *self, void *msg, int size);
};
struct Capsules { char pad[0x3a0]; int handles[3]; };

extern int Ov107_FindNearestObject(int actor, int mode);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern int Ov107_CollectSphereOverlaps(int actor, Sphere *sphere, int *out);
extern int Ov253_IdIsFree(int item, int hit);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *d);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern int Ov107_InvokeHitCallback(int hit, int a, int b, int kind, VecFx32 *push, int z);
extern void Ov107_BuildAndSendUpdate(int owner, int a, int id, void *at);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const struct Msg14 data_ov253_020d4900;

#define PACK3(msg, base, v) \
    ((u8 *)(msg))[(base)] = (u8)(((u32)(v) >> 0x10 & 0x7f) | ((u32)(v) >> 0x18 & 0x80)); \
    ((u8 *)(msg))[(base) + 1] = (u8)((u32)(v) >> 8); \
    ((u8 *)(msg))[(base) + 2] = (u8)(v)

static inline void PackPos(struct Msg14 *msg, const VecFx32 *src)
{
    Fx32 px;
    Fx32 py;
    Fx32 pz;
    px = *(Fx32 *)&src->x;
    PACK3(msg, 5, px.value);
    py = *(Fx32 *)&src->y;
    PACK3(msg, 8, py.value);
    pz = *(Fx32 *)&src->z;
    PACK3(msg, 11, pz.value);
}

void Ov253_TickSpin(int *node)
{
    int *state;
    int hits[4];
    VecFx32 diff;
    Sphere sphere;
    int j;
    long i;
    long n;
    int owner;
    int lo;
    int spread;

    state = (int *)node[1];
    state[5] = *(int *)(node[0] + 0x2c) * 0x1e / 5;
    state[9] = Ov107_FindNearestObject(*state, 0);
    if (state[9] != 0) {
        VEC_Subtract((void *)(state[9] + 0x190), (void *)state[2], &diff);
        state[4] = FX_Atan2(diff.x, diff.z);
    }
    state[7] += *(int *)(node[0] + 0x2c);
    if (state[7] >= 0x2aa && state[7] <= 0x1210) {
        for (j = 0; j < 2; j++) {
            sphere.pos = *(VecFx32 *)(((struct Capsules *)*state)->handles[j] + 0x14);
            sphere.radius = 0x2000;
            n = Ov107_CollectSphereOverlaps(*state, &sphere, hits);
            for (i = 0; i < n; i++) {
                struct HitPacket40 packet = {0};
                VecFx32 d;
                VecFx32 push;
                struct Msg14 msg;

                owner = *state;
                if (Ov253_IdIsFree(owner, hits[i]) != 0) {
                    VEC_Subtract((void *)(hits[i] + 0x74), &sphere.pos, &d);
                    VEC_Normalize(&d, &d);
                    ScaleVec3Fx12(0x800, &d, &push);
                    packet.vNormal = push;
                    packet.nPower = *(u16 *)(owner + 0x290);
                    packet.nKind = 0;
                    if (Ov107_InvokeHitCallback(hits[i], *state, *state, 0, &push, 0) != 0) {
                        msg = data_ov253_020d4900;
                        PackPos(&msg, (VecFx32 *)(hits[i] + 0x74));
                        if (((struct Ov253Actor *)*state)->pfnMessage != 0) {
                            ((struct Ov253Actor *)*state)->pfnMessage((struct Ov253Actor *)*state, &msg, 0xe);
                        }
                        Ov107_BuildAndSendUpdate(*state, 0, 0x4e, (void *)(hits[i] + 0x74));
                    }
                }
            }
        }
    }
    if (*((u8 *)state + 0x38) == 0 && state[7] >= 0xbbb) {
        Ov107_BuildAndSendUpdate(*state, 0x16b, 4, (void *)(*(int *)(*state + 0x398) + 0x14));
        *((u8 *)state + 0x38) = 1;
    }
    if (*(u8 *)state[1] != 0) {
        return;
    }
    lo = *(int *)(*state + 0x224);
    spread = *(int *)(*state + 0x228) - lo;
    if (spread < 0) {
        spread = -spread;
    }
    state[0xc] = lo + RandNextScaled(spread + 1);
    *(signed char *)(*state + 0x1c7) = 2;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
