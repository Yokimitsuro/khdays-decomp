typedef unsigned short u16;

typedef struct {
    int x, y, z;
} VecFx32;

typedef struct {
    VecFx32 *pOrigin;   /* +0x00 */
    VecFx32 *pDir;      /* +0x04 */
    int nRadius;        /* +0x08 */
    u16 wDirIsUnit;     /* +0x0c */
    u16 wFlags;         /* +0x0e */
    void *pExclude;     /* +0x10 */
} CollCastParams;       /* 0x14 */

/* Index of the session's local player, or its delegate. */
extern int func_01fffe14(void);
/* Collision world id of that player's track entry, or -1 when it has none. */
extern int func_ov022_02088474(int nPlayer);
/* Base of one track entry group, which is what the cast runs against. */
extern void *func_0202bfa0(int nWorldId);
extern void func_01ff8d18(const VecFx32 *v, VecFx32 *out);   /* normalise */
extern int VEC_Mag(const VecFx32 *v);
extern void func_01ffa724(int k, const VecFx32 *v, VecFx32 *out); /* scale */
/* Sweep one sphere; returns the shared hit record, or 0 when nothing was hit. */
extern int *func_01fff83c(void *pWorld, CollCastParams *pParams);
extern int func_ov002_0204e594(void *bSphereCast, int *pHit, void *pUnusedPos,
                               VecFx32 *pUnitDir, VecFx32 *pDispParam,
                               VecFx32 *pOriginParam, void *pUnusedMotion,
                               VecFx32 *pHitPos, int *ppPassOwner);
/* Surface normal of one face, from its three vertex indices. */
extern void func_02028d74(int nModel, const short *pIndices, VecFx32 *pOut);

/* Sweep a sphere of radius 0x500 from pStart along pMotion and report the first
 * surface it cannot pass through.
 *
 * The sweep shortens the motion by one radius, then casts up to three times.
 * Each hit goes to the pass-through resolver: when that walks the origin past a
 * surface the sweep is meant to ignore, this loops and casts again from the new
 * origin, excluding whatever the resolver named. The first hit the resolver
 * calls final ends the sweep, and its face normal is written to pOutNormal when
 * the caller asked for one.
 *
 * Returns 1 when a final hit was found, 0 when the sweep ran clear, the player
 * has no collision world, or three casts were not enough.
 *
 * The five stack aggregates are declared in reverse of their frame order: mwcc
 * gives the last one declared the lowest offset. nTry has to lead the scalars to
 * take r6 and leave r7 for the world pointer.
 */
int func_ov002_0204e6e0(VecFx32 *pStart, VecFx32 *pMotion, void *pHitPos,
                        VecFx32 *pOutNormal, void *pExclude)
{
    VecFx32 vOrigin;
    VecFx32 vDisp;
    VecFx32 vUnitDir;
    CollCastParams params;
    VecFx32 vNormal;
    void *pPassOwner;
    int nTry;
    void *pWorld;
    int nPlayer;
    int nWorldId;
    int nLen;
    int *pHit;

    nPlayer = func_01fffe14();
    nWorldId = func_ov022_02088474(nPlayer);
    pWorld = func_0202bfa0((u16)nWorldId);
    vOrigin = *pStart;
    pPassOwner = pExclude;
    if (nPlayer < 0 || nWorldId < 0) {
        return 0;
    }

    if (pOutNormal != 0) {
        pOutNormal->z = 0;
        pOutNormal->y = 0;
        pOutNormal->x = 0;
    }

    func_01ff8d18(pMotion, &vUnitDir);
    nLen = VEC_Mag(pMotion);
    func_01ffa724(nLen - 0x500, &vUnitDir, &vDisp);

    for (nTry = 0; nTry < 3; nTry++) {
        params.nRadius = 0x500;
        params.wDirIsUnit = 0;
        params.wFlags = 0xf;
        params.pExclude = pPassOwner;
        params.pOrigin = &vOrigin;
        params.pDir = &vDisp;
        pHit = func_01fff83c(pWorld, &params);
        if (pHit == 0) {
            return 0;
        }
        if (func_ov002_0204e594((void *)1, pHit, pStart, &vUnitDir, &vDisp,
                                &vOrigin, pMotion, pHitPos,
                                (int *)&pPassOwner) != 0) {
            if (pOutNormal != 0 && pHit[1] != 0) {
                func_02028d74(pHit[0], (const short *)(pHit[1] + 0x14),
                              &vNormal);
                func_01ff8d18(&vNormal, &vNormal);
                *pOutNormal = vNormal;
            }
            return 1;
        }
    }
    return 0;
}
