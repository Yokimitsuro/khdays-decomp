typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* The path node this predicate belongs to; it is one of the step functions
 * Ov002_CreateTaskNodePath installs at +0x14. */
typedef struct Ov002TaskNodePath {
    void *pHook0;                       /* +0x00 */
    void *pHook1;                       /* +0x04 */
    void *pHook2;                       /* +0x08 */
    int nThreshold;                     /* +0x0c */
    char pad10[4];
    void *pfnStep;                      /* +0x14 */
    unsigned char bOwner;               /* +0x18 */
    char pad19[1];
    short h1a;                          /* +0x1a */
    short h1c;                          /* +0x1c */
    char pad1e[2];
    int nRadius;                        /* +0x20 */
    int nHeight;                        /* +0x24 */
    int n28;                            /* +0x28 */
    VecFx32 place;                      /* +0x2c */
    char szName[16];                    /* +0x38 */
} Ov002TaskNodePath;

extern int func_01ff8e94(const VecFx32 *pA, const VecFx32 *pB);

/* Is this point inside the node's reach?
 *
 * A negative radius means the node has no bound at all and everything is in.
 * Otherwise the height is checked first, as a signed span: a positive height
 * reaches up from the node's place and a negative one reaches down, so the
 * sign of the offset has to agree with it, and a zero height admits nothing.
 * The radius is then checked flat, both points dropped to y zero before the
 * distance is taken.
 */
int func_ov002_020701b8(Ov002TaskNodePath *pNode, const VecFx32 *pPoint)
{
    VecFx32 vPlace;
    VecFx32 vPoint;
    int nHeight;
    int nOffset;

    if ((pNode->nRadius & 0x80000000) != 0) {
        return 1;
    }

    nOffset = pPoint->y - pNode->place.y;
    nHeight = pNode->nHeight;
    if (nHeight > 0) {
        if (nOffset < 0 || nOffset > nHeight) {
            return 0;
        }
    } else if (nHeight < 0) {
        if (nOffset > 0 || nOffset < nHeight) {
            return 0;
        }
    } else {
        return 0;
    }

    vPlace = pNode->place;
    vPoint = *pPoint;
    vPlace.y = 0;
    vPoint.y = 0;
    return func_01ff8e94(&vPlace, &vPoint) <= pNode->nRadius;
}
