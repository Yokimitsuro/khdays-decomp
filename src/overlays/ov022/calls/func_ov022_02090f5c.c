/* Ov022_TestShotHit -- run a shot's hit test for one frame.
 *
 * The radius and the damage factor come from the shot's descriptor, except
 * that a shot in state 4 uses the descriptor's phase-4 radius and, when the
 * descriptor's bit 11 is set, its phase-4 factor too. The descriptor's hit
 * kind picks the query shape: kind 0 casts a direction from the position with
 * a full cone; kind 1 tests the segment from the position to position plus
 * delta. Both carry the shot's owner as the group, the shot's hit-id list and
 * whether the shot is on its first hit (nField134 == 1).
 *
 * The hit parameters take the descriptor's hit flags, bit 0 of the shot's id
 * byte as flag A, and flag B from the matching-row search, which also runs with
 * bit 1 of that byte as its enable and raises 0x20 in the flags. The damage
 * value is either the plain actor value for the factor or, with descriptor bit
 * 8, the scaled row values (flag 0x200, and 0x400 when descriptor bit 9 is
 * set). A shot past its first hit only tests once its age reaches 0x3000.
 *
 * The early exit is a bare `return;` in an int function: the ROM leaves r0
 * untouched there (the last callee's result) and hands the hit resolver's
 * result back otherwise, which is what the original evidently did.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022ShotDesc */
struct ShotDesc {
    u32 nFlags;                      /* 0x00 */
    int nHitKind;                    /* 0x04 */
    u8 pad08[4];
    int nRadius;                     /* 0x0c */
    u8 pad10[0x1c];
    struct VecFx32 vecHitOffset;     /* 0x2c */
    u32 nHitFlags;                   /* 0x38 */
    u8 pad3c[4];
    int nRadiusPhase4;               /* 0x40 */
    int nFactorPhase4;               /* 0x44 */
};

/* Ov022Shot */
struct Shot {
    u8 nFlags;                       /* 0x000 */
    u8 pad001;
    s8 nState;                       /* 0x002 */
    u8 pad003;
    int nAge;                        /* 0x004 */
    u8 nOwner;                       /* 0x008 */
    s8 nId0;                         /* 0x009 */
    u8 nId1;                         /* 0x00a */
    u8 nId2;                         /* 0x00b */
    int nFuse;                       /* 0x00c */
    u8 pad010[0x124];
    s8 nField134;                    /* 0x134 */
    u8 pad135[3];
    struct ShotDesc *pDesc;          /* 0x138 */
    short aHitIds[8];                /* 0x13c */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[8];
    void *pShooter;                  /* 0x08 */
};

/* Ov022ActionQuery: a cast from a point along a direction */
struct ActionQuery {
    struct VecFx32 vecPos;           /* 0x00 */
    int nRadius;                     /* 0x0c */
    u32 nGroup;                      /* 0x10 */
    struct VecFx32 vecDir;           /* 0x14 */
    int nConeLimit;                  /* 0x20 */
    short *pHitIds;                  /* 0x24 */
    int nField28;                    /* 0x28 */
};

/* Ov022SegmentQuery: a test along the segment between two points */
struct SegmentQuery {
    struct VecFx32 vecPos;           /* 0x00 */
    struct VecFx32 vecEnd;           /* 0x0c */
    u32 nGroup;                      /* 0x18 */
    int nRadius;                     /* 0x1c */
    short *pHitIds;                  /* 0x20 */
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
    u8 bFlagA : 1;                   /* 0x25 */
    u8 bFlagB : 1;
    u8 nRest25 : 6;
    u8 pad26[2];
};

#define STATE_PHASE4 4
#define DESC_PHASE4_FACTOR 0x800
#define DESC_ROW_VALUES 0x100
#define DESC_ROW_FLAG 0x200
#define HIT_KIND_CAST 0
#define HIT_KIND_SEGMENT 1
#define FX32_ONE 0x1000
#define PARAM_FLAG_ROW 0x20
#define PARAM_FLAG_SCALED 0x200
#define PARAM_FLAG_400 0x400
#define FIRST_HIT_AGE 0x3000

