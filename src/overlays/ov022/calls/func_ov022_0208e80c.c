/* Ov022_SettlePointOnGround -- find where a move actually ends up.
 *
 * The move is cast first: anything solid in the way stops it short of the
 * contact by the caster's own radius, and a surface tagged as pass-through is
 * ignored so the move runs its full length through it.
 *
 * Whatever point that leaves is then dropped onto the ground: it is lifted a
 * little, a long downward cast looks for the floor, and the point settles on
 * whatever it finds. With no floor under it the lift is simply taken back.
 */

typedef unsigned char u8;
typedef unsigned short u16;

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct CollCastParams {
    struct VecFx32 *pOrigin;         /* 0x00 */
    struct VecFx32 *pDir;            /* 0x04 */
    int nRadius;                     /* 0x08 */
    u16 wDirIsUnit;                  /* 0x0c */
    u16 wFlagE;                      /* 0x0e */
    void *pExtra;                    /* 0x10 */
};

struct HitInfo {
    u8 pad00[0x80];
    u8 aSurfaceSlots[4];             /* 0x80 */
};

struct Hit {
    void *pModel;                    /* 0x00 */
    struct HitInfo *pInfo;           /* 0x04 */
    void *pState;                    /* 0x08 */
    int nNearestHit;                 /* 0x0c */
};

struct CollSurfaceAttr {
    u8 pad00[0xc];
    u8 aTags[4];                     /* 0x0c */
};

struct ActorNode;

/* Ov022Actor */
struct Actor {
    u8 pad0000[0x20];
    struct ActorNode *pNode;         /* 0x0020 */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0x58];
    struct Actor *pActor;            /* 0x58 */
};

extern struct Hit *func_0202c248(u16 nGroup, struct CollCastParams *pCast);
extern struct Hit *func_0202c208(u16 nGroup, struct CollCastParams *pCast);
extern struct CollSurfaceAttr *func_0202c37c(struct Hit *pHit, unsigned int nSlot);
extern void func_01ffd0e8(int nScale, struct VecFx32 *pDir, struct VecFx32 *pBase,
                          struct VecFx32 *pOut);
extern void VEC_Add(struct VecFx32 *pA, struct VecFx32 *pB, struct VecFx32 *pOut);

#define CAST_FLAGS 0xf
#define SURFACE_PASS_THROUGH 2
#define SURFACE_SLOTS 4
#define GROUND_LIFT 0x14000
#define GROUND_REACH 0x28000

void func_ov022_0208e80c(struct VecFx32 *pOut, struct ReactionCtx *pCtx,
                         struct VecFx32 *pOrigin, struct VecFx32 *pDir,
                         int nRadius, unsigned int nGroup)
{
    struct VecFx32 vecAt;
    struct VecFx32 vecDrop;
    struct CollCastParams cast;
    struct Actor *pActor;
    int nSlot;
    int bStopped;
    struct Hit *pHit;
    struct CollSurfaceAttr *pAttr;

    pActor = pCtx->pActor;
    bStopped = 0;
    cast.wFlagE = CAST_FLAGS;
    cast.pOrigin = pOrigin;
    cast.pDir = pDir;
    cast.wDirIsUnit = 0;
    cast.pExtra = pActor->pNode;
    cast.nRadius = nRadius;
    pHit = func_0202c248(nGroup, &cast);
    if (pHit != 0) {
        nSlot = 0;
        do {
            pAttr = func_0202c37c(pHit, pHit->pInfo->aSurfaceSlots[nSlot]);
            if (pAttr != 0 && pAttr->aTags[0] == SURFACE_PASS_THROUGH) {
                pHit = 0;
                break;
            }
            nSlot++;
        } while (nSlot < SURFACE_SLOTS);
        if (pHit != 0) {
            bStopped = 1;
            func_01ffd0e8(pHit->nNearestHit - nRadius, pDir, pOrigin, &vecAt);
        }
    }
    if (bStopped == 0) {
        VEC_Add(pOrigin, pDir, &vecAt);
    }
    vecAt.y = vecAt.y + GROUND_LIFT;
    vecDrop.x = 0;
    vecDrop.y = -GROUND_REACH;
    vecDrop.z = 0;
    cast.pOrigin = &vecAt;
    cast.wDirIsUnit = 0;
    cast.pDir = &vecDrop;
    cast.wFlagE = CAST_FLAGS;
    cast.pExtra = pActor->pNode;
    pHit = func_0202c208(nGroup, &cast);
    if (pHit != 0) {
        func_01ffd0e8(pHit->nNearestHit, &vecDrop, &vecAt, &vecAt);
    } else {
        vecAt.y = vecAt.y - GROUND_LIFT;
    }
    *pOut = vecAt;
}
