/* ov022: cast a part's move against the world and report what stopped it.
 *
 * Three casts in order, each skipped once one of them has landed. They share a
 * single parameter block: every one starts at the move's own position and is
 * aimed by the direction copy the pass ahead of it rewrites. What comes back is
 * a fraction along the cast, which the placement call turns into the contact
 * point the mover reads afterwards.
 *
 * Straight along the move is the first. A surface carrying no state of its own
 * is accepted only once none of its four tags resolves to the blocking kind.
 *
 * The second aims the same move down by the probe's drop, and keeps the surface
 * only when its normal has real vertical to it: a normal lying almost flat in
 * the horizontal plane belongs to a vertical wall, and this pass wants ground.
 *
 * The third casts straight down by the drop plus the move's own vertical.
 *
 * Both later passes throw their answer away when the contact lands on the wrong
 * side of where the move started, and the third leaves the contact in place
 * even so -- only its answer is dropped.
 *
 * The result is which cast landed, or zero.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define CAST_FLAGS 0xf
#define GROUND_BAND 0x100
#define BLOCKING 2

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* the block the mover fills before asking */
struct MoveProbe {
    struct VecFx32 vecPos;       /* 0x00 */
    struct VecFx32 vecDir;       /* 0x0c */
    int nRadius;                 /* 0x18 */
    int nDrop;                   /* 0x1c */
    int nSlotIndex;              /* 0x20 */
    struct VecFx32 vecHit;       /* 0x24 */
};

/* CollCastParams */
struct CollCastParams {
    struct VecFx32 *pOrigin;     /* 0x00 */
    struct VecFx32 *pDir;        /* 0x04 */
    int nRadius;                 /* 0x08 */
    u16 wDirIsUnit;              /* 0x0c */
    u16 wFlagE;                  /* 0x0e */
    void *pExtra;                /* 0x10 */
};

/* Hit */
struct Hit {
    void *pModel;                /* 0x00 */
    u8 *pInfo;                   /* 0x04 */
    void *pState;                /* 0x08 */
    int nNearestHit;             /* 0x0c */
};

/* CollSurfaceAttr */
struct CollSurfaceAttr {
    u8 pad00[0xc];
    u8 aTags[4];                 /* 0x0c */
    u8 pad10[4];
};

struct ReactionCtx;

extern struct Hit *func_0202c248(int nSlotIndex, struct CollCastParams *pQry);
extern struct Hit *func_0202c208(int nSlotIndex, struct CollCastParams *pQry);
extern struct Hit *func_0202c228(int nSlotIndex, struct CollCastParams *pQry);
extern struct CollSurfaceAttr *func_0202c37c(struct Hit *pHit, int nTag);
extern void func_02028d74(void *pModel, u8 *pFace, struct VecFx32 *pOut);
/* func_01ff8d18 is VEC_Normalize and func_01ffd0e8 is Vec3ScaleAddQ27; both
 * still carry their address names in the tree's symbol table. */
extern int func_01ff8d18(struct VecFx32 *pSrc, struct VecFx32 *pDst);
extern void func_01ffd0e8(int nFactor, struct VecFx32 *pDir,
                          struct VecFx32 *pOrigin, struct VecFx32 *pOut);

int func_ov022_0208aa28(struct ReactionCtx *pCtx, struct MoveProbe *pProbe)
{
    struct VecFx32 vecDir;
    struct VecFx32 vecNormal;
    struct CollCastParams qry;
    int nRet;
    struct Hit *pHit;
    struct CollSurfaceAttr *pAttr;
    int nDrop;
    int i;

    vecDir = pProbe->vecDir;
    nRet = 0;
    qry.nRadius = pProbe->nRadius;
    qry.pOrigin = &pProbe->vecPos;
    qry.pDir = &vecDir;
    qry.wDirIsUnit = 0;
    qry.pExtra = 0;
    qry.wFlagE = CAST_FLAGS;
    pHit = func_0202c248((u16)pProbe->nSlotIndex, &qry);
    if (pHit != 0) {
        if (pHit->pState == 0) {
            for (i = 0; i < 4; i++) {
                pAttr = func_0202c37c(pHit, pHit->pInfo[i + 0x80]);
                if (pAttr != 0 && pAttr->aTags[0] == BLOCKING) {
                    pHit = 0;
                    break;
                }
            }
        }
        if (pHit != 0) {
            func_01ffd0e8(pHit->nNearestHit, &pProbe->vecDir, &pProbe->vecPos,
                          &pProbe->vecHit);
            nRet = 1;
        }
    }
    if (pHit == 0) {
        vecDir = pProbe->vecDir;
        vecDir.y = vecDir.y - pProbe->nDrop;
        pHit = func_0202c208((u16)pProbe->nSlotIndex, &qry);
        if (pHit != 0) {
            func_02028d74(pHit->pModel, pHit->pInfo + 0x14, &vecNormal);
            func_01ff8d18(&vecNormal, &vecNormal);
            if (vecNormal.y >= GROUND_BAND || vecNormal.y <= -GROUND_BAND) {
                nRet = 2;
                func_01ffd0e8(pHit->nNearestHit, &vecDir, &pProbe->vecPos,
                              &pProbe->vecHit);
                if (pProbe->vecHit.y > pProbe->vecPos.y) {
                    nRet = 0;
                    pHit = 0;
                }
            } else {
                pHit = 0;
            }
        }
    }
    if (pHit == 0) {
        nDrop = pProbe->nDrop;
        vecDir.y = nDrop;
        vecDir.x = 0;
        vecDir.z = 0;
        vecDir.y = nDrop + pProbe->vecDir.y;
        pHit = func_0202c228((u16)pProbe->nSlotIndex, &qry);
        if (pHit != 0) {
            nRet = 3;
            func_01ffd0e8(pHit->nNearestHit, &vecDir, &pProbe->vecPos,
                              &pProbe->vecHit);
            if (pProbe->vecHit.y < pProbe->vecPos.y) {
                nRet = 0;
            }
        }
    }
    return nRet;
}
