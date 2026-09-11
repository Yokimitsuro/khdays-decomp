typedef struct {
    char pad_00[0x30];
    int field_30[16];
} Obj30;

extern long long func_01ff8a50(int x);

static inline int Q12Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

static inline int FxMul64(int x, long long y)
{
    return (int)((y * (long long)x + 0x80000000LL) >> 32);
}

/*
 * Pairwise Q12 fixed-point constraint solve over three particle indices into
 * the parallel arrays vel[] (per-particle value being corrected), coef[]
 * (per-particle coefficient) and obj->field_30[] (per-particle limit).
 *
 * For the pair (idxA, idxB) the two overshoots are cross-multiplied by the
 * OTHER particle's coefficient, which compares the two ratios without a
 * divide; the larger side becomes the one pinned to its limit. The pinned
 * side then recomputes a sum-based value and a signed remainder: a negative
 * remainder takes the short path (reciprocal of that one coefficient, applied
 * straight to vel[] and *out1), otherwise the reciprocal of
 * coefA^2 + coefB^2 scales remainder^2 into *out2 and the combined correction
 * into *out1. out1 is optional; out2 is always written.
 *
 * idxC is then handled on its own: vel[idxC] is clamped into
 * [-limit, +limit], accumulating the squared excess into *out2 when it moves.
 *
 * Both branch bodies order their sums by index (the idxA term first), not by
 * which side was pinned, which is what fixes the schedule of the shared
 * prologue. `coef` is a read-only view of the incoming array; declaring it
 * separately is what keeps it out of the parameter block during allocation.
 *
 * The four resolution blocks are mutually exclusive and the compiler places
 * each negative-remainder path out of line after its positive one; the gotos
 * below reproduce that layout, the same way src/calls/func_0202f55c.c does.
 * A plain nested if/else re-shuffles every block and no longer matches.
 */
void func_02038c90(int idxA, int idxB, int idxC, int *vel, int *coefs,
                   Obj30 *obj, int *out1, int *out2)
{
    const int *coef = coefs;
    int targetA = obj->field_30[idxA];
    int targetB = obj->field_30[idxB];
    int deltaA = vel[idxA] - targetA;
    int valA = Q12Mul(coef[idxB], deltaA);
    int deltaB = vel[idxB] - targetB;
    int valB = Q12Mul(coef[idxA], deltaB);
    long long recip;
    int diffA;
    int diffB;
    int sumA;
    int sumB;
    int sumSq;
    int diffSq;
    int total;
    int val, target, d;

    if (valA < valB) {
        goto branchB;
    }

    vel[idxA] = targetA;

    sumB = vel[idxB] + obj->field_30[idxB];
    diffA = valA - Q12Mul(coef[idxA], sumB);
    if (diffA < 0) {
        goto branchA_neg;
    }

    sumSq = Q12Mul(coef[idxA], coef[idxA]) + Q12Mul(coef[idxB], coef[idxB]);
    recip = func_01ff8a50(sumSq);
    diffSq = Q12Mul(diffA, diffA);
    *out2 += FxMul64(diffSq, recip);

    if (out1 != 0) {
        vel[idxB] = -obj->field_30[idxB];
        total = Q12Mul(coef[idxA], deltaA) + Q12Mul(coef[idxB], sumB);
        *out1 = -FxMul64(total, recip);
    }
    goto tail;

branchA_neg:
    if (out1 != 0) {
        recip = func_01ff8a50(coef[idxA]);
        vel[idxB] -= FxMul64(valA, recip);
        *out1 = -FxMul64(deltaA, recip);
    }
    goto tail;

branchB:
    vel[idxB] = targetB;

    sumA = vel[idxA] + obj->field_30[idxA];
    diffB = valB - Q12Mul(coef[idxB], sumA);
    if (diffB < 0) {
        goto branchB_neg;
    }

    sumSq = Q12Mul(coef[idxA], coef[idxA]) + Q12Mul(coef[idxB], coef[idxB]);
    recip = func_01ff8a50(sumSq);
    diffSq = Q12Mul(diffB, diffB);
    *out2 += FxMul64(diffSq, recip);

    if (out1 != 0) {
        vel[idxA] = -obj->field_30[idxA];
        total = Q12Mul(coef[idxA], sumA) + Q12Mul(coef[idxB], deltaB);
        *out1 = -FxMul64(total, recip);
    }
    goto tail;

branchB_neg:
    if (out1 != 0) {
        recip = func_01ff8a50(coef[idxB]);
        vel[idxA] -= FxMul64(valB, recip);
        *out1 = -FxMul64(deltaB, recip);
    }

tail:
    target = obj->field_30[idxC];
    val = vel[idxC];
    if (val < -target) {
        d = val + target;
        *out2 += Q12Mul(d, d);
        vel[idxC] = -obj->field_30[idxC];
    } else if (val <= target) {
        return;
    } else {
        d = val - target;
        *out2 += Q12Mul(d, d);
        vel[idxC] = obj->field_30[idxC];
    }
}
