typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

struct VecFx32 { int x, y, z; };
struct MtxFx33 { int m[3][3]; };
struct Ov214Params;

struct Ov214Actor {
    char pad000[0x2c];
    int nFrameDelta2c;
    char pad030[0x44];
    struct VecFx32 vPosition74;
    int nRadius80;
    char pad084[0x2c];
    struct VecFx32 vCenterb0;
    char pad0bc[0x58];
    struct VecFx32 vContactNormal114;
    char pad120[0x5a];
    u8 bCollisionFlags17a;
    u8 bCollisionState17b;
};

struct Ov214State {
    struct Ov214Actor *pActor;
    int nUnknown04;
    struct Ov214Actor *pTarget;
    int nUnknown0c;
    struct VecFx32 *pOffset10;
    struct VecFx32 vDirection14;
    struct VecFx32 vVelocity20;
    char pad02c[0x24];
    int nCallback50;
    int nUnknown54;
    int nTurnAngle58;
    int nTimer5c;
    int nDelay60;
    int nSpeed64;
    int nVertical68;
    u16 nMode6c;
    u8 nPhase6e;
    u8 nPhaseMax6f;
    u8 bEffect70;
    u8 bHandled71;
    u8 pad072;
    u8 bLatch73;
    u8 bCollision74;
    char pad075[3];
    int bHoming78;
};

struct Ov214Task {
    struct Ov214Actor *pActor;
    struct Ov214State *pState;
    char pad008[0x18];
    signed char nSlot20;
};

struct Ov214CollisionShape {
    char pad000[0x14];
    s16 nX14;
    s16 nY16;
    s16 nZ18;
};

struct Ov214CollisionResult {
    char pad000[4];
    struct Ov214CollisionShape *pShape04;
    int nType08;
};

struct Ov214CollisionFlags {
    unsigned char bGrounded : 1;
};

extern void func_ov107_020c9264(struct Ov214Actor *actor, int mode, int zero);
extern void func_ov107_020c0b90(struct Ov214Actor *actor, int mode, struct VecFx32 value, int zero);
extern struct Ov214CollisionResult *func_01fff8e8(void *collision, struct VecFx32 *origin,
                                                 struct VecFx32 *direction, int radius, int zero);
extern int func_01ff8d18(struct VecFx32 *source, struct VecFx32 *destination);
extern void func_01ffa724(int scale, struct VecFx32 *source, struct VecFx32 *destination);
extern void VEC_Add(struct VecFx32 *a, struct VecFx32 *b, struct VecFx32 *out);
extern void VEC_Subtract(struct VecFx32 *a, struct VecFx32 *b, struct VecFx32 *out);
extern int VEC_DotProduct(struct VecFx32 *a, struct VecFx32 *b);
extern int func_020050b4(int x, int z);
extern int func_ov107_020cab14(struct Ov214Actor *actor, int kind);
extern int FX_Inv(int numerator, int denominator);
extern void MTX_RotY33_(struct MtxFx33 *matrix, int sine, int cosine);
extern void MTX_MultVec33(struct VecFx32 *vector, struct MtxFx33 *matrix, struct VecFx32 *out);
extern int func_02020400(int a, int b);
extern void func_0203c634(struct Ov214Task *task, int slot, void *callback);
extern void func_ov214_020cce44(struct Ov214State *state, unsigned int kind,
                                struct Ov214Params *params);
extern void func_ov214_020ce5ec(void);

