/* Charge tick (variant 1) of the ov204 enemy (and its byte-identical twin): the +8 velocity is
 * the +0x390 part's motion step rotated by the actor's +0xa0 orientation, the charge sweep runs,
 * the target is re-acquired (the +0x38 yaw aimed at it from the +0x24 position), the +0x3c turn
 * rate is the step over 0x3000 capped at 0x200 and the +0x2c travel grows by the step. Once the
 * +0x28 busy byte clears: at the start of the +0x58 phase the +0x20 point is packed into the
 * overlay's 14-byte template for the actor's +0x24 message hook and reaction 0x132 mode 5 fires
 * there; the phase accumulates the frame-time and drives the ground sweep (phase over 0x600 as a
 * 64-bit fraction); past 0x800 the +0x390 part runs action 6, animation 0xf plays, the +0x44
 * mask and the phase reset and the tick hands off to the second variant. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

struct Ov204Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov204Owner *self, PosMsg *msg, int size);
};

struct Ov204ChargeState {
    struct Ov204Owner *pOwner;  /* +0x00 */
    int pTarget;                /* +0x04 */
    VecFx32 vVelocity;             /* +0x08 */
    char pad014[0xc];
    VecFx32 *pPoint;               /* +0x20 */
    VecFx32 *pPos;                 /* +0x24 */
    u8 *pBusy;                  /* +0x28 */
    int nTravel;                /* +0x2c */
    char pad030[8];
    int nTargetYaw;             /* +0x38 */
    int nTurnRate;              /* +0x3c */
    char pad040[4];
    u8 bHitMask44;              /* +0x44 */
    char pad045[0x13];
    int nPhase;                 /* +0x58 */
};

extern int Ov107_ActionResource_GetOffsetAndScale(void *part, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern void Ov205_ChargeSweep(struct Ov204ChargeState *state);
extern int Ov107_FindNearestObject(struct Ov204Owner *actor, int mode);
extern void VEC_Subtract(void *a, void *b, VecFx32 *d);
extern fx16 FX_Atan2(int x, int z);
extern int FX_Div(int a, int b);
extern void Ov107_BuildAndSendUpdate(struct Ov204Owner *owner, int a, int id, VecFx32 *at);
extern s64 FX_DivFx64c(int num, int den);
extern void Ov205_GroundSweep(struct Ov204ChargeState *state, s64 t, VecFx32 *at);
extern void Ov107_StartAnim(void *part, int a, int b);
extern void Ov107_PostTagUpdate(struct Ov204Owner *actor, int anim, int flag);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const PosMsg data_ov205_020d725a;
extern void Ov205_ChargeTick2(int *node);

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov204ChargeState *state, PosMsg *msg, const VecFx32 *src)
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
    if (state->pOwner->pfnMessage != 0) {
        state->pOwner->pfnMessage(state->pOwner, msg, 0xe);
    }
}

void Ov205_ChargeTick1(int *node)
{
    struct Ov204ChargeState *state = (struct Ov204ChargeState *)node[1];
    VecFx32 step;
    VecFx32 dir;
    PosMsg msg;
    int speed;
    int rate;

    speed = Ov107_ActionResource_GetOffsetAndScale(*(void **)((char *)state->pOwner + 0x390), &step);
    Vec3TransformViaTempMtx(&state->vVelocity, (char *)state->pOwner + 0xa0, &step);
    ScaleVec3Fx12(speed, &state->vVelocity, &state->vVelocity);
    Ov205_ChargeSweep(state);
    state->pTarget = Ov107_FindNearestObject(state->pOwner, 0);
    if (state->pTarget != 0) {
        VEC_Subtract((void *)(state->pTarget + 0x74), state->pPos, &dir);
        state->nTargetYaw = FX_Atan2(dir.x, dir.z);
    }
    rate = FX_Div(speed, 0x3000);
    if (rate > 0x200) {
        rate = 0x200;
    }
    state->nTurnRate = rate;
    state->nTravel += speed;
    if (*state->pBusy != 0) {
        return;
    }
    if (state->nPhase == 0) {
        msg = data_ov205_020d725a;
        SendPos(state, &msg, state->pPoint);
        Ov107_BuildAndSendUpdate(state->pOwner, 0x132, 5, state->pPoint);
    }
    state->nPhase += *(int *)(*node + 0x2c);
    Ov205_GroundSweep(state, FX_DivFx64c(state->nPhase, 0x600), state->pPoint);
    if (state->nPhase < 0x800) {
        return;
    }
    Ov107_StartAnim(*(void **)((char *)state->pOwner + 0x390), 6, 0);
    Ov107_PostTagUpdate(state->pOwner, 0xf, 0);
    state->bHitMask44 = 0;
    state->nPhase = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov205_ChargeTick2);
}
