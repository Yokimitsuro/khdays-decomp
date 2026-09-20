typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int m[9];
} MtxFx33;

struct Ov043Model {
    u8 pad000[0x80];
    u16 heading080;
};

struct Ov043Actor {
    u8 pad0000[0x20];
    struct Ov043Model *pModel020;
    u8 pad024[0x698];
    int actionId6BC;
    u8 pad6C0[0x2004];
    u8 soundState26C4;
    u8 pad26C5[3];
    VecFx32 soundPosition26C8;
};

struct Ov043EffectGroup {
    u8 pad000[8];
    struct Ov043Actor *pActor008;
};

struct Ov043EffectConfig {
    u8 pad000[0xc];
    int collisionParam00C;
};

struct Ov043RequestEffect {
    u8 pad000;
    s8 slot001;
    s8 state002;
    u8 pad003;
    int elapsed004;
    u8 collisionKind008;
    u8 pad009[3];
    int speed00C;
    u8 pad010[0x18];
    u8 animation028[0xa4];
    VecFx32 position0CC;
    VecFx32 scaleAndLength0D8;
    u8 pad0E4[0x54];
    struct Ov043EffectConfig *pConfig138;
    short handles13C[8];
};

struct Ov043Sweep {
    VecFx32 start;
    VecFx32 end;
    u32 kind;
    int config;
    int zero1;
    int zero2;
};

struct Ov043HitResult {
    u8 pad000[0xc];
    VecFx32 position00C;
    u8 pad018[0x9c];
};

extern char *data_ov043_020b58e0;
extern short data_0203d210[];

extern void func_ov043_020b4ef0(struct Ov043Actor *pActor, int slot, VecFx32 *pOut);
extern void MTX_RotY33_(MtxFx33 *pMtx, int nSin, int nCos);
extern void func_ov043_020b4cd4(struct Ov043RequestEffect *pEffect, VecFx32 *pOut);
extern void MTX_MultVec33(const VecFx32 *pVec, const MtxFx33 *pMtx, VecFx32 *pOut);
extern void func_01ffa724(int scale, const VecFx32 *pVec, VecFx32 *pOut);
extern void VEC_Add(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern void VEC_Subtract(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern int VEC_Mag(const VecFx32 *pVec);
extern int func_ov022_020a1c80(struct Ov043Actor *pActor, struct Ov043Sweep *pSweep,
                               struct Ov043HitResult *pHit);
extern void func_ov043_020b4fb8(struct Ov043Actor *pActor, char *pNode, int slot,
                                VecFx32 *pPosition, VecFx32 *pDirection);
extern void func_ov022_02091b48(struct Ov043EffectGroup *pGroup,
                                struct Ov043RequestEffect *pEffect,
                                VecFx32 *pPosition, VecFx32 *pDirection);
extern void func_ov022_020ad28c(struct Ov043Actor *pActor, VecFx32 *pPosition,
                                int nCue, int nVariant);
extern void func_ov022_02091540(void *pAnimation, int dt);
extern void func_ov022_02091d80(struct Ov043EffectGroup *pGroup,
                                struct Ov043RequestEffect *pEffect);

int func_ov043_020b547c(struct Ov043EffectGroup *pGroup,
                        struct Ov043RequestEffect *pEffect, int dt)
{
    MtxFx33 rotation;
    VecFx32 slotPosition;
    VecFx32 swing;
    struct Ov043Sweep sweep;
    VecFx32 scaleAndLength;
    VecFx32 finalPosition;
    struct Ov043HitResult hit;
    char *pNode;
    struct Ov043Actor *pActor;
    struct Ov043EffectConfig *pConfig;
    u16 heading;
    u16 adjustedHeading;
    int index;
    int length;
    int i;

    pActor = pGroup->pActor008;
    heading = pActor->pModel020->heading080;
    pNode = data_ov043_020b58e0 + 0x2d38;
    pConfig = pEffect->pConfig138;
    adjustedHeading = heading - 0x8000;
    func_ov043_020b4ef0(pActor, pEffect->slot001, &slotPosition);
    index = (int)adjustedHeading >> 4;
    MTX_RotY33_(&rotation, -data_0203d210[index * 2],
                -data_0203d210[index * 2 + 1]);
    func_ov043_020b4cd4(pEffect, &swing);
    pEffect->elapsed004 += dt;
    MTX_MultVec33(&swing, &rotation, &swing);
    func_01ffa724(0x6000, &swing, &swing);

    sweep.start = slotPosition;
    VEC_Add(&sweep.start, &swing, &sweep.end);
    sweep.config = pConfig->collisionParam00C;
    sweep.zero1 = 0;
    sweep.kind = pEffect->collisionKind008;
    sweep.zero2 = 0;
    if (func_ov022_020a1c80(pActor, &sweep, &hit) != 0) {
        VEC_Subtract(&hit.position00C, &slotPosition, &swing);
        length = VEC_Mag(&swing);
        finalPosition = hit.position00C;
    } else {
        length = VEC_Mag(&swing);
        VEC_Add(&swing, &slotPosition, &finalPosition);
    }

    scaleAndLength.y = 0x1000;
    scaleAndLength.x = 0x1000;
    scaleAndLength.z = length;
    pEffect->scaleAndLength0D8 = scaleAndLength;
    func_ov043_020b4fb8(pActor, pNode, pEffect->slot001, &finalPosition, &swing);
    pEffect->speed00C = 0x1100;

    *(int *)(pNode + 0x368 + pEffect->slot001 * 0x240) += dt;
    if (*(int *)(pNode + 0x368 + pEffect->slot001 * 0x240) >= 0x15000) {
        for (i = 0; i < 8; i++) {
            pEffect->handles13C[i] = -1;
        }
        *(int *)(pNode + 0x368 + pEffect->slot001 * 0x240) = 0;
    }

    func_ov022_02091b48(pGroup, pEffect, &slotPosition, &swing);
    if (pActor->soundState26C4 != 0 && pActor->soundState26C4 != 4) {
        func_ov022_020ad28c(pActor, &pActor->soundPosition26C8, 0xc4, 2);
    }
    pEffect->state002 = 2;
    pEffect->position0CC = slotPosition;
    func_ov022_02091540(pEffect->animation028, dt);
    if (pActor->actionId6BC != 0x30) {
        pEffect->state002 = 3;
    }
    if (pEffect->state002 != 2) {
        pEffect->elapsed004 = 0;
        func_ov022_02091d80(pGroup, pEffect);
    }
    return 0;
}
