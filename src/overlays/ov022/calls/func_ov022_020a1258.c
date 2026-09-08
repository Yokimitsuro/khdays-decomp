/* ov022: report a hit the local player landed.
 *
 * Only the first player's session builds the record; everyone else's copy of
 * the actor learns about the hit over the wire instead. The record carries the
 * actor's id, the two words the source describes itself with, and the source's
 * mask -- which is either the mask itself or the single bit its number selects,
 * depending on the source's own flag. The contact point comes from the caller.
 *
 * A hit with no kind flag is the ordinary one: it is marked kind one and the
 * impact point is fetched from the owner. A hit with the flag is kind two and
 * keeps whatever impact point was already there. Either way the actor is left
 * in the hit state pointing at the owner, and whatever the report answers is
 * folded into the actor's hit result.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

#define HIT_KIND_NORMAL 1
#define HIT_KIND_FLAGGED 2
#define HIT_STATE_LANDED 2

struct Source {
    u32 nA;                      /* 0x00 */
    u8 pad0004[4];
    u32 nB;                      /* 0x08 */
    u32 nMask;                   /* 0x0c */
    u8 pad0010[0x15];
    u8 nSpare25 : 1;             /* 0x25 bit 0 */
    u8 bMaskIsDirect : 1;        /* 0x25 bit 1 */
    u8 nRest25 : 6;
};

struct HitRecord {
    VecFx32 vecPos;              /* 0x00 */
    u8 nId;                      /* 0x0c */
    u8 nKind;                    /* 0x0d */
    u8 pad000e[2];
    u32 nA;                      /* 0x10 */
    u32 nB;                      /* 0x14 */
    u32 nMask;                   /* 0x18 */
};

struct Actor {
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x26b2];
    u32 nHitResult;              /* 0x26bc */
    u8 pad26c0[4];
    u8 nHitState;                /* 0x26c4 */
    u8 pad26c5[3];
    VecFx32 vecImpact;           /* 0x26c8 */
    void *pHitOwner;             /* 0x26d4 */
};

extern int func_02030788(void);                 /* local player index */
extern VecFx32 *func_ov002_02076d24(void *pOwner);
extern u32 func_ov002_02076dac(void *pOwner, struct HitRecord *pRec);

void func_ov022_020a1258(struct Actor *pActor, struct Source *pSrc,
                         void *pOwner, const VecFx32 *pvecPos, int bFlagged)
{
    struct HitRecord rec;
    VecFx32 *pvecImpact;

    if (func_02030788() != 0) {
        return;
    }
    rec.nId = pActor->nId;
    rec.nA = pSrc->nA;
    rec.nB = pSrc->nB;
    if (pSrc->bMaskIsDirect == 0) {
        rec.nMask = 1 << pSrc->nMask;
    } else {
        rec.nMask = pSrc->nMask;
    }
    rec.vecPos = *pvecPos;
    if (bFlagged != 0) {
        rec.nKind = HIT_KIND_FLAGGED;
    } else {
        rec.nKind = HIT_KIND_NORMAL;
        pvecImpact = func_ov002_02076d24(pOwner);
        pActor->vecImpact = *pvecImpact;
    }
    pActor->nHitState = HIT_STATE_LANDED;
    pActor->pHitOwner = pOwner;
    pActor->nHitResult |= func_ov002_02076dac(pOwner, &rec);
}
