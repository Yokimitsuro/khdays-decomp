/*
 * Homing flight tick of the ov153 projectile state (x3: ov153/154/155). The actors inside the
 * owner's +0x74 sphere are pushed away along the flattened direction from the owner at 0x800
 * through the ov107 hit hook (kind 0); the first that takes it gets a kind-5 position message
 * with the +4 position delivered to the owner's +0x24 handler, sub-state 0, reaction 0x13c/5 and
 * the slot released. Then, while the owner's +0x17a bit 0 is set and a target is acquirable, a
 * target ahead of the flight direction (flattened offset . flattened +0x14 direction > 0.5)
 * re-aims the direction: the heading of the summed vectors plus a random +-0x860 turn becomes
 * a sine/cosine pair in +0x14/+0x1c. The +8/+0x10 step is the direction scaled by the +0x20
 * speed; without bit 0 the +0xc height drops by 30 x dt / 16, with it the height decays
 * (x -0xd00 / 4096) and the speed eases towards 16 by a fortieth. Bit 1 of the flags, or the
 * +0x24 distance passing 0x14000 after growing by the step length, ends the flight (message,
 * reaction 0x13c/6, sub-state 0, slot released).
 *
 * Codegen notes: the sender's volatile ints keep the packed position on the stack (three
 * triples after the aggregates); `const` on the sine table lets both table loads precede the
 * direction stores; `angle += r` (not `angle = angle + r`) puts the atan2 result first in the
 * add; the SDK macros are spelled literally (FX_RAD_TO_IDX with `>> 44`, FX_SinIdx/CosIdx as
 * table[(idx >> 4) << 1] and +1).
 */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/actor.h"
#include "game/engine.h"

typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

struct Flags17a {
    u8 bit0 : 1;
    u8 bit1 : 1;
};

struct Ov153Actor {
    Actor base;                  /* 0x000 */
    char *pItem38c;
};

struct Ov153FlightState {
    struct Ov153Actor *pOwner;
    VecFx32 *pPos;
    int nStepX;
    int nHeight;
    int nStepZ;
    int nDirX;
    int nDirY;
    int nDirZ;
    int nSpeed;
    int nDist;
};

extern int Ov107_CollectSphereOverlaps(char *item, VecFx32 *sphere, struct Ov153Actor **out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern int Ov107_InvokeHitCallback(struct Ov153Actor *hit, struct Ov153Actor *a, char *item, int kind, const VecFx32 *push, int z);
extern void Ov107_BuildAndSendUpdate(struct Ov153Actor *owner, u16 a, u16 id, VecFx32 *pos);
extern void SetIndexedSlot(int node, int slot, void *cb);
extern struct Ov153Actor *Ov107_FindNearestObject(struct Ov153Actor *owner, int mode);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_Mag(const VecFx32 *v);
extern const short data_0203d210[];
extern const PosMsg data_ov155_020d58a8;
extern const PosMsg data_ov155_020d58b6;
extern const PosMsg data_ov155_020d58d2;

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov153FlightState *state, PosMsg *msg, const VecFx32 *src)
{
    volatile int px;
    volatile int py;
    volatile int pz;
    int x;
    x = src->x;
    PackFx24(&msg->pos[0], x);
    px = x;
    x = src->y;
    PackFx24(&msg->pos[1], x);
    py = x;
    x = src->z;
    PackFx24(&msg->pos[2], x);
    pz = x;
    if (state->pOwner->base.pfnPostMessage != 0) {
        ((void (*)(struct Ov153Actor *, PosMsg *, int))state->pOwner->base.pfnPostMessage)(state->pOwner, msg, 0xe);
    }
}

void Ov155_HomingFlightTick(int node)
{
    struct Ov153Actor *actor;
    struct Ov153FlightState *state = *(struct Ov153FlightState **)(node + 4);
    struct Ov153Actor *hits[4];
    VecFx32 push;
    PosMsg msgA;
    VecFx32 d;
    VecFx32 dir;
    VecFx32 sum;
    PosMsg msgB;
    PosMsg msgC;
    struct Ov153Actor *target;
    int angle;
    int r;
    int idx;
    int i;
    int n;

    actor = state->pOwner;
    n = Ov107_CollectSphereOverlaps(actor->pItem38c, &actor->base.sphere.center, hits);
    for (i = 0; i < n; i++) {
        VEC_Subtract(&hits[i]->base.sphere.center, &actor->base.sphere.center, &push);
        push.y = 0;
        VEC_Normalize(&push, &push);
        ScaleVec3Fx12(0x800, &push, &push);
        if (Ov107_InvokeHitCallback(hits[i], state->pOwner, state->pOwner->pItem38c, 0, &push, 0) != 0) {
            msgA = data_ov155_020d58b6;
            SendPos(state, &msgA, state->pPos);
            state->pOwner->base.nextState = 0;
            Ov107_BuildAndSendUpdate(state->pOwner, 0x13c, 5, state->pPos);
            SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
            return;
        }
    }
    if (state->pOwner->base.contact17a.bits.bit0) {
        target = Ov107_FindNearestObject(state->pOwner, 0);
        if (target != 0) {
            VEC_Subtract(&target->base.sphere.center, &actor->base.sphere.center, &d);
            d.y = 0;
            dir = *(VecFx32 *)&state->nDirX;
            dir.y = 0;
            VEC_Normalize(&d, &d);
            VEC_Normalize(&dir, &dir);
            if (VEC_DotProduct(&d, &dir) > 0x800) {
                VEC_Add(&d, &dir, &sum);
                r = RandNextScaled(0x10c1) - 0x860;
                angle = FX_Atan2(sum.x, sum.z);
                angle += r;
                idx = (unsigned short)((0x28BE60DB9391LL * angle + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
                state->nDirX = data_0203d210[(idx >> 4) << 1];                               /* FX_SinIdx */
                state->nDirZ = data_0203d210[((idx >> 4) << 1) + 1];                         /* FX_CosIdx */
            }
        }
    }
    state->nStepX = (int)(((long long)state->nDirX * state->nSpeed + 0x800) >> 12);
    state->nStepZ = (int)(((long long)state->nDirZ * state->nSpeed + 0x800) >> 12);
    if (!state->pOwner->base.contact17a.bits.bit0) {
        state->nHeight -= (int)(((long long)(*(int *)(*(int *)node + 0x2c) * 30) * 0x100 + 0x800) >> 12);
    } else {
        state->nHeight = -(int)(((long long)state->nHeight * 0xd00 + 0x800) >> 12);
        state->nSpeed += (0x10 - state->nSpeed) / 40;
    }
    if (state->pOwner->base.contact17a.bits.bit1) {
        msgB = data_ov155_020d58a8;
        SendPos(state, &msgB, state->pPos);
        Ov107_BuildAndSendUpdate(state->pOwner, 0x13c, 6, state->pPos);
        state->pOwner->base.nextState = 0;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    state->nDist += VEC_Mag((VecFx32 *)&state->nStepX);
    if (state->nDist <= 0x14000) {
        return;
    }
    msgC = data_ov155_020d58d2;
    SendPos(state, &msgC, state->pPos);
    Ov107_BuildAndSendUpdate(state->pOwner, 0x13c, 6, state->pPos);
    state->pOwner->base.nextState = 0;
    SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
}