extern void VEC_Add(struct VecFx32 *a, struct VecFx32 *b, struct VecFx32 *pOut);
extern u16 FX_Atan2(int x, int z);
extern int func_ov022_020a22f0(void *pActor, int bEnabled, int *pMatchMask,
                               u8 *pAmount);
extern int func_ov022_020a1f84(void *pActor, int nFactor, int nLevel, int bEnabled);
extern void func_ov022_020a23a4(void *pActor, int nFactor, int *pValue, int *pOther);
extern int func_ov022_020911a8(struct ReactionCtx *pCtx, struct ShotDesc *pDesc,
                               void *pQuery, struct ActionParams *pParams);

int func_ov022_02090f5c(struct ReactionCtx *pCtx, struct Shot *pShot,
                        struct VecFx32 *pPos, struct VecFx32 *pDelta)
{
    struct SegmentQuery seg;
    struct ActionQuery cast;
    struct ActionParams params;
    void *pShooter;
    struct ShotDesc *pDesc;
    int nRadius;
    int nFactor;
    void *pQuery;
    int bRow;
    int nRow;

    pDesc = pShot->pDesc;
    pShooter = pCtx->pShooter;
    nRadius = pDesc->nRadius;
    nFactor = pShot->nFuse;
    if (pShot->nState == STATE_PHASE4) {
        nRadius = pDesc->nRadiusPhase4;
        if ((pDesc->nFlags & DESC_PHASE4_FACTOR) != 0) {
            nFactor = pDesc->nFactorPhase4;
        }
    }
    switch (pDesc->nHitKind) {
    case HIT_KIND_SEGMENT:
        seg.vecPos = *pPos;
        VEC_Add(pPos, pDelta, &seg.vecEnd);
        seg.pHitIds = pShot->aHitIds;
        seg.nRadius = nRadius;
        seg.nGroup = pShot->nOwner;
        seg.nField24 = 0;
        if (pShot->nField134 == 1) {
            seg.nField24 |= 1;
        }
        pQuery = &seg;
        break;
    case HIT_KIND_CAST:
        cast.vecPos = *pPos;
        cast.vecDir = *pDelta;
        cast.nRadius = nRadius;
        cast.nGroup = pShot->nOwner;
        cast.nConeLimit = FX32_ONE;
        cast.nField28 = 0;
        cast.pHitIds = pShot->aHitIds;
        if (pShot->nField134 == 1) {
            cast.nField28 |= 1;
        }
        pQuery = &cast;
        break;
    }
    FX_Atan2(pDelta->x, pDelta->z);
    bRow = 0;
    params.nField08 = pDesc->nHitFlags;
    params.bFlagA = 0;
    if ((pShot->nId2 & 1) != 0) {
        params.bFlagA = 1;
    }
    if ((pShot->nId2 & 2) != 0) {
        bRow = 1;
        params.nField08 |= PARAM_FLAG_ROW;
    }
    params.nField0c = 0;
    params.nLevel = 0;
    nRow = func_ov022_020a22f0(pShooter, bRow, &params.nField0c, &params.nLevel);
    params.bFlagB = (u8)nRow;
    params.vecField14 = pDesc->vecHitOffset;
    params.nField20 = 0;
    if ((pDesc->nFlags & DESC_ROW_VALUES) == 0) {
        params.nValue = func_ov022_020a1f84(pShooter, nFactor, params.nLevel, bRow);
        params.nField04 = 0;
    } else {
        params.nField08 |= PARAM_FLAG_SCALED;
        func_ov022_020a23a4(pShooter, nFactor, &params.nValue, &params.nField04);
        if ((pDesc->nFlags & DESC_ROW_FLAG) != 0) {
            params.nField08 |= PARAM_FLAG_400;
        }
    }
    if (pShot->nField134 != 0 && pShot->nAge < FIRST_HIT_AGE) {
        return;
    }
    return func_ov022_020911a8(pCtx, pDesc, pQuery, &params);
}
