/* ov022: fold an external push into the actor's step.
 *
 * Reads the push vector the actor is currently subject to, drops its downward
 * component while grounded, and adds it to the step. If the combined step and
 * the push are both longer than one unit the push is renormalised first, so a
 * strong push cannot stack without bound, and one input mode scales it down.
 * Only the horizontal part is committed.
 */

typedef unsigned char u8;
typedef unsigned int u32;

struct Vec3 {
    int x, y, z;
};

struct Actor {
    unsigned long long nFlags;   /* 0x000 */
    u8 pad008[0x1c];
    u32 nInputMask;              /* 0x024 */
    u8 pad028[0x470];
    struct Vec3 vecStep;         /* 0x498 */
    u8 pad4a4[0x1c];
    struct Vec3 *pPush;          /* 0x4c0 */
};

extern int VEC_Mag(const struct Vec3 *pVec);
extern void VEC_Add(const struct Vec3 *pA, const struct Vec3 *pB,
                    struct Vec3 *pOut);
extern void func_01ff8d18(const struct Vec3 *pIn, struct Vec3 *pOut);
extern void func_01ffa724(int nScale, const struct Vec3 *pIn,
                          struct Vec3 *pOut);

void func_ov022_0209a264(struct Actor *pActor)
{
    struct Vec3 vecPush;
    struct Vec3 vecSum;
    struct Vec3 vecFlat;

    if ((pActor->nFlags & (1ULL << 7)) != 0) {
        return;
    }
    if (pActor->pPush == 0) {
        return;
    }
    vecPush = *pActor->pPush;
    vecSum = pActor->vecStep;
    if ((pActor->nFlags & (1ULL << 10)) != 0) {
        return;
    }
    if (VEC_Mag(&vecPush) <= 0) {
        return;
    }
    if ((pActor->nInputMask & 4) != 0 && vecPush.y < 0) {
        vecPush.y = 0;
    }
    VEC_Add(&vecPush, &vecSum, &vecSum);
    if (VEC_Mag(&vecSum) > 0x1000 && VEC_Mag(&vecPush) > 0x1000) {
        func_01ff8d18(&vecPush, &vecPush);
    }
    if ((pActor->nInputMask & 2) != 0) {
        func_01ffa724(0x333, &vecPush, &vecPush);
    }
    vecFlat = vecPush;
    vecFlat.y = 0;
    VEC_Add(&pActor->vecStep, &vecFlat, &pActor->vecStep);
}
