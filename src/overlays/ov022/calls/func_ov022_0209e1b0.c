/* Ov022_SweepFanOverGroup -- test a horizontal fan against every member of a
 * group.
 *
 * Nothing is tested while the actor carries the no-contact flag. The fan's
 * axis is taken once, normalised and flattened, and the group named by the
 * query is looked up. Every member that is present and open to contact is
 * kept when it lies within the fan's reach plus its own radius and the
 * flattened direction to it makes at least the fan's spread with the axis.
 *
 * Any hit answers yes. Only the local player reports one: the contact is
 * turned into a hit record and handed on, and a member further than the reach
 * plus a unit and a half leaves the actor's impact point one reach along the
 * way to it.
 */

typedef unsigned char u8;
typedef unsigned short u16;

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
};

/* Ov002Element (only the list link and the flags are used here) */
struct GroupMember {
    u8 pad0000[4];
    struct GroupMember *pNext;   /* 0x04 */
    u8 pad0008[0xa];
    u16 nFlags;                  /* 0x12 */
};

/* Ov022ContactPoint */
struct ContactPoint {
    VecFx32 vecPos;              /* 0x00 */
    int nRadius;                 /* 0x0c */
};

struct HitRecord {
    VecFx32 vecPos;              /* 0x00 */
};

/* Ov022Actor */
struct Actor {
    unsigned int nFlags;         /* 0x0000 */
    u8 pad0004[0x26c4];
    VecFx32 vecImpact;           /* 0x26c8 */
};

extern int VEC_Mag(VecFx32 *pVec);
extern void func_01ff8d18(VecFx32 *pSrc, VecFx32 *pDst);   /* VEC_Normalize */
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_01ff8e94(VecFx32 *pA, VecFx32 *pB);         /* VEC_Distance */
extern int VEC_DotProduct(VecFx32 *pA, VecFx32 *pB);
extern void VEC_MultAdd(int nScale, VecFx32 *pVec, VecFx32 *pBase, VecFx32 *pOut);
extern int func_ov002_02072754(int nGroup);
extern struct GroupMember *func_ov002_02076688(u16 nId);
extern struct ContactPoint *func_ov002_02076d24(struct GroupMember *pMember);
extern int func_02030788(void);
extern void func_ov022_020a1118(struct HitRecord *pHit, void *pCtx,
                                VecFx32 *pContact, struct ContactPoint *pPoint,
                                VecFx32 *pDir);
extern void func_ov022_020a1258(struct Actor *pActor, void *pCtx,
                                struct GroupMember *pMember,
                                struct HitRecord *pHit, int nArg);

#define ACTOR_NO_CONTACT 0x10000
#define MEMBER_OPEN 0x40
#define IMPACT_MARGIN 0x1800

int func_ov022_0209e1b0(struct Actor *pActor, struct FanQuery *pFan, void *pCtx)
{
    VecFx32 vecToPoint;
    VecFx32 vecAxis;
    struct HitRecord hit;
    struct GroupMember *pMember;
    struct ContactPoint *pPoint;
    int nCosMin;
    int bHit;

    bHit = 0;
    if ((pActor->nFlags & ACTOR_NO_CONTACT) != 0) {
        return 0;
    }
    vecAxis = pFan->vecDir;
    if (VEC_Mag(&vecAxis) != 0) {
        func_01ff8d18(&vecAxis, &vecAxis);
    }
    vecAxis.y = 0;
    nCosMin = -pFan->nCosSpread;
    pMember = func_ov002_02076688((u16)func_ov002_02072754(pFan->nGroup));
    if (pMember != 0) {
        do {
            pPoint = func_ov002_02076d24(pMember);
            if (pPoint != 0 && (pMember->nFlags & MEMBER_OPEN) != 0
                && func_01ff8e94(&pPoint->vecPos, &pFan->vecOrigin)
                       <= pFan->nRadius + pPoint->nRadius) {
                VEC_Subtract(&pPoint->vecPos, &pFan->vecOrigin, &vecToPoint);
                if (VEC_Mag(&vecToPoint) != 0) {
                    func_01ff8d18(&vecToPoint, &vecToPoint);
                }
                vecToPoint.y = 0;
                if (VEC_DotProduct(&vecToPoint, &vecAxis) >= nCosMin) {
                    bHit = 1;
                    if (func_02030788() == 0 && pCtx != 0) {
                        func_ov022_020a1118(&hit, pCtx, &pFan->vecOrigin, pPoint,
                                            &pFan->vecDir);
                        func_ov022_020a1258(pActor, pCtx, pMember, &hit, 0);
                        if (func_01ff8e94(&pFan->vecOrigin,
                                         &func_ov002_02076d24(pMember)->vecPos)
                            >= pFan->nRadius + IMPACT_MARGIN) {
                            VEC_Subtract(&func_ov002_02076d24(pMember)->vecPos,
                                         &pFan->vecOrigin, &vecToPoint);
                            if (VEC_Mag(&vecToPoint) != 0) {
                                func_01ff8d18(&vecToPoint, &vecToPoint);
                            }
                            VEC_MultAdd(pFan->nRadius, &vecToPoint, &pFan->vecOrigin,
                                        &pActor->vecImpact);
                        }
                    }
                }
            }
            pMember = pMember->pNext;
        } while (pMember != 0);
    }
    return bHit;
}
