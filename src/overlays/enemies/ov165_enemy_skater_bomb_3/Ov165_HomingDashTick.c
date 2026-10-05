/* Ov165_HomingDashTick: ported from a matched sibling family (same shape, constants and offsets adjusted). */

/*
 * Coordinates are held in a one-value wrapper type (Fx32), a tentative
 * reconstruction of the original's coordinate type. Copying a wrapped value is
 * a struct copy, which mwcc keeps, and that is the ROM's unread stack copy of
 * the position.
 */

#include "nitro/types.h"
#include "game/ai_task.h"
#include "game/engine.h"

typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;

typedef struct {
    int x;
    int y;
    int z;
    int w;
} Quat;

struct Sphere {
    FxVec centre;
    int radius;
};

struct Msg {
    u16 h[7];
};

struct Flags60 {
    u16 lo : 8;
    u16 hi : 8;
};

struct Flags17a {
    u8 bBit0 : 1;
    u8 bBit1 : 1;
};

struct State {
    void *pActor;
    char pad04[4];
    void *pTarget;
    int nAngle0c;
    int nAngle10;
    char pad14[4];
    FxVec vStep;
    char pad24[0x28];
    int nSpeed4c;
    char pad40[0x14];
    int nDistance64;
};

struct Node {
    AI_TASK_FIELDS(struct State)
};

extern void VEC_Subtract(FxVec *a, FxVec *b, FxVec *ab);
extern void VEC_Add(FxVec *a, FxVec *b, FxVec *ab);
extern int VEC_DotProduct(FxVec *a, FxVec *b);
extern int VEC_Normalize(FxVec *out, FxVec *in);
extern void ScaleVec3Fx12(int scale, FxVec *in, FxVec *out);
extern void Quat_FromTwoVectors(Quat *out, const FxVec *a, FxVec *b);
extern void Quat_Slerp(Quat *out, int t, Quat *a, Quat *b);
extern fx16 FX_Atan2(int x, int z);
extern void Srt_SetRotationQuat(void *srt, Quat *q);
extern void *Ov107_FindNearestObject(void *actor, int mode);
extern int Ov107_CollectSphereOverlaps(void *actor, struct Sphere *shape, void **out);
extern int Ov107_InvokeHitCallback(void *victim, void *a, void *b, int mode,
                               FxVec *push, int flags);
extern void Ov107_BuildAndSendUpdate(void *actor, int id, u16 mode, FxVec *at);
extern void Ov107_PostTagUpdate(void *actor, int a, int b);
extern void Ov107_StartAnim(void *obj, int a, int b);
extern void SetIndexedSlot(struct Node *node, int slot, void *next);

extern const FxVec data_02042258;
extern const FxVec data_02042264;
extern const struct Msg data_ov165_020d4abe;
extern void Ov165_AiReleaseHeldAndAim(void);

