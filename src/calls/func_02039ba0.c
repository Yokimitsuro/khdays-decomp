/* func_02039ba0 -- do two oriented boxes intersect, MAIN. Eberly's (Magic Software) separating axis
 * test in fixed point: the three axes of each box and, unless some pair of axes is parallel (a
 * |cos| above the cutoff 0xffff), the nine cross products. A box is a centre, three unit axes and
 * three half extents. Returns 1 when no axis separates the boxes. */
typedef int fx32;
typedef long long fx64;

typedef struct { fx32 x, y, z; } VecFx32;

typedef struct Box {
    VecFx32 center;                     /* +0x00 */
    VecFx32 axis[3];                    /* +0x0c */
    fx32 extent[3];                     /* +0x30 */
} Box;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

#define BOX_CUTOFF 0xffff

static inline fx32 FX_Mul(fx32 v1, fx32 v2)
{
    return (fx32)(((fx64)v1 * v2 + 0x800) >> 12);
}

static inline fx32 FX_Abs(fx32 v)
{
    return v < 0 ? -v : v;
}

int func_02039ba0(const Box *box0, const Box *box1)
{
    const VecFx32 *A = box0->axis;
    const VecFx32 *B = box1->axis;
    const fx32 *EA = box0->extent;
    const fx32 *EB = box1->extent;
    int bParallel = 0;
    long i;
    VecFx32 D;
    fx32 C[3][3];
    fx32 absC[3][3];
    fx32 AD[3];
    fx32 fR0;
    fx32 fR1;
    fx32 fR;
    fx32 fR01;

    VEC_Subtract(&box1->center, &box0->center, &D);

    /* axis A0 */
    for (i = 0; i < 3; i++) {
        C[0][i] = VEC_DotProduct(&A[0], &B[i]);
        absC[0][i] = FX_Abs(C[0][i]);
        if (absC[0][i] > BOX_CUTOFF) {
            bParallel = 1;
        }
    }
    AD[0] = VEC_DotProduct(&A[0], &D);
    fR = FX_Abs(AD[0]);
    fR1 = FX_Mul(EB[0], absC[0][0]) + FX_Mul(EB[1], absC[0][1]) + FX_Mul(EB[2], absC[0][2]);
    fR01 = EA[0] + fR1;
    if (fR > fR01) {
        return 0;
    }

    /* axis A1 */
    for (i = 0; i < 3; i++) {
        C[1][i] = VEC_DotProduct(&A[1], &B[i]);
        absC[1][i] = FX_Abs(C[1][i]);
        if (absC[1][i] > BOX_CUTOFF) {
            bParallel = 1;
        }
    }
    AD[1] = VEC_DotProduct(&A[1], &D);
    fR = FX_Abs(AD[1]);
    fR1 = FX_Mul(EB[0], absC[1][0]) + FX_Mul(EB[1], absC[1][1]) + FX_Mul(EB[2], absC[1][2]);
    fR01 = EA[1] + fR1;
    if (fR > fR01) {
        return 0;
    }

    /* axis A2 */
    for (i = 0; i < 3; i++) {
        C[2][i] = VEC_DotProduct(&A[2], &B[i]);
        absC[2][i] = FX_Abs(C[2][i]);
        if (absC[2][i] > BOX_CUTOFF) {
            bParallel = 1;
        }
    }
    AD[2] = VEC_DotProduct(&A[2], &D);
    fR = FX_Abs(AD[2]);
    fR1 = FX_Mul(EB[0], absC[2][0]) + FX_Mul(EB[1], absC[2][1]) + FX_Mul(EB[2], absC[2][2]);
    fR01 = EA[2] + fR1;
    if (fR > fR01) {
        return 0;
    }

    /* axis B0 */
    fR = FX_Abs(VEC_DotProduct(&B[0], &D));
    fR0 = FX_Mul(EA[0], absC[0][0]) + FX_Mul(EA[1], absC[1][0]) + FX_Mul(EA[2], absC[2][0]);
    fR01 = fR0 + EB[0];
    if (fR > fR01) {
        return 0;
    }

    /* axis B1 */
    fR = FX_Abs(VEC_DotProduct(&B[1], &D));
    fR0 = FX_Mul(EA[0], absC[0][1]) + FX_Mul(EA[1], absC[1][1]) + FX_Mul(EA[2], absC[2][1]);
    fR01 = fR0 + EB[1];
    if (fR > fR01) {
        return 0;
    }

    /* axis B2 */
    fR = FX_Abs(VEC_DotProduct(&B[2], &D));
    fR0 = FX_Mul(EA[0], absC[0][2]) + FX_Mul(EA[1], absC[1][2]) + FX_Mul(EA[2], absC[2][2]);
    fR01 = fR0 + EB[2];
    if (fR > fR01) {
        return 0;
    }

    /* with a parallel pair the edge axes add nothing */
    if (bParallel) {
        return 1;
    }

    /* axis A0 x B0 */
    fR = FX_Abs(FX_Mul(AD[2], C[1][0]) - FX_Mul(AD[1], C[2][0]));
    fR0 = FX_Mul(EA[1], absC[2][0]) + FX_Mul(EA[2], absC[1][0]);
    fR1 = FX_Mul(EB[1], absC[0][2]) + FX_Mul(EB[2], absC[0][1]);
    fR01 = fR0 + fR1;
    if (fR > fR01) {
        return 0;
    }

    /* axis A0 x B1 */
    fR = FX_Abs(FX_Mul(AD[2], C[1][1]) - FX_Mul(AD[1], C[2][1]));
    fR0 = FX_Mul(EA[1], absC[2][1]) + FX_Mul(EA[2], absC[1][1]);
    fR1 = FX_Mul(EB[0], absC[0][2]) + FX_Mul(EB[2], absC[0][0]);
    fR01 = fR0 + fR1;
    if (fR > fR01) {
        return 0;
    }

    /* axis A0 x B2 */
    fR = FX_Abs(FX_Mul(AD[2], C[1][2]) - FX_Mul(AD[1], C[2][2]));
    fR0 = FX_Mul(EA[1], absC[2][2]) + FX_Mul(EA[2], absC[1][2]);
    fR1 = FX_Mul(EB[0], absC[0][1]) + FX_Mul(EB[1], absC[0][0]);
    fR01 = fR0 + fR1;
    if (fR > fR01) {
        return 0;
    }

    /* axis A1 x B0 */
    fR = FX_Abs(FX_Mul(AD[0], C[2][0]) - FX_Mul(AD[2], C[0][0]));
    fR0 = FX_Mul(EA[0], absC[2][0]) + FX_Mul(EA[2], absC[0][0]);
    fR1 = FX_Mul(EB[1], absC[1][2]) + FX_Mul(EB[2], absC[1][1]);
    fR01 = fR0 + fR1;
    if (fR > fR01) {
        return 0;
    }

    /* axis A1 x B1 */
    fR = FX_Abs(FX_Mul(AD[0], C[2][1]) - FX_Mul(AD[2], C[0][1]));
    fR0 = FX_Mul(EA[0], absC[2][1]) + FX_Mul(EA[2], absC[0][1]);
    fR1 = FX_Mul(EB[0], absC[1][2]) + FX_Mul(EB[2], absC[1][0]);
    fR01 = fR0 + fR1;
    if (fR > fR01) {
        return 0;
    }

    /* axis A1 x B2 */
    fR = FX_Abs(FX_Mul(AD[0], C[2][2]) - FX_Mul(AD[2], C[0][2]));
    fR0 = FX_Mul(EA[0], absC[2][2]) + FX_Mul(EA[2], absC[0][2]);
    fR1 = FX_Mul(EB[0], absC[1][1]) + FX_Mul(EB[1], absC[1][0]);
    fR01 = fR0 + fR1;
    if (fR > fR01) {
        return 0;
    }

    /* axis A2 x B0 */
    fR = FX_Abs(FX_Mul(AD[1], C[0][0]) - FX_Mul(AD[0], C[1][0]));
    fR0 = FX_Mul(EA[0], absC[1][0]) + FX_Mul(EA[1], absC[0][0]);
    fR1 = FX_Mul(EB[1], absC[2][2]) + FX_Mul(EB[2], absC[2][1]);
    fR01 = fR0 + fR1;
    if (fR > fR01) {
        return 0;
    }

    /* axis A2 x B1 */
    fR = FX_Abs(FX_Mul(AD[1], C[0][1]) - FX_Mul(AD[0], C[1][1]));
    fR0 = FX_Mul(EA[0], absC[1][1]) + FX_Mul(EA[1], absC[0][1]);
    fR1 = FX_Mul(EB[0], absC[2][2]) + FX_Mul(EB[2], absC[2][0]);
    fR01 = fR0 + fR1;
    if (fR > fR01) {
        return 0;
    }

    /* axis A2 x B2 */
    fR = FX_Abs(FX_Mul(AD[1], C[0][2]) - FX_Mul(AD[0], C[1][2]));
    fR0 = FX_Mul(EA[0], absC[1][2]) + FX_Mul(EA[1], absC[0][2]);
    fR1 = FX_Mul(EB[0], absC[2][1]) + FX_Mul(EB[1], absC[2][0]);
    fR01 = fR0 + fR1;
    if (fR > fR01) {
        return 0;
    }
    return 1;
}