extern const struct VecFx32 data_02041dc8;
extern const struct VecFx32 data_02042258;
extern const s16 data_0203d210[];

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))
#define ANGLE_TO_INDEX(angle) \
    ((int)(((unsigned)(((long long)(int)(unsigned)(angle) * 0x28be60db9391LL + \
           0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4)

void func_ov214_020cdf68(struct Ov214Task *task)
{
    struct Ov214State *state = task->pState;
    struct VecFx32 normal = state->pActor->vContactNormal114;
    struct VecFx32 velocity;
    struct VecFx32 reflected;
    struct VecFx32 delta;
    struct VecFx32 delta2;
    struct MtxFx33 matrix;
    struct VecFx32 rotated;
    struct Ov214CollisionResult *hit;
    int collision;
    int targetAngle;
    int index;
    int wasPositive;
    int step;
    int inverse;
    register int gravityStep;
    int phaseCount;

    collision = ((unsigned)state->pActor->bCollisionFlags17a << 30) >> 31;
    if (state->bCollision74 == 0) {
        state->bLatch73 = 0;
    }
    state->bCollision74 = 0;

    if (state->nPhase6e >= state->nPhaseMax6f) {
        func_ov107_020c9264(state->pActor, 8, 0);
        func_ov107_020c0b90(state->pActor, 6, data_02041dc8, 0);
        state->nCallback50 = 0;
        state->bEffect70 = 0;
        func_0203c634(task, task->nSlot20, func_ov214_020ce5ec);
        return;
    }

    if (collision == 0 && state->pActor->bCollisionState17b == 0) {
        hit = func_01fff8e8(*(void **)(*(char **)((char *)state->pActor + 4) + 0x7c),
                            &state->pActor->vPosition74, (struct VecFx32 *)((char *)state + 0x2c),
                            state->pActor->nRadius80, 0);
        if (hit != 0 && hit->nType08 == 0) {
            collision = 1;
            normal.x = hit->pShape04->nX14;
            normal.y = hit->pShape04->nY16;
            normal.z = hit->pShape04->nZ18;
        }
    }

    if (collision != 0) {
        normal.y = 0;
        if (func_01ff8d18(&normal, &normal) == 0) {
            normal = data_02042258;
        }
        func_01ffa724(state->pActor->nRadius80, &state->vDirection14, &velocity);
        VEC_Add(&velocity, state->pOffset10, &velocity);
        func_ov107_020c0b90(state->pActor, 1, velocity, 0);
        state->nSpeed64 = 0;
        state->nPhase6e++;
        if (state->nPhase6e > state->nPhaseMax6f) {
            state->nPhase6e = state->nPhaseMax6f;
        }
        func_01ffa724(-0x1000, &state->vDirection14, &velocity);
        targetAngle = VEC_DotProduct(&velocity, &normal);
        func_01ffa724(targetAngle << 1, &normal, &reflected);
        VEC_Subtract(&reflected, &velocity, &reflected);
        reflected.y = 0;
        if (func_01ff8d18(&reflected, &state->vDirection14) == 0) {
            state->vDirection14 = data_02042258;
        }
        state->bHoming78 = 0;
        state->nTurnAngle58 = 0;
    } else if (state->bHoming78 == 0) {
        state->pTarget = (struct Ov214Actor *)func_ov107_020cab14(state->pActor, 0);
        if (state->pTarget != 0 && state->nTimer5c <= 0) {
            VEC_Subtract((struct VecFx32 *)((char *)state->pTarget + 0x190),
                         &state->pActor->vCenterb0, &delta);
            delta.y = 0;
            collision = func_01ff8d18(&delta, &delta);
            if (collision == 0) {
                delta = data_02042258;
            }
            targetAngle = func_020050b4(delta.x, delta.z);
            index = ANGLE_TO_INDEX(targetAngle);
            state->vDirection14.x = data_0203d210[index * 2];
            state->vDirection14.y = 0;
            state->vDirection14.z = data_0203d210[index * 2 + 1];
            if (collision < 0x10000) {
                state->bHoming78 = 1;
                state->nTimer5c = 0x5000;
                state->nDelay60 = 0x4cc;
                state->nVertical68 = 0x700;
            }
        }
    }

    if (state->bHoming78 != 0) {
        wasPositive = state->nDelay60 > 0;
        if (((struct Ov214CollisionFlags *)&state->pActor->bCollisionFlags17a)->bGrounded) {
            state->nDelay60 -= task->pActor->nFrameDelta2c;
        }
        if (state->nDelay60 <= 0) {
            if (wasPositive) {
                if (state->pTarget != 0) {
                    VEC_Subtract((struct VecFx32 *)((char *)state->pTarget + 0x190),
                                 &state->pActor->vCenterb0, &delta2);
                    targetAngle = func_020050b4(delta2.x, delta2.z);
                    index = ANGLE_TO_INDEX(targetAngle);
                    state->vDirection14.x = data_0203d210[index * 2];
                    state->vDirection14.y = 0;
                    state->vDirection14.z = data_0203d210[index * 2 + 1];
                } else {
                    state->vDirection14 = data_02042258;
                }
            }
            func_01ffa724(0x800, &state->vDirection14, &state->vVelocity20);
            state->nDelay60 = 0;
        } else {
            for (step = task->pActor->nFrameDelta2c; step > 0; step -= 0x88) {
                int slice;
                if (step <= 0x88) {
                    slice = step;
                } else {
                    slice = 0x88;
                }
                inverse = FX_Inv(slice, 0x88);
                state->nSpeed64 = FX_MUL(state->nSpeed64, 0x1000 - FX_MUL(inverse, 0x100));
            }
            func_01ffa724(state->nSpeed64, &state->vDirection14, &state->vVelocity20);
            state->vVelocity20.y = state->nVertical68;
            if (state->nVertical68 > -0x7000) {
                gravityStep = task->pActor->nFrameDelta2c * -0x80;
                state->nVertical68 += gravityStep / 0x88;
            }
        }
    } else {
        state->nTimer5c -= task->pActor->nFrameDelta2c;
        if (state->nTimer5c <= 0) {
            state->nTimer5c = 0;
        }
        index = state->nTurnAngle58 >> 4;
        MTX_RotY33_(&matrix, data_0203d210[index * 2], data_0203d210[index * 2 + 1]);
        MTX_MultVec33(&state->vDirection14, &matrix, &rotated);
        state->nTurnAngle58 += 0xb6;
        if (state->nTurnAngle58 > 0x1fff) {
            state->nTurnAngle58 = 0x1fff;
        }
        phaseCount = (int)state->nPhaseMax6f - 1;
        targetAngle = phaseCount - (int)state->nPhase6e;
        targetAngle *= 0x300;
        targetAngle = func_02020400(targetAngle, phaseCount) + 0x500;
        for (step = task->pActor->nFrameDelta2c; step > 0; step -= 0x88) {
            state->nSpeed64 += FX_MUL(targetAngle - state->nSpeed64, 0x800);
        }
        func_01ffa724(state->nSpeed64, &rotated, &state->vVelocity20);
    }

    if ((state->nMode6c = 0) == 0) {
        func_ov107_020c0b90(state->pActor, 7, *state->pOffset10, 0);
    }
    func_ov214_020cce44(state, 0, 0);
}
