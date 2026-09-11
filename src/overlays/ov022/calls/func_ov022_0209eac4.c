/* Ov022_SweepFanOverEntries -- test a horizontal fan against every active
 * entry.
 *
 * Outside a live session the hit context must be open; inside one it must be
 * open or the actor must carry flag bit 12. The fan's axis is normalised and
 * flattened once and its tip (apex plus direction) taken as the centre: every
 * entry but the actor's own (unless the fan says self-hits count) is looked
 * up against the fan's group and hit-id list, its point fetched, and it counts
 * when it lies within the reach plus its own reach of the tip and the
 * flattened direction from the tip to it makes at least the spread with the
 * axis.
 *
 * Any hit answers yes. With a context the contact is turned into a hit
 * record and applied, and the entry's id (shifted into the high bits) is
 * written into the first free slot of the hit-id list.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* Ov022FanQuery */
struct FanQuery {
    VecFx32 vecOrigin;           /* 0x00 */
    int nRadius;                 /* 0x0c */
    int nGroup;                  /* 0x10 */
    VecFx32 vecDir;              /* 0x14 */
    int nCosSpread;              /* 0x20 */
    short *pHitIds;              /* 0x24 eight slots, -1 free */
    u32 nFlags;                  /* 0x28 bit 0: self hits count */
};

/* Ov022SweepHit */
struct SweepHit {
    u8 pad00[8];
    int nFlags;                  /* 0x08 bit 6: open to contact; signed so the > 0 test
                                    compiles to and/cmp/bgt */
};

struct HitRecord {
    VecFx32 vecPos;              /* 0x00 */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x4ba];
    int nReach;                  /* 0x04c4 */
};

#define HIT_OPEN 0x40
#define FLAG_BIT12 (1ULL << 12)
#define FAN_SELF 0x1
#define HIT_ID_FREE (-1)
#define HIT_ID_SLOTS 8
#define HIT_ID_SHIFT 11
#define FLAG_SET(nFlags, nBit) (((nFlags) & (nBit)) > 0)

extern int func_02030670(void);
extern int VEC_Mag(VecFx32 *pVec);
extern void func_01ff8d18(VecFx32 *pSrc, VecFx32 *pDst);   /* VEC_Normalize */
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_01ff8e94(VecFx32 *pA, VecFx32 *pB);         /* VEC_Distance */
extern int VEC_DotProduct(VecFx32 *pA, VecFx32 *pB);
extern int func_ov022_020882f8(void);
extern struct Actor *func_ov022_0209ee54(struct Actor *pActor, int nEntry, int nGroup,
                                         short *pHitIds);
extern void func_ov022_020ad44c(VecFx32 *pOut, struct Actor *pEntry);
extern void func_ov022_020a1118(struct HitRecord *pHit, struct SweepHit *pCtx,
                                VecFx32 *pContact, VecFx32 *pPoint, VecFx32 *pDir);
extern void func_ov022_020a1870(struct Actor *pActor, struct SweepHit *pCtx,
                                struct Actor *pEntry, struct HitRecord *pHit);

int func_ov022_0209eac4(struct Actor *pActor, struct FanQuery *pFan, struct SweepHit *pCtx)
{
    VecFx32 vecToPoint;
    VecFx32 vecAxis;
    struct HitRecord hit;
    VecFx32 vecTip;
    VecFx32 vecPoint;
    int nCosMin;
    int bHit;
    struct Actor *pEntry;
    int nEntry;
    int nSlot;
    short *pIds;

    bHit = 0;
    if (func_02030670() == 0) {
        if (!FLAG_SET(pCtx->nFlags, HIT_OPEN)) {
            return 0;
        }
    } else if ((pCtx->nFlags & HIT_OPEN) == 0 && (pActor->nFlags & FLAG_BIT12) == 0) {
        return 0;
    }
    vecAxis = pFan->vecDir;
    if (VEC_Mag(&vecAxis) != 0) {
        func_01ff8d18(&vecAxis, &vecAxis);
    }
    nEntry = 0;
    vecAxis.y = 0;
    nCosMin = -pFan->nCosSpread;
    if (func_ov022_020882f8() > 0) {
        do {
            if (nEntry != pActor->nId || (pFan->nFlags & FAN_SELF) != 0) {
                pEntry = func_ov022_0209ee54(pActor, nEntry, pFan->nGroup, pFan->pHitIds);
                if (pEntry != 0) {
                    func_ov022_020ad44c(&vecPoint, pEntry);
                    VEC_Add(&pFan->vecOrigin, &pFan->vecDir, &vecTip);
                    if (func_01ff8e94(&vecPoint, &vecTip) <= pFan->nRadius + pEntry->nReach) {
                        VEC_Subtract(&vecPoint, &vecTip, &vecToPoint);
                        if (VEC_Mag(&vecToPoint) != 0) {
                            func_01ff8d18(&vecToPoint, &vecToPoint);
                        }
                        vecToPoint.y = 0;
                        if (VEC_DotProduct(&vecToPoint, &vecAxis) >= nCosMin) {
                            bHit = 1;
                            if (pCtx != 0) {
                                func_ov022_020a1118(&hit, pCtx, &vecTip, &vecPoint,
                                                    &pFan->vecDir);
                                func_ov022_020a1870(pActor, pCtx, pEntry, &hit);
                            }
                            pIds = pFan->pHitIds;
                            if (pIds != 0) {
                                for (nSlot = 0; nSlot < HIT_ID_SLOTS; nSlot++) {
                                    if (pIds[nSlot] == HIT_ID_FREE) {
                                        pIds[nSlot] = pEntry->nId << HIT_ID_SHIFT;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            nEntry++;
        } while (nEntry < func_ov022_020882f8());
    }
    return bHit;
}
