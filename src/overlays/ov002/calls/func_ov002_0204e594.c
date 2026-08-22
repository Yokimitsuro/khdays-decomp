typedef unsigned char u8;

typedef struct {
    int x, y, z;
} VecFx32;

extern void NNSi_FndGetCurrentRootHeap(void);
/* out = origin + t * disp, in fx32. */
extern void func_01ffd0e8(int t, const VecFx32 *disp, const VecFx32 *origin,
                          VecFx32 *out);
/* Surface attribute record for one slot id of a hit, or 0. */
extern int func_0202c37c(void *hit, int slotId);
/* Distance between two points, through the hardware square root. */
extern int func_01ff8e94(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd(int k, const VecFx32 *a, const VecFx32 *b,
                        VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Mag(const VecFx32 *v);

/* Resolve one collision-cast hit against the pass-through attribute.
 *
 * Probes surface attribute slots 1 and 2 of the hit face; pHit[1], the hit info
 * record, carries the slot ids at +0x80. If either names a surface whose four
 * attribute tags contain 5, the cast is meant to continue through it: the
 * contact owner from the hit state, pHit[2] + 0x28, is published into
 * *ppPassOwner so the caller's next cast excludes it, the origin is walked
 * forward to the contact point -- plus one sphere radius, 0x500, when the
 * surface has no owner -- and the remaining displacement is shrunk to match.
 * Returns 0, and the caller re-casts.
 *
 * Returns 1 when no pass-through tag was found, which makes the hit final.
 *
 * bSphereCast is 1 from the sphere-cast wrapper and 0 from the ray-cast one,
 * but both arms hold the same code; the branch survives in the ROM with equal
 * sides.
 *
 * The pDisp and pOrigin copies are not decoration: they are what makes mwcc home
 * the two vector arguments the way the ROM does. So is writing bPassed after the
 * store rather than before it, which settles the order of the two zero hoists.
 */
int func_ov002_0204e594(void *bSphereCast, int *pHit, void *pUnusedPos,
                        VecFx32 *pUnitDir, VecFx32 *pDispParam,
                        VecFx32 *pOriginParam, void *pUnusedMotion,
                        VecFx32 *pHitPos, int *ppPassOwner)
{
    VecFx32 *pDisp;
    VecFx32 *pOrigin;
    int bPassed;
    int nSlot;
    int nTag;
    int nSlotId;
    int nAttr;
    int nDist;

    pDisp = pDispParam;
    pOrigin = pOriginParam;
    NNSi_FndGetCurrentRootHeap();
    if (pHit != 0) {
    bPassed = 0;
    func_01ffd0e8(pHit[3], pDisp, pOrigin, pHitPos);

    for (nSlot = 1; nSlot < 3; nSlot++) {
        nSlotId = 0xff;
        if (bSphereCast != 0) {
            if (pHit[1] != 0) {
                nSlotId = *(u8 *)(pHit[1] + nSlot + 0x80);
            }
        } else {
            if (pHit[1] != 0) {
                nSlotId = *(u8 *)(pHit[1] + nSlot + 0x80);
            }
        }
        nAttr = func_0202c37c(pHit, nSlotId);
        if (nAttr != 0) {
            for (nTag = 0; nTag < 4; nTag++) {
                if (*(u8 *)(nAttr + nTag + 0x0c) == 5) {
                    if (pHit[2] != 0) {
                        *ppPassOwner = *(int *)(pHit[2] + 0x28);
                    } else {
                        *ppPassOwner = 0;
                    }
                    bPassed = 1;
                    break;
                }
            }
        }
        if (bPassed) {
            break;
        }
    }

    if (!bPassed) {
        return 1;
    }

    nDist = func_01ff8e94(pOrigin, pHitPos);
    if (*ppPassOwner == 0) {
        nDist += 0x500;
    }
    VEC_Add(pOrigin, pDisp, pDisp);
    VEC_MultAdd(nDist, pUnitDir, pOrigin, pOrigin);
    VEC_Subtract(pDisp, pOrigin, pDisp);
    VEC_Mag(pDisp);
        return 0;
    }
    return 0;
}
