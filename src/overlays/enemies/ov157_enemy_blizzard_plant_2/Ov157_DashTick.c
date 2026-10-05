/* Dash tick of the ov156 enemy (and its byte-identical twin). The actors inside the owner's
 * +0x74 sphere are pushed away along the flattened direction from the owner at 0x800 through the
 * ov107 hit hook (kind 0); the first that takes it gets a kind-5 position message with the +8
 * position delivered to the owner's +0x24 handler, reaction 0x13d/5, sub-state 0 and the slot
 * released. Then a target ahead of the +0x18 direction turns it towards the target by
 * 30 x dt / 15 (d040) as a sine/cosine pair. With bit 0 of the +0x24 flags the actor found at
 * the owner's position (c9094) that is not +0x1ac-4 gets a 0x2004 hit packet (zero normal, the
 * +0x38c item's +0x290/+0x19c ids) through the owner's +0x25c source when its shape's +8 bit 0
 * is set; acceptance sends the message, fires reaction 0/0x53, sub-state 0 and releases the
 * slot. The +0x2c bounce timer counts down; once spent, a wall contact (bit 1 of +0x17a, or a
 * sphere cast of the direction at 0x500 hitting a +8-clear surface whose +4 record gives the
 * normal) reflects the direction about the contact normal, re-arms the timer at 0x100 and fires
 * reaction 0x13d/6. The +0xc/+0x14 step is the direction at 0x500 and the +0x10 height drops
 * 0x40 per tick unless bit 0 of +0x17a is set (then it is 0); the +0x28 distance grows by the
 * step length and past 0x14e00 the dash ends (message, reaction 0x13d/6, sub-state 0, slot
 * released).
 *
 * Codegen notes as in ov153_cccf8: volatile ints in the sender keep the packed position on the
 * stack, `const` on the sine table lets both table loads precede the direction stores, and the
 * hit packet is zeroed as a whole before its fields are filled. */

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

struct w8 { unsigned int lo : 8, rest : 24; };

struct Flags24 {
    u8 bit0 : 1;
};

struct HitPacket {
    u32 flagsLo : 16;
    u32 flagsHi : 16;
    VecFx32 normal;
    int field_10 : 16;
    int field_12 : 16;
    int field_14 : 16;
    int field_16 : 16;
    void *field_18;
    signed char field_1c;
    u8 pad01d[3];
    int field_20;
    u32 flags24Lo : 16;
    u32 flags24Hi : 16;
    int field_28;
};

struct CollisionRecord {
    char pad000[0x14];
    short nx;
    short ny;
    short nz;
};

struct CollisionResult {
    int field_00;
    struct CollisionRecord *pRecord;
    int field_08;
};

struct Ov156Item {
    char pad000[0x19c];
    u8 nId19c;
    char pad19d[0x290 - 0x19d];
    u16 nId290;
};

struct Ov156Actor {
    Actor base;                  /* 0x000 */
    struct Ov156Item *pItem38c;
};

struct Ov156DashState {
    struct Ov156Actor *pOwner;
    int pTarget;
    VecFx32 *pPos;
    VecFx32 vStep;
    int nDirX;
    int nDirY;
    int nDirZ;
    struct Flags24 flags24;
    char pad025[3];
    int nDist;
    int nBounceTimer;
};

extern int Ov107_CollectSphereOverlaps(struct Ov156Item *item, VecFx32 *sphere, struct Ov156Actor **out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern int Ov107_InvokeHitCallback(struct Ov156Actor *hit, struct Ov156Actor *a, struct Ov156Item *item, int kind, const VecFx32 *push, int z);
extern void Ov107_BuildAndSendUpdate(struct Ov156Actor *owner, u16 a, u16 id, VecFx32 *pos);
extern void SetIndexedSlot(int node, int slot, void *cb);
extern struct Ov156Actor *Ov107_FindNearestObject(struct Ov156Actor *owner, int mode);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx16 FX_Atan2(int x, int z);
extern char *Ov107_FindEntityHitBySphere(struct Ov156Actor *owner, VecFx32 *pos, int *shape);
extern int Ov107_AiState_ApplyHit(char *other, int source, struct HitPacket *packet);
extern struct CollisionResult *Collision_CastSphereEx(void *collision, VecFx32 *position, VecFx32 *direction, int radius, void *ignore);
extern int VEC_Mag(const VecFx32 *v);
extern const short data_0203d210[];
extern const VecFx32 data_02041dc8;
extern const PosMsg data_ov157_020d0bcc;
extern const PosMsg data_ov157_020d0bda;
extern const PosMsg data_ov157_020d0be8;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov156DashState *state, PosMsg *msg, const VecFx32 *src)
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
        ((void (*)(struct Ov156Actor *, PosMsg *, int))state->pOwner->base.pfnPostMessage)(state->pOwner, msg, 0xe);
    }
}

