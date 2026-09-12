typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct Desc {
    u8 nKind;                        /* 0x00 */
    u8 pad01[3];
    int nField04;                    /* 0x04 */
    int nOffsetY;                    /* 0x08 */
    u8 pad0c[0x10];
    int nField1c;                    /* 0x1c */
    u8 pad20[0xc];
    int nField2c;                    /* 0x2c */
    int nField30;                    /* 0x30 */
    int nField34;                    /* 0x34 */
    struct VecFx32 vecField38;       /* 0x38 */
    u8 nLevel;                       /* 0x44 */
};

struct SlotPart {
    int nTimer;                      /* 0x000 */
    u8 pad004[0x18];
    u16 nSlotFlags;                  /* 0x01c */
    u8 pad01e[0xa2];
    struct VecFx32 vecAt;            /* 0x0c0 */
    u8 pad0cc[0x7c];
    struct Desc *pDesc;              /* 0x148 */
    u8 nState;                       /* 0x14c */
    u8 nGroup : 3;                   /* 0x14d */
    u8 nSpare : 5;
    u8 nRepeat;                      /* 0x14e */
};

struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                       /* 0x0c */
    u8 pad10[0x48];
    void *pActor;                    /* 0x58 */
};

/* Ov022Capsule: the segment the sweep handlers test, named after the matched
 * readers func_ov022_0209e398 and func_ov022_020a1064. */
struct Capsule {
    struct VecFx32 vecA;             /* 0x00 */
    struct VecFx32 vecB;             /* 0x0c */
    int nGroup;                      /* 0x18 */
    int nRadius;                     /* 0x1c */
};

/* Ov022SpawnRequest */
struct SpawnQuery {
    struct Capsule capsule;          /* 0x00 */
    int nField20;                    /* 0x20 */
    int nField24;                    /* 0x24 */
};

/* Ov022ActionParams */
struct ActionParams {
    int nValue;                      /* 0x00 */
    int nField04;                    /* 0x04 */
    int nField08;                    /* 0x08 */
    int nField0c;                    /* 0x0c */
    u8 nLevel;                       /* 0x10 */
    u8 pad11[3];
    struct VecFx32 vecField14;       /* 0x14 */
    int nField20;                    /* 0x20 */
    s8 nPhase;                       /* 0x24 */
    u8 bFlag0 : 1;                   /* 0x25 bit 0 */
    u8 bFlag1 : 1;                   /*      bit 1 */
    u8 nSpare : 6;
    u8 pad26[2];
};

extern void func_ov022_0208a938(u16 *pFlags, int nValue);
extern int func_0202a818(u16 *pFlags, int nDelta);
extern void func_ov022_0208a6b0(struct ReactionCtx *pCtx);
extern int func_ov022_020a216c(void *pActor, int nKey, int nActionLevel);
extern int func_ov022_0208ac80(struct ReactionCtx *pCtx,
                               struct SpawnQuery *pQuery,
                               struct ActionParams *pParams);

#define KIND_SPAWNER 8
#define AGE_LIMIT 0xa000
#define REPEAT_MARK 0x8000
#define REPEAT_RESET 0x4000
#define REPEAT_STEP 0x2000
#define SPAWN_MARK 0x6000
#define STATE_SPENT 4
#define STATE_HELD 3

int func_ov022_0208ebf8(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                        int nDelta)
{
    void *pActor;
    struct Desc *pDesc;
    struct SpawnQuery query;
    struct ActionParams params;
    struct SpawnQuery *pQuery;
    struct ActionParams *pParams;
    int bExpired;
    int nGroup;

    pActor = pCtx->pActor;
    pDesc = pPart->pDesc;
    pPart->nTimer = pPart->nTimer + nDelta;
    bExpired = 0;
    if (pDesc->nKind == KIND_SPAWNER && pDesc->nField1c != 0
        && pPart->nTimer >= AGE_LIMIT) {
        bExpired = 1;
    }
    if (pPart->nRepeat != 0 && pPart->nTimer >= REPEAT_MARK) {
        pPart->nTimer = REPEAT_RESET;
        pPart->nRepeat = pPart->nRepeat - 1;
        func_ov022_0208a938(&pPart->nSlotFlags, REPEAT_STEP);
    }
    if (func_0202a818(&pPart->nSlotFlags, nDelta) != 0 || bExpired != 0) {
        pPart->nTimer = 0;
        if (bExpired != 0) {
            func_ov022_0208a6b0(pCtx);
            pPart->nState = STATE_HELD;
        } else {
            pPart->nState = STATE_SPENT;
        }
    } else if (pPart->nTimer == SPAWN_MARK) {
        pQuery = &query;
        pParams = &params;
        query.capsule.vecB = pPart->vecAt;
        query.capsule.vecA = query.capsule.vecB;
        query.capsule.vecA.y = query.capsule.vecA.y + pDesc->nOffsetY;
        query.capsule.nRadius = pDesc->nField04;
        nGroup = pPart->nGroup;
        query.nField20 = 0;
        query.nField24 = 0;
        query.capsule.nGroup = nGroup;
        params.nField0c = pDesc->nField34;
        params.nValue = func_ov022_020a216c(pActor, pDesc->nField2c, params.nField0c);
        params.nField08 = pDesc->nField30;
        params.vecField14 = pDesc->vecField38;
        params.nField20 = 0;
        params.bFlag0 = 0;
        params.bFlag1 = 0;
        params.nLevel = pDesc->nLevel;
        params.nField04 = 0;
        params.nPhase = (s8)(pCtx->nSlot % 3);
        func_ov022_0208ac80(pCtx, pQuery, pParams);
    }
    return 0;
}
