typedef unsigned short u16;

typedef struct {
    int x, y, z;
} VecFx32;

typedef struct {
    VecFx32 *pOrigin;   /* +0x00 */
    VecFx32 *pDir;      /* +0x04 */
    int nRadius;        /* +0x08, left alone by a ray cast */
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
/* Cast one ray; returns the shared hit record, or 0 when nothing was hit. */
extern int *func_01fff7a4(void *pWorld, CollCastParams *pParams);
extern int func_ov002_0204e594(void *bSphereCast, int *pHit, void *pUnusedPos,
                               VecFx32 *pUnitDir, VecFx32 *pDispParam,
                               VecFx32 *pOriginParam, void *pUnusedMotion,
                               VecFx32 *pHitPos, int *ppPassOwner);
/* Surface normal of one face, from its three vertex indices. */
extern void func_02028d74(int nModel, const short *pIndices, VecFx32 *pOut);

/* Cast a ray from pStart along pMotion and report the first surface it cannot
 * pass through, ignoring anything close to horizontal.
 *
 * The ray twin of the sphere sweep: same three-try loop, same pass-through
 * resolver, but the direction is the caller's motion unshortened and no cast
 * radius is set. The extra rule is the normal filter -- a surface whose normal
 * has a Y component inside +/-0x100 is treated as not worth reporting, so the
 * loop casts again past it rather than answering with it.
 *
 * Returns 1 when a final hit was found, 0 when the ray runs clear, the player
 * has no collision world, or three casts were not enough.
 */
int func_ov002_0204e864(VecFx32 *pStart, VecFx32 *pMotion, void *pHitPos,
                        VecFx32 *pOutNormal, void *pExclude)
{
    VecFx32 vOrigin;
    VecFx32 vDir;
    VecFx32 vUnitDir;
    CollCastParams params;
    VecFx32 vNormal;
    void *pPassOwner;
    int nTry;
    void *pWorld;
    int nPlayer;
    int nWorldId;
    int *pHit;

    nPlayer = func_01fffe14();
    nWorldId = func_ov022_02088474(nPlayer);
    pWorld = func_0202bfa0((u16)nWorldId);
    vOrigin = *pStart;
    pPassOwner = pExclude;
    vDir = *pMotion;
    if (nPlayer < 0 || nWorldId < 0) {
        return 0;
    }

    if (pOutNormal != 0) {
        pOutNormal->z = 0;
        pOutNormal->y = 0;
        pOutNormal->x = 0;
    }

    func_01ff8d18(pMotion, &vUnitDir);

    for (nTry = 0; nTry < 3; nTry++) {
        params.pOrigin = &vOrigin;
        params.pDir = &vDir;
        params.wDirIsUnit = 0;
        params.wFlags = 0xf;
        params.pExclude = pPassOwner;
        pHit = func_01fff7a4(pWorld, &params);
        if (pHit == 0) {
            return 0;
        }
        if (func_ov002_0204e594((void *)0, pHit, pStart, &vUnitDir, &vDir,
                                &vOrigin, pMotion, pHitPos,
                                (int *)&pPassOwner) != 0) {
            if (pOutNormal != 0 && pHit[1] != 0) {
                func_02028d74(pHit[0], (const short *)(pHit[1] + 0x14),
                              &vNormal);
                func_01ff8d18(&vNormal, &vNormal);
                if (vNormal.y < 0x100 && vNormal.y > -0x100) {
                    continue;
                }
                *pOutNormal = vNormal;
            }
            return 1;
        }
    }
    return 0;
}
