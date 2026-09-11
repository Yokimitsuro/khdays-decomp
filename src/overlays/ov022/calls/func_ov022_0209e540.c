/* Ov022_SweepFanOverParts -- test a horizontal fan against every part of every
 * entry the actor's sub-object tracks.
 *
 * Without a sub-object and its entry table nothing is tested. The fan's axis
 * is normalised and flattened once. Every entry of the table that the hit-id
 * filter lets through has its active parts tested: the flattened direction to
 * the part must make at least the fan's spread with the axis, and the part's
 * shape must meet the sphere of the fan's reach about its apex.
 *
 * Any hit answers yes. Only the local player reports one: the contact is
 * turned into a hit record and applied; when that lands as a fresh hit on a
 * part further than the reach plus a unit and a half, the actor's impact point
 * is left one reach along the way to it. The entry's id then goes into the
 * first free slot of the hit-id list and no more of its parts are tested.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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
};

/* Ov107SweepQuery */
struct SweepQuery {
    VecFx32 vecCentre;           /* 0x00 */
    int nRadius;                 /* 0x0c */
};

/* Ov107Shape: only the anchor position is read here */
struct Shape {
    u8 pad00[4];
    VecFx32 vecPos;              /* 0x04 */
};

/* Ov022PartNode */
struct PartNode {
    struct Shape *pShape;        /* 0x00 */
    u8 pad04[4];
    u32 nFlags : 8;              /* 0x08 bit 0: active */
    u32 nRest : 24;
};

/* Ov022HitEntry */
struct Entry {
    u8 pad000[2];
    u16 nId;                     /* 0x002 */
    u8 pad004[0x228];
    u8 listParts[4];             /* 0x22c */
};

/* Ov022EntryTable */
struct EntryTable {
    u8 pad00[0x80];
    u8 listEntries[4];           /* 0x80 */
};

/* Ov022ActorSub */
struct ActorSub {
    u8 pad00[4];
    struct EntryTable *pTable;   /* 0x04 */
};

struct HitRecord {
    VecFx32 vecPos;              /* 0x00 */
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[0x4ec];
    struct ActorSub *pSub;       /* 0x04ec */
    u8 pad04f0[0x21d4];
    u8 nHitState;                /* 0x26c4 */
    u8 pad26c5[3];
    VecFx32 vecImpact;           /* 0x26c8 */
};

extern int VEC_Mag(VecFx32 *pVec);
extern void func_01ff8d18(VecFx32 *pSrc, VecFx32 *pDst);   /* VEC_Normalize */
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_01ff8e94(VecFx32 *pA, VecFx32 *pB);         /* VEC_Distance */
extern int VEC_DotProduct(VecFx32 *pA, VecFx32 *pB);
extern void VEC_MultAdd(int nScale, VecFx32 *pVec, VecFx32 *pBase, VecFx32 *pOut);
extern struct Entry **func_01fffd70(void *pList);            /* List_First */
extern struct PartNode *func_01fffd8c(void *pList);          /* List_Next */
extern struct Entry *func_ov022_0209ea44(struct Entry *pEntry, short *pHitIds,
                                         void *pCtx);
extern int func_ov107_020c3504(struct Shape *pShape, struct SweepQuery *pQuery,
                               VecFx32 *pOut);
extern int func_02030788(void);
extern void func_ov022_020a1118(struct HitRecord *pHit, void *pCtx,
                                VecFx32 *pContact, VecFx32 *pPoint,
                                VecFx32 *pDir);
extern int func_ov022_020a1330(struct Actor *pActor, void *pCtx,
                               struct Entry *pEntry, struct PartNode *pNode,
                               struct HitRecord *pHit);

#define PART_ACTIVE 0x1
#define HIT_FRESH 1
#define HIT_ID_FREE (-1)
#define HIT_ID_SLOTS 8
#define IMPACT_MARGIN 0x1800

int func_ov022_0209e540(struct Actor *pActor, struct FanQuery *pFan, void *pCtx)
{
    VecFx32 vecToPoint;
    VecFx32 vecAxis;
    struct HitRecord hit;
    VecFx32 vecContact;
    struct SweepQuery query;
    int bHit;
    int nCosMin;
    struct EntryTable *pTable;
    int bOk;
    struct Entry **ppEntry;
    struct Entry *pEntry;
    struct Entry *pUsable;
    struct PartNode *pNode;
    int bDone;
    int nSlot;
    short *pIds;

    bHit = 0;
    bOk = 1;
    if (pActor->pSub == 0) {
        bOk = 0;
    }
    pTable = pActor->pSub->pTable;
    if (pTable == 0) {
        bOk = 0;
    }
    if (bOk == 0) {
        return 0;
    }
    nCosMin = -pFan->nCosSpread;
    vecAxis = pFan->vecDir;
    if (VEC_Mag(&vecAxis) != 0) {
        func_01ff8d18(&vecAxis, &vecAxis);
    }
    vecAxis.y = 0;
    ppEntry = func_01fffd70(pTable->listEntries);
    pEntry = ppEntry == 0 ? 0 : *ppEntry;
    while (pEntry != 0) {
        bDone = 0;
        pUsable = func_ov022_0209ea44(pEntry, pFan->pHitIds, pCtx);
        if (pUsable != 0) {
            pNode = (struct PartNode *)func_01fffd70(pUsable->listParts);
            while (pNode != 0) {
                if (bDone) {
                    break;
                }
                if (pNode != 0 && (pNode->nFlags & PART_ACTIVE) != 0) {
                    query.vecCentre = pFan->vecOrigin;
                    query.nRadius = pFan->nRadius;
                    VEC_Subtract(&pNode->pShape->vecPos, &pFan->vecOrigin, &vecToPoint);
                    if (VEC_Mag(&vecToPoint) != 0) {
                        func_01ff8d18(&vecToPoint, &vecToPoint);
                    }
                    vecToPoint.y = 0;
                    if (VEC_DotProduct(&vecToPoint, &vecAxis) >= nCosMin
                        && func_ov107_020c3504(pNode->pShape, &query, &vecContact) != 0) {
                        bHit = 1;
                        if (func_02030788() == 0 && pCtx != 0) {
                            func_ov022_020a1118(&hit, pCtx, &pFan->vecOrigin,
                                                &pNode->pShape->vecPos, &pFan->vecDir);
                            if (func_ov022_020a1330(pActor, pCtx, pEntry, pNode, &hit) != 0) {
                                if (pActor->nHitState == HIT_FRESH
                                    && func_01ff8e94(&pFan->vecOrigin, &pNode->pShape->vecPos)
                                           >= pFan->nRadius + IMPACT_MARGIN) {
                                    VEC_Subtract(&pNode->pShape->vecPos, &pFan->vecOrigin,
                                                 &vecToPoint);
                                    if (VEC_Mag(&vecToPoint) != 0) {
                                        func_01ff8d18(&vecToPoint, &vecToPoint);
                                    }
                                    VEC_MultAdd(pFan->nRadius, &vecToPoint, &pFan->vecOrigin,
                                                &pActor->vecImpact);
                                }
                                pIds = pFan->pHitIds;
                                if (pIds != 0) {
                                    for (nSlot = 0; nSlot < HIT_ID_SLOTS; nSlot++) {
                                        if (pIds[nSlot] == HIT_ID_FREE) {
                                            bDone = 1;
                                            pIds[nSlot] = pEntry->nId;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                pNode = func_01fffd8c(pUsable->listParts);
            }
        }
        ppEntry = (struct Entry **)func_01fffd8c(pTable->listEntries);
        pEntry = ppEntry == 0 ? 0 : *ppEntry;
    }
    return bHit;
}
