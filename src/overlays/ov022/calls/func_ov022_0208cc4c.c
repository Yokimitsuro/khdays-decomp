/* Ov022_StepSlotState2 -- one frame of the slot state that ends on contact.
 *
 * Only an open slot is stepped. Once its timer has reached its radius it asks
 * whether its action lands, from where it is aimed, out to a fixed reach, with
 * no direction and the full circle, and against nobody in particular. An answer
 * of either kind ends the run, each with its own reaction. The run also ends
 * once the timer has reached the slot's power while the slot is already in the
 * second state.
 *
 * Whatever happens, the slot's own tracks take the frame.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 pad000[8];
    u16 nSlotFlags;                  /* 0x008 */
    u8 pad00a[0xa2];
    struct VecFx32 vecAim;           /* 0x0ac */
    u8 pad0b8[0x58];
    s8 nSlotIndex;                   /* 0x110 */
    u8 pad111[3];
    u16 nOpen;                       /* 0x114 */
    u16 pad116;
    u8 nState;                       /* 0x118 */
    u8 pad119[3];
    int nTimer;                      /* 0x11c */
    int nPower;                      /* 0x120 */
    int nRadius;                     /* 0x124 */
};

struct Actor;

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                       /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[11];    /* 0x18 */
};

/* Ov022ActionQuery */
struct ActionQuery {
    struct VecFx32 vecPos;           /* 0x00 */
    int nRadius;                     /* 0x0c */
    unsigned int nGroup;             /* 0x10 */
    struct VecFx32 vecDir;           /* 0x14 */
    int nConeLimit;                  /* 0x20 */
    short *pHitIds;                  /* 0x24 */
    int nField28;                    /* 0x28 */
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
    u8 bFlag1 : 1;                   /* bit 1 */
    u8 nSpare : 6;
    u8 pad26[2];
};

extern const struct VecFx32 data_02041dc8;

extern int func_ov022_0208ac10(struct ReactionCtx *pCtx,
                               struct ActionQuery *pQuery,
                               struct ActionParams *pParams);
extern int func_ov022_0208acc4(int nKind, int nArg);
extern void func_ov022_0208a50c(struct ReactionCtx *pCtx,
                                struct ActorSlot *pSlot, int nReaction);
extern int func_0202a818(u16 *pFlags, int nDelta);

#define SLOT_OPEN 0xffff
#define REACH 0x4000
#define FX32_ONE 0x1000
#define REACTION_KIND 5
#define STATE_SECOND 2

int func_ov022_0208cc4c(struct ReactionCtx *pCtx, int nDelta)
{
    struct ActionQuery query;
    struct ActionParams params;
    int bDone;
    struct ActorSlot *pSlot;
    int nReaction;
    int nAnswer;
    int nIndex;

    pSlot = pCtx->aSlots[pCtx->nSlot];
    bDone = 0;
    if (pSlot->nOpen == SLOT_OPEN) {
        if (pSlot->nTimer >= pSlot->nRadius) {
            query.vecPos = pSlot->vecAim;
            query.vecDir.x = 0;
            query.vecDir.y = 0;
            query.vecDir.z = 0;
            nIndex = pSlot->nSlotIndex;
            params.nField08 = 0x88;
            params.nField0c = 0;
            params.nValue = 0;
            query.nGroup = nIndex;
            params.vecField14 = data_02041dc8;
            query.nRadius = REACH;
            query.nConeLimit = FX32_ONE;
            query.pHitIds = 0;
            query.nField28 = 0;
            params.nField20 = 0;
            params.bFlag0 = 0;
            params.bFlag1 = 0;
            params.nLevel = 0;
            params.nField04 = 0;
            params.nPhase = (s8)(pCtx->nSlot % 3);
            nAnswer = func_ov022_0208ac10(pCtx, &query, &params);
            if (nAnswer != 0) {
                if (nAnswer == 1) {
                    nReaction = func_ov022_0208acc4(REACTION_KIND, 1);
                } else if (nAnswer == 2) {
                    nReaction = func_ov022_0208acc4(REACTION_KIND, 2);
                }
                bDone = 1;
            }
        }
        if (pSlot->nTimer >= pSlot->nPower && pSlot->nState == STATE_SECOND) {
            nReaction = func_ov022_0208acc4(REACTION_KIND, 2);
            bDone = 1;
        }
        if (bDone != 0) {
            func_ov022_0208a50c(pCtx, pSlot, nReaction);
        }
    }
    func_0202a818(&pSlot->nSlotFlags, nDelta);
    return 0;
}
