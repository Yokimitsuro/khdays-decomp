/* ov022: find the ground under a point.
 *
 * Casts straight down from just above the point given and reports where it
 * lands. A surface that carries state of its own is only accepted while that
 * state still belongs to a live piece; anything else is treated as no ground at
 * all. The contact point and the hit itself are both optional outputs, so a
 * caller that only wants to know whether there is ground can pass neither.
 */

typedef unsigned char u8;
typedef unsigned short u16;

#define CAST_FLAGS 0xf
#define CAST_RISE 0x800
#define CAST_REACH 0x8000

struct VecFx32 {
    int x;
    int y;
    int z;
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

struct HitPass {
    u8 pad0000[0x158];
    void *pElement;              /* 0x0158 */
};

struct HitState {
    u8 pad0000[0x28];
    struct HitPass *pOwner;      /* 0x0028 */
};

/* Hit */
struct Hit {
    void *pModel;                /* 0x00 */
    u8 *pInfo;                   /* 0x04 */
    struct HitState *pState;     /* 0x08 */
    int nNearestHit;             /* 0x0c */
};

extern struct Hit *func_0202c208(int nSlotIndex, struct CollCastParams *pQry);
/* func_01ffd0e8 is Vec3ScaleAddQ27; it still carries its address name. */
extern void func_01ffd0e8(int nFactor, struct VecFx32 *pDir,
                          struct VecFx32 *pOrigin, struct VecFx32 *pOut);

int func_ov022_02098040(int nSlotIndex, const struct VecFx32 *pvecPos,
                        struct VecFx32 *pvecOut, struct Hit **ppHit)
{
    struct VecFx32 vecOrigin;
    struct VecFx32 vecDir;
    struct VecFx32 vecHit;
    struct CollCastParams qry;
    struct Hit *pHit;

    vecHit = *pvecPos;
    vecOrigin.x = pvecPos->x;
    vecOrigin.y = pvecPos->y + CAST_RISE;
    vecOrigin.z = pvecPos->z;
    vecDir.z = 0;
    vecDir.x = 0;
    vecDir.y = -CAST_REACH;
    qry.pOrigin = &vecOrigin;
    qry.pDir = &vecDir;
    qry.wDirIsUnit = 0;
    qry.wFlagE = CAST_FLAGS;
    qry.pExtra = 0;
    pHit = func_0202c208((u16)nSlotIndex, &qry);
    if (pHit != 0) {
        if (pHit->pState != 0 && pHit->pState->pOwner->pElement == 0) {
            return 0;
        }
        func_01ffd0e8(pHit->nNearestHit, &vecDir, &vecOrigin, &vecHit);
        if (pvecOut != 0) {
            *pvecOut = vecHit;
        }
        if (ppHit != 0) {
            *ppHit = pHit;
        }
        return 1;
    }
    return 0;
}
