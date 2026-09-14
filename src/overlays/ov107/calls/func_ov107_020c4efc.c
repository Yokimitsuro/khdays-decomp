/* Applies a mutual separation push between two AiState creatures A and B along
   a shared delta vector, weighted by each side's "field_54" magnitude. If
   both magnitudes are zero the push is zero for both. If only one side has a
   nonzero magnitude, that side alone is scaled and the push is discarded
   (reset to zero) when the receiving side's own facing (field_114) already
   opposes it and its gate flag (field_17a bit 1) is set. If both are nonzero,
   the full-factor push is blended between the two sides by the ratio
   field_54_A : field_54_B. Whatever push results is added into each side's
   accumulator (field_16c), each side's counter (field_178) is bumped, and
   each side's flag (field_17a bit 4) is marked. */

typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct AiState {
    char pad000[0x54];
    int field_54;              /* 0x54 */
    char pad058[0x114 - 0x58];
    VecFx32 field_114;         /* 0x114 */
    char pad120[0x16c - 0x120];
    VecFx32 field_16c;         /* 0x16c */
    signed char field_178;     /* 0x178 */
    char pad179[0x17a - 0x179];
    unsigned char field_17a;   /* 0x17a */
} AiState;

extern void func_01ffa724(int factor, const VecFx32 *src, VecFx32 *dst); /* scale */
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern long long func_01ff8a14(int num, int denom); /* fixed-point divide */
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern const VecFx32 data_02041dc8; /* zero vector */

void func_ov107_020c4efc(int nFactor, VecFx32 *pDelta, AiState *pA, AiState *pB)
{
    VecFx32 vPushA = {0, 0, 0};
    VecFx32 vPushB = {0, 0, 0};
    long long qNear;
    long long qFar;

    if (pA->field_54 == 0 && pB->field_54 == 0) {
        VecFx32 vZero = data_02041dc8;
        vPushA = vZero;
        vPushB = vZero;
    } else if (pA->field_54 == 0) {
        func_01ffa724(-nFactor, pDelta, &vPushB);
        if (((unsigned int)pB->field_17a << 30) >> 31) {
            if (VEC_DotProduct(&pB->field_114, &vPushB) < 0) {
                vPushB = data_02041dc8;
            }
        }
    } else if (pB->field_54 == 0) {
        func_01ffa724(nFactor, pDelta, &vPushA);
        if (((unsigned int)pA->field_17a << 30) >> 31) {
            if (VEC_DotProduct(&pA->field_114, &vPushA) < 0) {
                vPushA = data_02041dc8;
            }
        }
    } else {
        qNear = func_01ff8a14(pA->field_54, pA->field_54 + pB->field_54);

        func_01ffa724(nFactor, pDelta, &vPushA);
        qFar = 0x100000000LL - qNear;

        vPushA.x = (int)(((qFar * (long long)vPushA.x) + 0x80000000LL) >> 32);
        vPushA.y = (int)(((qFar * (long long)vPushA.y) + 0x80000000LL) >> 32);
        vPushA.z = (int)(((qFar * (long long)vPushA.z) + 0x80000000LL) >> 32);

        func_01ffa724(-nFactor, pDelta, &vPushB);

        vPushB.x = (int)(((qNear * (long long)vPushB.x) + 0x80000000LL) >> 32);
        vPushB.y = (int)(((qNear * (long long)vPushB.y) + 0x80000000LL) >> 32);
        vPushB.z = (int)(((qNear * (long long)vPushB.z) + 0x80000000LL) >> 32);
    }

    pA->field_17a |= 0x10;
    pB->field_17a |= 0x10;

    VEC_Add(&pA->field_16c, &vPushA, &pA->field_16c);
    pA->field_178 = pA->field_178 + 1;

    VEC_Add(&pB->field_16c, &vPushB, &pB->field_16c);
    pB->field_178 = pB->field_178 + 1;
}
