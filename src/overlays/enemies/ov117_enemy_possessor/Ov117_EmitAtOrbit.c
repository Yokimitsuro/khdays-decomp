/* Orbit step: moves the actor around its target on the orbit axis, steering its orientation, and
 * emits the effect on its timer. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    int x;
    int y;
    int z;
    int w;
} Quaternion;

typedef struct {
    int m[9];
} MtxFx33;

typedef struct {
    u16 a;
    u16 b;
} Pair16;

typedef struct {
    u16 lo : 8;
    u16 hi : 8;
} Hw60;

typedef struct TargetActor TargetActor;

struct TargetActor {
    int unknown00;
    int affiliation;
    char padding08[0x1c];
    void (*notify)(int, const Pair16 *, int);
    char padding28[0x38];
    Hw60 status;
    char padding62[0x12];
    VecFx32 localPosition;
    char padding80[0x10c];
    int nestedState;
    VecFx32 worldPosition;
    char padding19c[0x28];
    unsigned char actorFlags;
    char padding1c5[2];
    signed char state;
    char padding1c8[0x1c];
    int passFlags;
    char padding1e8[0x3c];
    int delayLo;
    int delayHi;
};

typedef struct OrbitContext OrbitContext;

struct OrbitContext {
    TargetActor *owner;
    int padding04;
    Quaternion previousOrientation;
    Quaternion orientation;
    int padding28;
    VecFx32 steering;
    int effectTimer;
    int padding3c;
    int orbitDelay;
    VecFx32 *position;
    char padding48[0x18];
    int angle;
    VecFx32 motion;
    int padding70;
    TargetActor *target;
    VecFx32 orbitAxis;
    VecFx32 orbitOffset;
};

typedef struct {
    int *frameState;
    OrbitContext *orbitContext;
    char padding08[0x18];
    signed char actionSlot;
} OrbitTask;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *unit);
extern int RandNextScaled();
extern void SetIndexedSlot(OrbitTask *self, int slot, void *cb);
extern void QuatFromAxisAngle(Quaternion *dst, const VecFx32 *axis, int angle);
extern void Vec3TransformViaTempMtx(VecFx32 *dst, const Quaternion *q, const VecFx32 *v);
extern void ScaleVec3Fx12(int scale, const VecFx32 *src, VecFx32 *dst);
extern void Mtx33_LookAt(MtxFx33 *m, const VecFx32 *a, const VecFx32 *b, const VecFx32 *c);
extern void Quat_FromMtx33(Quaternion *q, const MtxFx33 *m);
extern fx16 FX_Atan2(int x, int z);
extern void Ov107_InvokeHitCallback(int a, int b, int c, int d, const VecFx32 *e, int f);
extern void Ov117_AiFallTick(void);
extern VecFx32 data_020475ac;
extern VecFx32 data_02042264;
extern VecFx32 data_02041dc8;
extern Pair16 data_ov117_020cdc28[];

static inline TargetActor *GetTarget(OrbitContext *ctx) {
    return ctx->target;
}

static inline int RollOrbitDelay(TargetActor *owner) {
    int lo = owner->delayLo;
    int d = owner->delayHi - lo;
    if (d < 0) {
        d = -d;
    }
    return RandNextScaled(d + 1) + lo;
}

static inline void SetVec3(VecFx32 *dst, int x, int y, int z) {
    dst->x = x;
    dst->y = y;
    dst->z = z;
}

static inline int AffiliationsDiffer(int targetAffiliation, int ownerAffiliation) {
    return targetAffiliation != ownerAffiliation;
}

void Ov117_EmitAtOrbit(OrbitTask *self) {
    OrbitContext *ctx = self->orbitContext;
    VecFx32 offset;
    VecFx32 aimPos;
    Quaternion spin;
    MtxFx33 m;
    VecFx32 toTarget;
    Pair16 rec;
    int dist;
    int pi;
    int flags;
    void (*cb)(int, const Pair16 *, int);

    VEC_Subtract(&ctx->target->worldPosition,
                 ctx->position, &toTarget);
    dist = VEC_Normalize(&toTarget, &toTarget);

    if (AffiliationsDiffer(ctx->target->affiliation, ctx->owner->affiliation) ||
        *(u16 *)(ctx->target->nestedState + 0x12) == 0 ||
        (ctx->target->status.lo & 1) == 0 || dist > 0x2c00 ||
        (ctx->owner->actorFlags & 2) != 0) {
        ctx->orbitDelay = RollOrbitDelay(ctx->owner);
        ctx->owner->state = 2;
        SetIndexedSlot(self, self->actionSlot, 0);
        return;
    }

    QuatFromAxisAngle(&spin, &ctx->orbitAxis, ctx->angle);
    ctx->angle += self->frameState[0xb] * 30 / 4;
    pi = 0x3244;
    if (ctx->angle > pi) {
        ctx->angle = ctx->angle - pi * 2;
    }
    Vec3TransformViaTempMtx(&aimPos, &spin, &ctx->orbitOffset);
    VEC_Add(&ctx->target->localPosition,
            &aimPos, &aimPos);
    VEC_Subtract(&aimPos, ctx->position, &offset);
    ScaleVec3Fx12(self->frameState[0xb] * 15, &offset,
                  &ctx->steering);

    Mtx33_LookAt(&m, &data_020475ac, ctx->position, &data_02042264);
    Quat_FromMtx33(&ctx->orientation, &m);

    ctx->effectTimer += self->frameState[0xb];
    if (ctx->effectTimer >= 0x800) {
        ctx->effectTimer = 0;
        Ov107_InvokeHitCallback((int)ctx->target, (int)ctx->owner, (int)ctx->owner,
                            0, &data_02041dc8, 0x10);
    }

    flags = ctx->target->passFlags;
    if ((flags & 3) != 0) {
        Pair16 *rp = &rec;
        rp->b = data_ov117_020cdc28[1].b;
        rp->a = data_ov117_020cdc28[1].a;
        cb = ctx->owner->notify;
        if (cb != 0) {
            cb((int)ctx->owner, rp, 4);
        }
        ctx->owner->status.hi &= ~6;
        SetVec3(&ctx->motion, ctx->steering.x, 0x400, ctx->steering.z);
        QuatFromAxisAngle(&ctx->orientation, &data_02042264,
                      FX_Atan2(ctx->steering.x, ctx->steering.z));
        ctx->previousOrientation = ctx->orientation;
        SetIndexedSlot(self, self->actionSlot, Ov117_AiFallTick);
        return;
    }
    if ((flags & 4) != 0) {
        ctx->owner->state = 2;
        SetIndexedSlot(self, self->actionSlot, 0);
    }
}