void Ov165_HomingDashTick(struct Node *node)
{
    struct State *st;
    FxVec vFwd;
    FxVec vToTarget;
    Quat quat;
    Quat delta;
    struct Sphere shape;
    void *aVictims[4];
    FxVec vPush;
    FxVec vImpact;
    struct Msg msg;
    FxVec vFacing;
    struct Msg tmpl;
    FxVec raw;
    void (*pfnHook)(void *, struct Msg *, int);
    int i;
    int hit;
    int angle;
    int nHits;

    st = node->pState;
    hit = 0;
    st->pTarget = Ov107_FindNearestObject(st->pActor, 0);
    if (st->pTarget == 0) {
        *(u8 *)((char *)st->pActor + 0x1c7) = 2;
        SetIndexedSlot(node, node->slot, 0);
        return;
    }

    quat = *(Quat *)((char *)st->pActor + 0xa0);
    Vec3TransformViaTempMtx(&vFwd, &quat, &data_02042258);
    VEC_Normalize(&vFwd, &vFwd);
    VEC_Subtract((FxVec *)((char *)*(void **)((char *)st->pTarget + 0x1d8) + 4),
                 (FxVec *)((char *)*(void **)((char *)st->pActor + 0x38c) + 4),
                 &vToTarget);
    VEC_Normalize(&vToTarget, &vToTarget);
    Quat_FromTwoVectors(&delta, &data_02042258, &vToTarget);
    if (VEC_DotProduct(&vFwd, &vToTarget) >= -0xa00) {
        Quat_Slerp(&quat, (int)((((long long)(*(int *)((char *)node->pList + 0x2c) * 0x1e) << 27) + 0x80000000) >> 32),
                      &quat, &delta);
        Vec4_Normalize(&quat, &quat);
        Srt_SetRotationQuat((char *)st->pActor + 0xa0, &quat);
    }

    Vec3TransformViaTempMtx(&st->vStep, (Quat *)((char *)st->pActor + 0xa0), &data_02042258);
    VEC_Normalize(&st->vStep, &st->vStep);
    ScaleVec3Fx12(st->nSpeed4c, &st->vStep, &st->vStep);
    st->nDistance64 = st->nDistance64 + st->nSpeed4c;

    shape.centre = *(FxVec *)((char *)*(void **)((char *)st->pActor + 0x38c) + 4);
    VEC_Add(&shape.centre, &st->vStep, &shape.centre);
    shape.radius = 0x1000;
    nHits = Ov107_CollectSphereOverlaps(st->pActor, &shape, aVictims);
    i = 0;
    if (nHits > 0) {
        tmpl = data_ov165_020d4abe;
        do {
            VEC_Subtract((FxVec *)((char *)*(void **)((char *)aVictims[i] + 0x1d8) + 4),
                         &shape.centre, &vPush);
            vPush.y.value = 0;
            VEC_Normalize(&vPush, &vPush);
            ScaleVec3Fx12(0x800, &vPush, &vPush);
            if (Ov107_InvokeHitCallback(aVictims[i], st->pActor, st->pActor, 2,
                                    &vPush, 0) != 0) {
                msg = tmpl;
                ScaleVec3Fx12(shape.radius, &vToTarget, &vImpact);
                VEC_Add(&shape.centre, &vImpact, &vImpact);
                raw.x = vImpact.x;
                raw.y = vImpact.y;
                raw.z = vImpact.z;
                ((u8 *)&msg)[5] = (u8)(((u32)raw.x.value >> 16 & 0x7f) |
                                       ((u32)raw.x.value >> 24 & 0x80));
                ((u8 *)&msg)[6] = (u8)((u32)raw.x.value >> 8);
                ((u8 *)&msg)[7] = (u8)raw.x.value;
                ((u8 *)&msg)[8] = (u8)(((u32)raw.y.value >> 16 & 0x7f) |
                                       ((u32)raw.y.value >> 24 & 0x80));
                ((u8 *)&msg)[9] = (u8)((u32)raw.y.value >> 8);
                ((u8 *)&msg)[10] = (u8)raw.y.value;
                ((u8 *)&msg)[11] = (u8)(((u32)raw.z.value >> 16 & 0x7f) |
                                        ((u32)raw.z.value >> 24 & 0x80));
                ((u8 *)&msg)[12] = (u8)((u32)raw.z.value >> 8);
                ((u8 *)&msg)[13] = (u8)raw.z.value;
                pfnHook = *(void (**)(void *, struct Msg *, int))((char *)st->pActor + 0x24);
                if (pfnHook != 0) {
                    (*pfnHook)(st->pActor, &msg, 0xe);
                }
                hit = 1;
                Ov107_BuildAndSendUpdate(st->pActor, 0x153, 5, &vImpact);
            }
            i++;
        } while (i < nHits);
    }

    if (hit == 0 && st->nDistance64 < 0x6000 &&
        ((struct Flags17a *)((char *)st->pActor + 0x17a))->bBit0 == 0 &&
        ((struct Flags17a *)((char *)st->pActor + 0x17a))->bBit1 == 0) {
        return;
    }

    Vec3TransformViaTempMtx(&vFacing, &quat, &data_02042258);
    vFacing.y.value = 0;
    if (VEC_Normalize(&vFacing, &vFacing) == 0) {
        vFacing = data_02042258;
    }
    angle = st->nAngle10 = FX_Atan2(vFacing.x.value, vFacing.z.value);
    st->nAngle0c = angle;
    QuatFromAxisAngle(&quat, &data_02042264, angle);
    Srt_SetRotationQuat((char *)st->pActor + 0xa0, &quat);
    Ov107_PostTagUpdate(st->pActor, 5, 0);
    ((struct Flags60 *)((char *)st->pActor + 0x60))->hi =
        ((struct Flags60 *)((char *)st->pActor + 0x60))->hi & ~0x40;
    Ov107_StartAnim(*(void **)((char *)st->pActor + 0x3c8), 1, 0);
    SetIndexedSlot(node, node->slot, (void *)Ov165_AiReleaseHeldAndAim);
}
