/* Ov022_ResolveShotHit -- run a shot's hit test and act on what it hit.
 *
 * The facing is the angle of the delta. A miss, a descriptor with bit 3, or
 * an actor with no hit state only does something when the actor's hit state
 * is 4: unless the descriptor has bit 6 it marshals record 1 at the impact
 * point (record 5 with the shot's id when the shot carries a second id), and
 * the shot is retired either way.
 *
 * On a hit the shot retires unless the descriptor has bit 2. Then the actor's
 * hit result decides: bit 0 marshals record 1 (unless descriptor bit 2 or the
 * shot has no id); bits 3 or 4 marshal record 7 for bit 4 only; otherwise a
 * shot with an id marshals record 0 with it (plus record 2 when hit result
 * bit 1 is set, and the actor's state bit 3 is raised) or record 5 when it has
 * a second id, and a descriptor with bit 10 spawns its slot at the impact
 * point.
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
    u8 pad04[0x44];
    short nSpawnHandler;             /* 0x48 */
    short nSpawnCue;                 /* 0x4a */
};

/* Ov022Shot */
struct Shot {
    u8 nFlags;                       /* 0x000 */
    u8 pad001;
    s8 nState;                       /* 0x002 */
    u8 pad003[6];
    s8 nId0;                         /* 0x009 */
    s8 nId1;                         /* 0x00a */
    u8 pad00b[0x12d];
    struct ShotDesc *pDesc;          /* 0x138 */
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[0x910];
    u32 nStateFlags;                 /* 0x0910 */
    u8 pad0914[0x1da8];
    u32 nHitResult;                  /* 0x26bc */
    u8 pad26c0[4];
    u8 nHitState;                    /* 0x26c4 */
    u8 pad26c5[3];
    struct VecFx32 vecImpact;        /* 0x26c8 */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[8];
    struct Actor *pShooter;          /* 0x08 */
};

#define DESC_NO_HIT 0x8
#define DESC_KEEP 0x2
#define DESC_NO_MISS_RECORD 0x40
#define DESC_SPAWN 0x400
#define HIT_STATE_MISSED 4
#define RESULT_BIT0 0x1
#define RESULT_BIT1 0x2
#define RESULT_BITS34 0x18
#define RESULT_BIT4 0x10
#define STATE_RETIRED 3
#define FX32_ONE 0x1000

extern int func_ov022_02090f5c(struct ReactionCtx *pCtx, struct Shot *pShot,
                               struct VecFx32 *pPos, struct VecFx32 *pDelta);
extern int FX_Atan2(int x, int z);
extern void func_ov022_020ad208(struct Actor *pActor, int nKind,
                                struct VecFx32 *pAt, int nScale, u16 nAngle,
                                int nArg);
extern void func_ov022_020b0e3c(u32 *pStateFlags);
extern void func_02033d0c(int nHandlerId, int nCue, struct VecFx32 *pPos,
                          int nFlags);

void func_ov022_02091b48(struct ReactionCtx *pCtx, struct Shot *pShot,
                         struct VecFx32 *pPos, struct VecFx32 *pDelta)
{
    struct Actor *pShooter;
    struct ShotDesc *pDesc;
    int bHit;
    u16 nAngle;
    u32 nResult;
    int nId;

    pShooter = pCtx->pShooter;
    pDesc = pShot->pDesc;
    bHit = func_ov022_02090f5c(pCtx, pShot, pPos, pDelta);
    nAngle = FX_Atan2(pDelta->x, pDelta->z);
    if (bHit != 0 && (pDesc->nFlags & DESC_NO_HIT) == 0 && pShooter->nHitState != 0) {
        if ((pDesc->nFlags & DESC_KEEP) == 0) {
            pShot->nState = STATE_RETIRED;
        }
        nResult = pShooter->nHitResult;
        if ((nResult & RESULT_BIT0) != 0) {
            if ((pDesc->nFlags & DESC_KEEP) != 0) {
                return;
            }
            if (pShot->nId0 < 0) {
                return;
            }
            func_ov022_020ad208(pShooter, 1, &pShooter->vecImpact, FX32_ONE, nAngle, 0);
            return;
        }
        if ((nResult & RESULT_BITS34) == 0) {
            nId = pShot->nId0;
            if (nId >= 0) {
                if (pShot->nId1 == 0) {
                    func_ov022_020ad208(pShooter, 0, &pShooter->vecImpact, FX32_ONE, nAngle,
                                        nId);
                    if ((pShooter->nHitResult & RESULT_BIT1) != 0) {
                        func_ov022_020ad208(pShooter, 2, &pShooter->vecImpact, FX32_ONE,
                                            nAngle, 0);
                    }
                    func_ov022_020b0e3c(&pShooter->nStateFlags);
                } else {
                    func_ov022_020ad208(pShooter, 5, &pShooter->vecImpact, FX32_ONE, nAngle,
                                        nId);
                }
            }
            if ((pDesc->nFlags & DESC_SPAWN) != 0) {
                func_02033d0c(pDesc->nSpawnHandler, pDesc->nSpawnCue, &pShooter->vecImpact,
                              0);
            }
        } else if ((nResult & RESULT_BIT4) != 0) {
            func_ov022_020ad208(pShooter, 7, &pShooter->vecImpact, FX32_ONE, nAngle, 0);
        }
    } else if (pShooter->nHitState == HIT_STATE_MISSED) {
        if ((pDesc->nFlags & DESC_NO_MISS_RECORD) == 0) {
            if (pShot->nId1 == 0) {
                func_ov022_020ad208(pShooter, 1, &pShooter->vecImpact, FX32_ONE, nAngle, 0);
            } else {
                func_ov022_020ad208(pShooter, 5, &pShooter->vecImpact, FX32_ONE, nAngle,
                                    pShot->nId0);
            }
        }
        pShot->nState = STATE_RETIRED;
    }
}
