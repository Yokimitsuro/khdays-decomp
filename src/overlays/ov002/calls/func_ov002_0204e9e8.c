typedef unsigned short u16;

typedef struct {
    int x, y, z;
} VecFx32;

/* Index of the session's local player, or its delegate. */
extern int func_01fffe14(void);
/* Collision world id of that player's track entry, or -1 when it has none. */
extern int func_ov022_02088474(int nPlayer);
/* Cast a ray through one world id; returns the shared hit record, or 0. */
extern int *func_0202c2f8(int nWorldId, VecFx32 *pOrigin, VecFx32 *pDir,
                          void *pExclude);
/* out = origin + t * dir, in fx32. */
extern void func_01ffd0e8(int t, const VecFx32 *dir, const VecFx32 *origin,
                          VecFx32 *out);

/* Cast a ray from pOrigin along pDir and write the contact point to pOut.
 *
 * The plain form of the collision query: one cast, no pass-through retry and no
 * normal, just the point where the ray first meets the local player's world.
 * Returns 1 when it hit something, 0 when the ray ran clear or the player has
 * no collision world.
 */
int func_ov002_0204e9e8(VecFx32 *pOrigin, VecFx32 *pDir, VecFx32 *pOut,
                        void *pExclude)
{
    int nPlayer;
    int nWorldId;
    int *pHit;

    nPlayer = func_01fffe14();
    nWorldId = func_ov022_02088474(nPlayer);
    if (nPlayer < 0 || nWorldId < 0) {
        return 0;
    }

    pHit = func_0202c2f8((u16)nWorldId, pOrigin, pDir, pExclude);
    if (pHit == 0) {
        return 0;
    }

    func_01ffd0e8(pHit[3], pDir, pOrigin, pOut);
    return 1;
}
