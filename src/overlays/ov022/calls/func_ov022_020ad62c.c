/* ov022: fill the two parameter blocks an effect is spawned from.
 *
 * Either block may be left out, and each is filled independently.
 *
 * The first is placed on the actor: it takes the actor's own effect anchor, a
 * unit scale on two axes, the actor's area key, and a direction that is its
 * facing negated, so the effect faces back down the actor's front. It also
 * carries a pointer to the actor's own trailing block.
 *
 * The second is cleared outright and then given only three things: a fixed flag
 * word, a count of one, and the caller's own point.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

#define ANGLE_BIAS 0x8000
#define ANGLE_SHIFT 4
#define UNIT_SCALE 0x1000
#define SPAWN_FLAGS 0x808
#define ACTOR_TAIL 0x2bd4

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022ActorNode */
struct ActorNode {
    u8 pad00[0x80];
    u16 nAngle;                  /* 0x80 */
    u8 pad82[2];
};

/* Ov022Actor */
struct Actor {
    u8 pad000[0x20];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad024[0x42];
    s16 nSlotIndex;              /* 0x0066 */
    u8 pad068[0x2b6c];
    u8 aEffectTail[0x28];        /* 0x2bd4 */
};

/* the block the effect is placed with */
struct EffectPlace {
    struct VecFx32 vecAt;        /* 0x00 */
    int nScaleX;                 /* 0x0c */
    int nSlotIndex;              /* 0x10 */
    struct VecFx32 vecFace;      /* 0x14 */
    int nScaleZ;                 /* 0x20 */
    void *pTail;                 /* 0x24 */
    int nField28;                /* 0x28 */
};

/* the block the effect is requested with */
struct EffectRequest {
    u8 pad00[8];
    int nFlags;                  /* 0x08 */
    u8 pad0c[8];
    struct VecFx32 vecAt;        /* 0x14 */
    int nCount;                  /* 0x20 */
    u8 pad24[4];
};

/* kFxSinCosTable, read as one flat array of halfwords. It has to be const:
 * without that the compiler cannot move the two reads past the first store it
 * feeds, and ends up holding the doubled index in a callee-saved register. */
extern const s16 data_0203d210[];

extern void func_ov022_020ad44c(struct VecFx32 *pOut, struct Actor *pActor);
extern void MI_CpuFill8(void *pDst, u8 nByte, u32 nSize);

void func_ov022_020ad62c(struct Actor *pActor, struct VecFx32 *pAt,
                         struct EffectPlace *pPlace,
                         struct EffectRequest *pRequest)
{
    struct VecFx32 vecAt;
    int nIndex;
    int nSin;
    int nCos;

    if (pPlace != 0) {
        func_ov022_020ad44c(&vecAt, pActor);
        pPlace->vecAt = vecAt;
        nIndex = (u16)(pActor->pNode->nAngle - ANGLE_BIAS) >> ANGLE_SHIFT;
        nSin = data_0203d210[nIndex * 2];
        nCos = data_0203d210[nIndex * 2 + 1];
        pPlace->vecFace.x = -nSin;
        pPlace->vecFace.z = -nCos;
        pPlace->vecFace.y = 0;
        pPlace->nScaleX = UNIT_SCALE;
        pPlace->nSlotIndex = pActor->nSlotIndex;
        pPlace->nScaleZ = UNIT_SCALE;
        pPlace->pTail = pActor->aEffectTail;
        pPlace->nField28 = 0;
    }
    if (pRequest != 0) {
        MI_CpuFill8(pRequest, 0, 0x28);
        pRequest->nFlags = SPAWN_FLAGS;
        pRequest->nCount = 1;
        pRequest->vecAt = *pAt;
    }
}
