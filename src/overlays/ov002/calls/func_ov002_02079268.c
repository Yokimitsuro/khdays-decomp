typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* The hit record the caller hands over. The leading byte picks the shape, and
 * what follows the source point is either a radius or a second point. */
typedef struct {
    signed char nShape;             /* +0x00 */
    char pad01[3];
    VecFx32 vFrom;                  /* +0x04 */
    union {
        int nRadius;                /* +0x10, shape 0 */
        VecFx32 vTo;                /* +0x10, shape 1 */
    } u;
} Ov002HitShape;                   /* 0x1c */

extern int func_ov002_0207c7fc(VecFx32 *pFrom, int nRadius, VecFx32 *pAt,
                               int nExtent);
extern int func_ov002_0207c824(VecFx32 *pFrom, VecFx32 *pTo, VecFx32 *pAt,
                               int nExtent);
extern int func_ov002_0207c7dc(VecFx32 *pAt, int nExtent, VecFx32 *pFrom);

/* Test one hit record against a timed element.
 *
 * Only mode 1 is handled; anything else reports -1 so the caller knows the
 * record was not consumed. Shape 0 is a sphere, shape 1 a segment and shape 2
 * a point, each tested against the element's position at +0x1c with the extent
 * at +0x28. The answer is the plain hit/no-hit boolean.
 *
 * The handled mode has to be the taken branch and the three shapes an if/else
 * chain: writing the guard the other way round predicates the tail, and a
 * switch turns the chain into a dispatch.
 */
int func_ov002_02079268(char *pElement, int nMode, Ov002HitShape *pShape)
{
    int nShape;
    int nHit;

    if (nMode == 1) {
        nShape = pShape->nShape;
        nHit = 0;

        if (nShape == 0) {
            nHit = func_ov002_0207c7fc(&pShape->vFrom, pShape->u.nRadius,
                                       (VecFx32 *)(pElement + 0x1c),
                                       *(int *)(pElement + 0x28));
        } else if (nShape == 1) {
            nHit = func_ov002_0207c824(&pShape->vFrom, &pShape->u.vTo,
                                       (VecFx32 *)(pElement + 0x1c),
                                       *(int *)(pElement + 0x28));
        } else if (nShape == 2) {
            nHit = func_ov002_0207c7dc((VecFx32 *)(pElement + 0x1c),
                                       *(int *)(pElement + 0x28),
                                       &pShape->vFrom);
        }

        return nHit != 0;
    }

    return -1;
}
