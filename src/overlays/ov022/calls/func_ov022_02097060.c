/* ov022: drop a point onto a segment and report whatever the caller asked for.
 *
 * The answer is the position along the segment, as a fraction: the point's
 * offset from the start projected on the segment, divided by the segment's own
 * squared length. A segment of no length gives zero rather than a division.
 *
 * The fraction is not clamped, so a point beyond either end gives a value
 * outside zero to one and the foot of the perpendicular lands off the segment.
 *
 * Three outputs are all optional and each is skipped when its pointer is null:
 * the foot itself, the distance from the point to it, and the unit direction
 * between them. The last argument picks which way round that direction runs.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct VecFx32 {
    int x;
    int y;
    int z;
};

extern void VEC_Subtract(const struct VecFx32 *pA, const struct VecFx32 *pB,
                         struct VecFx32 *pOut);
extern int VEC_DotProduct(const struct VecFx32 *pA, const struct VecFx32 *pB);
extern int VEC_Mag(const struct VecFx32 *pA);
extern void VEC_MultAdd(int nFactor, const struct VecFx32 *pStep,
                        const struct VecFx32 *pFrom, struct VecFx32 *pOut);
/* the tree's name for the fixed-point divide; it takes the numerator and the
 * denominator, not a single value to invert */
extern int FX_Inv(int nNum, int nDen);
/* VEC_Normalize */
extern int func_01ff8d18(const struct VecFx32 *pSrc, struct VecFx32 *pDst);

int func_ov022_02097060(struct VecFx32 *pOutFoot, int *pOutDist,
                        struct VecFx32 *pOutDir, const struct VecFx32 *pPoint,
                        const struct VecFx32 *pFrom, const struct VecFx32 *pTo,
                        int bFromPoint)
{
    struct VecFx32 vecSeg;
    struct VecFx32 vecFoot;
    struct VecFx32 vecDelta;
    int nAlong;
    int nLen2;

    VEC_Subtract(pTo, pFrom, &vecSeg);
    nAlong = VEC_DotProduct(pPoint, &vecSeg) - VEC_DotProduct(pFrom, &vecSeg);
    nLen2 = VEC_DotProduct(&vecSeg, &vecSeg);
    if (nLen2 == 0) {
        nAlong = 0;
    } else {
        nAlong = FX_Inv(nAlong, nLen2);
    }
    VEC_MultAdd(nAlong, &vecSeg, pFrom, &vecFoot);
    if (bFromPoint != 0) {
        VEC_Subtract(pPoint, &vecFoot, &vecDelta);
    } else {
        VEC_Subtract(&vecFoot, pPoint, &vecDelta);
    }
    if (pOutFoot != 0) {
        *pOutFoot = vecFoot;
    }
    if (pOutDist != 0) {
        *pOutDist = VEC_Mag(&vecDelta);
    }
    if (pOutDir != 0) {
        func_01ff8d18(&vecDelta, pOutDir);
    }
    return nAlong;
}
