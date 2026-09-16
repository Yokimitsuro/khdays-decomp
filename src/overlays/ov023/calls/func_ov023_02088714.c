/* func_ov023_02088714 -- Ov023_ActorInit: reset an actor of the event for entity nEntity with
 * the word given: flags 0x1d (+0x1a28), the walk target and its previous copy zeroed
 * (+0x15c0 / +0x15cc), the walk speed (+0x15d8) cleared, +0x15bc -1 and +0x15b8 1.0, no
 * parent (+0) or children (+0x1a3c); the pending entries (+0x984) are wiped with ids -1 and
 * the whole motion set (+0x538) wiped with frames -1. */
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef signed short   s16;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov023Motion {
    int  nEndFrame;           /* 0x00 */
    s16  nFrame;              /* 0x04 */
    u8   pad_06[2];
    int  nBlend;              /* 0x08 */
    char szName[0x20];        /* 0x0c */
} Ov023Motion;                /* 0x2c */

typedef struct Ov023RotTween {
    u8   pad_00[0x18];
    int  nJoint;              /* 0x18 */
    u8   pad_1c[0x28 - 0x1c];
} Ov023RotTween;               /* 0x28 */

typedef struct Ov023Actor {
    struct Ov023Actor *pParent; /* 0x0000 */
    u8   pad_0004[0x538 - 0x4];
    Ov023Motion aMotion[5][5]; /* 0x0538: [depth][track] */
    Ov023RotTween aRotTween[7]; /* 0x0984 */
    u8   pad_0a9c[0x15b8 - 0xa9c];
    int  nTurnSpeed;          /* 0x15b8: fx32 */
    int  nTurnDirection;      /* 0x15bc: -1 shorter way, 0 up, else down */
    VecFx32 vTarget;          /* 0x15c0 */
    VecFx32 vTargetPrev;      /* 0x15cc */
    int  nWalkSpeed;          /* 0x15d8 */
    u8   pad_15dc[0x1a28 - 0x15dc];
    int  nFlags;              /* 0x1a28 */
    int  nField1a2c;          /* 0x1a2c */
    u8   pad_1a30[8];
    int  nEntity;             /* 0x1a38 */
    int  nChildren;           /* 0x1a3c */
} Ov023Actor;

extern void MI_CpuFill8(void *pDst, u32 nValue, u32 nSize);

void func_ov023_02088714(Ov023Actor *pActor, int nWord, int nEntity)
{
    int i;
    int j;

    pActor->nFlags = 0x1d;
    pActor->vTargetPrev.x = pActor->vTargetPrev.y = pActor->vTargetPrev.z = 0;
    pActor->vTarget.x = pActor->vTarget.y = pActor->vTarget.z = 0;
    pActor->nWalkSpeed = 0;
    pActor->nField1a2c = nWord;
    pActor->nEntity = nEntity;
    pActor->pParent = 0;
    pActor->nTurnDirection = -1;
    pActor->nTurnSpeed = 0x1000;
    pActor->nChildren = 0;
    MI_CpuFill8(pActor->aRotTween, 0, 0x78);
    for (i = 0; i < 7; i++) {
        pActor->aRotTween[i].nJoint = -1;
    }
    MI_CpuFill8(pActor->aMotion, 0, sizeof(pActor->aMotion));
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            pActor->aMotion[j][i].nFrame = -1;
        }
    }
}
