/* Per-tick facing update for the ov130 chaser. Acquires the current target and
   records it; if there is none the tick does nothing. Otherwise it takes the
   unit vector from the node's position to the target and the unit vector from
   the owner's anchor to that position, weights the two by how far along the
   run the node already is, and stores the atan2 of the blended direction as
   the new facing angle. */

typedef struct { int nX, nY, nZ; } VecFx32;

struct ChaseNode {
    char *pSelf;        /* 0x00 */
    char pad04[4];
    char *pTarget;      /* 0x08 */
    char pad0c[8];
    VecFx32 *pPos;      /* 0x14 */
    char pad18[16];
    int nFacing28;      /* 0x28 */
};

struct SpinState {
    char *pActor;               /* 0x00 */
    struct ChaseNode *pChase;   /* 0x04 */
};

extern char *func_ov107_020cab14(char *pSelf, int nFlags);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *pOut);
extern int func_01ff8d18(const VecFx32 *v, VecFx32 *pOut);
extern long long func_01ff8a14(int nNum, int nDen);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *pOut);
extern int func_020050b4(int nX, int nZ);

void func_ov130_020cc5b8(struct SpinState *pState)
{
    struct ChaseNode *nd;
    VecFx32 vToTarget;
    VecFx32 vFromAnchor;
    VecFx32 vBlend;
    int nNear;
    int nFar;
    long long qNear;
    long long qFar;

    nd = pState->pChase;
    nd->pTarget = func_ov107_020cab14(nd->pSelf, 0);
    if (nd->pTarget == 0) {
        return;
    }

    VEC_Subtract(nd->pPos, (const VecFx32 *)(nd->pTarget + 0x74), &vToTarget);
    nNear = func_01ff8d18(&vToTarget, &vToTarget);
    VEC_Subtract((const VecFx32 *)(nd->pSelf + 0x190), nd->pPos, &vFromAnchor);
    nFar = func_01ff8d18(&vFromAnchor, &vFromAnchor);

    qNear = func_01ff8a14(nNear, nNear + nFar);
    qFar = 0x100000000LL - qNear;

    vToTarget.nX = (int)(((qNear * (long long)vToTarget.nX) + 0x80000000LL) >> 32);
    vToTarget.nY = (int)(((qNear * (long long)vToTarget.nY) + 0x80000000LL) >> 32);
    vToTarget.nZ = (int)(((qNear * (long long)vToTarget.nZ) + 0x80000000LL) >> 32);
    vFromAnchor.nX = (int)(((qFar * (long long)vFromAnchor.nX) + 0x80000000LL) >> 32);
    vFromAnchor.nY = (int)(((qFar * (long long)vFromAnchor.nY) + 0x80000000LL) >> 32);
    vFromAnchor.nZ = (int)(((qFar * (long long)vFromAnchor.nZ) + 0x80000000LL) >> 32);

    VEC_Add(&vToTarget, &vFromAnchor, &vBlend);
    func_01ff8d18(&vBlend, &vBlend);
    nd->nFacing28 = func_020050b4(vBlend.nX, vBlend.nZ);
}