void Ov157_DashTick(int node)
{
    struct Ov156Actor *actor;
    struct Ov156DashState *state = *(struct Ov156DashState **)(node + 4);
    struct Ov156Actor *hits[4];
    VecFx32 push;
    PosMsg msgA;
    VecFx32 d;
    int shape;
    struct Ov156Actor *target;
    struct CollisionResult *result;
    char *other;
    int cur;
    int want;
    int angle;
    unsigned int idx;
    int hit;
    int i;
    int nHits;

    actor = state->pOwner;
    nHits = Ov107_CollectSphereOverlaps(actor->pItem38c, &actor->base.sphere.center, hits);
    for (i = 0; i < nHits; i++) {
        VEC_Subtract(&hits[i]->base.sphere.center, &actor->base.sphere.center, &push);
        push.y = 0;
        VEC_Normalize(&push, &push);
        ScaleVec3Fx12(0x800, &push, &push);
        if (Ov107_InvokeHitCallback(hits[i], state->pOwner, state->pOwner->pItem38c, 0, &push, 0) != 0) {
            msgA = data_ov157_020d0bda;
            SendPos(state, &msgA, state->pPos);
            Ov107_BuildAndSendUpdate(state->pOwner, 0x13d, 5, state->pPos);
            state->pOwner->base.nextState = 0;
            SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
            return;
        }
    }
    target = Ov107_FindNearestObject(state->pOwner, 0);
    if (target != 0) {
        VEC_Subtract(&target->base.sphere.center, &actor->base.sphere.center, &d);
        if (VEC_DotProduct(&d, (VecFx32 *)&state->nDirX) > 0) {
            cur = FX_Atan2(state->nDirX, state->nDirZ);
            want = FX_Atan2(d.x, d.z);
            angle = Angle_TurnToward(cur, want, *(int *)(*(int *)node + 0x2c) * 30 / 15, 0);
            idx = ANG2IDX(angle);
            state->nDirX = data_0203d210[idx * 2];                                       /* FX_SinIdx */
            state->nDirZ = data_0203d210[idx * 2 + 1];                                   /* FX_CosIdx */
        }
    }
    if (state->flags24.bit0) {
        other = Ov107_FindEntityHitBySphere(state->pOwner, &actor->base.sphere.center, &shape);
        if (other != 0 && (*(u16 *)(other + 0x1ac) & 4) == 0) {
            struct HitPacket packet = {0};
            PosMsg msgB;
            packet.flagsLo = 0x2004;
            packet.normal = data_02041dc8;
            packet.field_10 = state->pOwner->pItem38c->nId290;
            packet.field_16 = state->pOwner->pItem38c->nId19c;
            packet.field_18 = (void *)shape;
            if ((((struct w8 *)(shape + 8))->lo & 1) != 0 &&
                Ov107_AiState_ApplyHit(other, ((int)state->pOwner->base.field_25c), &packet) != 0) {
                msgB = data_ov157_020d0bcc;
                SendPos(state, &msgB, state->pPos);
                Ov107_BuildAndSendUpdate(state->pOwner, 0, 0x53, state->pPos);
                state->pOwner->base.nextState = 0;
                SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
                return;
            }
        }
    }
    if (state->nBounceTimer > 0) {
        state->nBounceTimer -= *(int *)(*(int *)node + 0x2c);
    }
    if (state->nBounceTimer <= 0) {
        VecFx32 n;
        VecFx32 back;
        VecFx32 refl;
        n = state->pOwner->base.vContactNormal;
        hit = state->pOwner->base.contact17a.bits.bit1;
        if (hit == 0 && state->pOwner->base.field_17b == 0) {
            char *scene = state->pOwner->base.pScene;
            ScaleVec3Fx12(0x500, (VecFx32 *)&state->nDirX, &back);
            result = Collision_CastSphereEx(*(void **)(scene + 0x7c), &state->pOwner->base.sphere.center, &back, state->pOwner->base.sphere.radius, 0);
            if (result != 0 && result->field_08 == 0) {
                hit = 1;
                n.x = result->pRecord->nx;
                n.y = result->pRecord->ny;
                n.z = result->pRecord->nz;
            }
        }
        if (hit != 0) {
            ScaleVec3Fx12(-0x1000, (VecFx32 *)&state->nDirX, &back);
            ScaleVec3Fx12(VEC_DotProduct(&back, &n) << 1, &n, &refl);
            VEC_Subtract(&refl, &back, &refl);
            VEC_Normalize(&refl, (VecFx32 *)&state->nDirX);
            state->nBounceTimer = 0x100;
            Ov107_BuildAndSendUpdate(state->pOwner, 0x13d, 6, state->pPos);
        }
    }
    state->vStep.x = (int)(((long long)state->nDirX * 0x500 + 0x800) >> 12);
    if (state->pOwner->base.contact17a.bits.bit0) {
        state->vStep.y = 0;
    } else {
        state->vStep.y -= 0x40;
    }
    state->vStep.z = (int)(((long long)state->nDirZ * 0x500 + 0x800) >> 12);
    state->nDist += VEC_Mag(&state->vStep);
    if (state->nDist <= 0x14e00) {
        return;
    }
    {
        PosMsg msgC;
        msgC = data_ov157_020d0be8;
        SendPos(state, &msgC, state->pPos);
        Ov107_BuildAndSendUpdate(state->pOwner, 0x13d, 6, state->pPos);
        state->pOwner->base.nextState = 0;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
    }
}
