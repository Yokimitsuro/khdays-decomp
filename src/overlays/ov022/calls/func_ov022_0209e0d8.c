/* ov022: does a point fall within reach of a capsule?
 *
 * The capsule is a segment with a radius. First the closest point on the
 * segment is taken; it counts only when it lands strictly inside the segment
 * and within the two radii added together. Otherwise each end is tried in turn
 * and the first one inside the same reach wins, with its own position handed
 * back as the contact point.
 */

typedef unsigned char u8;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

#define END_COUNT 2
#define SEGMENT_END 0x1000

struct Capsule {
    VecFx32 vecA;                /* 0x00 */
    VecFx32 vecB;                /* 0x0c */
    u8 pad0018[4];
    int nRadius;                 /* 0x1c */
};

extern int func_ov022_02097060(VecFx32 *pOut, int *pnDist, VecFx32 *pSpare,
                               const VecFx32 *pPoint, const VecFx32 *pA,
                               const VecFx32 *pB, int nFlags);
extern int func_01ff8e94(const VecFx32 *pA, const VecFx32 *pB);  /* VEC_Distance */

int func_ov022_0209e0d8(const VecFx32 *pPoint, int nRadius, VecFx32 *pOut,
                        struct Capsule *pCapsule)
{
    VecFx32 *apEnds[END_COUNT];
    /* The copy reads the list through its own pointer. That is load bearing:
     * reading both uses off the array itself keeps the loaded end in a
     * register across the branch and costs the found flag its own. */
    VecFx32 **ppEnds;
    int nDist;
    int nEnd;
    int bHit;
    int bFound;
    int nAlong;

    ppEnds = apEnds;
    apEnds[0] = &pCapsule->vecA;
    apEnds[1] = &pCapsule->vecB;
    bHit = 0;
    nAlong = func_ov022_02097060(pOut, &nDist, 0, pPoint, &pCapsule->vecA,
                                 &pCapsule->vecB, 0);
    if (nAlong > 0 && nAlong < SEGMENT_END
        && nDist <= pCapsule->nRadius + nRadius) {
        bHit = 1;
    }
    if (bHit == 0) {
        bFound = 0;
        for (nEnd = 0; nEnd < END_COUNT; nEnd++) {
            nDist = func_01ff8e94(pPoint, apEnds[nEnd]);
            if (nDist <= pCapsule->nRadius + nRadius) {
                bFound = 1;
                *pOut = *ppEnds[nEnd];
                break;
            }
        }
        if (bFound != 0) {
            bHit = 1;
        }
    }
    return bHit;
}
