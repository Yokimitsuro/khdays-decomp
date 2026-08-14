typedef unsigned short u16;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

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
extern int func_01ff8d18(const VecFx32 *v, VecFx32 *unit);
extern int func_02023eb4();
extern void func_0203c634(OrbitTask *self, int slot, void *cb);
extern void func_0202f188(Quaternion *dst, const VecFx32 *axis, int angle);
extern void func_0202f384(VecFx32 *dst, const Quaternion *q, const VecFx32 *v);
extern void func_01ffa724(int scale, const VecFx32 *src, VecFx32 *dst);
extern void func_0203cd7c(MtxFx33 *m, const VecFx32 *a, const VecFx32 *b, const VecFx32 *c);
extern void func_0202ea48(Quaternion *q, const MtxFx33 *m);
extern int func_020050b4(int x, int z);
extern void func_ov107_020ca918(int a, int b, int c, int d, const VecFx32 *e, int f);
extern void func_ov186_020d32e0(void);
extern VecFx32 data_020475ac;
extern VecFx32 data_02042264;
extern VecFx32 data_02041dc8;
extern Pair16 data_ov186_020d34c0[];

static inline TargetActor *GetTarget(OrbitContext *ctx) {
    return ctx->target;
}

static inline int RollOrbitDelay(TargetActor *owner) {
    int lo = owner->delayLo;
    int d = owner->delayHi - lo;
    if (d < 0) {
        d = -d;
    }
    return func_02023eb4(d + 1) + lo;
}

static inline void SetVec3(VecFx32 *dst, int x, int y, int z) {
    dst->x = x;
    dst->y = y;
    dst->z = z;
}

static inline int AffiliationsDiffer(int targetAffiliation, int ownerAffiliation) {
    return targetAffiliation != ownerAffiliation;
}

/*
 * Per-frame step of the orbit action.
 *
 * It gives up straight away, rolling a fresh orbit delay and handing the actor
 * back to state 2, when the target is on the same side, has no nested state, is
 * not enabled, sits further than 0x2c00 away, or the owner carries flag 2.
 *
 * Otherwise it advances the orbit angle by the frame delta, wrapping at half a
 * turn, rotates the stored offset about the stored axis to get the point on the
 * orbit, and steers towards it.  The orientation is rebuilt from the look-at
 * matrix each frame, and every 0x800 of accumulated time it fires one contact
 * hit.  The target's pass flags then choose the exit: bits 0 or 1 notify the
 * owner with the second record of the overlay table, clear two status bits,
 * launch the actor along the steering direction with a fixed rise and hand over
 * to the follow-up action, while bit 2 just returns the actor to state 2.
 *
 * This is the same function as ov118's 020d13cc and ov117's 020cd78c down to the
 * instruction: the three overlays share the orbit action and differ only in the
 * overlay table they notify from and the follow-up action they hand over to.
 * The source is that twin with those two symbols substituted, and the local type
 * names are kept as the twin has them so the shared shape stays visible.
 */
void func_ov186_020d3014(OrbitTask *self) {
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
    dist = func_01ff8d18(&toTarget, &toTarget);

    if (AffiliationsDiffer(ctx->target->affiliation, ctx->owner->affiliation) ||
        *(u16 *)(ctx->target->nestedState + 0x12) == 0 ||
        (ctx->target->status.lo & 1) == 0 || dist > 0x2c00 ||
        (ctx->owner->actorFlags & 2) != 0) {
        ctx->orbitDelay = RollOrbitDelay(ctx->owner);
        ctx->owner->state = 2;
        func_0203c634(self, self->actionSlot, 0);
        return;
    }

    func_0202f188(&spin, &ctx->orbitAxis, ctx->angle);
    ctx->angle += self->frameState[0xb] * 30 / 4;
    pi = 0x3244;
    if (ctx->angle > pi) {
        ctx->angle = ctx->angle - pi * 2;
    }
    func_0202f384(&aimPos, &spin, &ctx->orbitOffset);
    VEC_Add(&ctx->target->localPosition,
            &aimPos, &aimPos);
    VEC_Subtract(&aimPos, ctx->position, &offset);
    func_01ffa724(self->frameState[0xb] * 15, &offset,
                  &ctx->steering);

    func_0203cd7c(&m, &data_020475ac, ctx->position, &data_02042264);
    func_0202ea48(&ctx->orientation, &m);

    ctx->effectTimer += self->frameState[0xb];
    if (ctx->effectTimer >= 0x800) {
        ctx->effectTimer = 0;
        func_ov107_020ca918((int)ctx->target, (int)ctx->owner, (int)ctx->owner,
                            0, &data_02041dc8, 0x10);
    }

    flags = ctx->target->passFlags;
    if ((flags & 3) != 0) {
        Pair16 *rp = &rec;
        rp->b = data_ov186_020d34c0[1].b;
        rp->a = data_ov186_020d34c0[1].a;
        cb = ctx->owner->notify;
        if (cb != 0) {
            cb((int)ctx->owner, rp, 4);
        }
        ctx->owner->status.hi &= ~6;
        SetVec3(&ctx->motion, ctx->steering.x, 0x400, ctx->steering.z);
        func_0202f188(&ctx->orientation, &data_02042264,
                      func_020050b4(ctx->steering.x, ctx->steering.z));
        ctx->previousOrientation = ctx->orientation;
        func_0203c634(self, self->actionSlot, func_ov186_020d32e0);
        return;
    }
    if ((flags & 4) != 0) {
        ctx->owner->state = 2;
        func_0203c634(self, self->actionSlot, 0);
    }
}

