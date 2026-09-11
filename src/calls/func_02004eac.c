/*
 * Builds a frustum-style 4x4 projection matrix (the NitroSDK MTX_FrustumW shape:
 * a perspective frustum whose w row is scaled by scaleW).
 *
 * The three reciprocals 1/(right-left), 1/(top-bottom) and 1/(near-far) come off
 * the NDS hardware divider, pipelined: FX_InvAsync kicks the first one and sets
 * DIVCNT's mode, then each result is collected by func_01ff8ab0 (spin on DIVCNT,
 * read the raw 64-bit DIV_RESULT) while the next division is started by writing
 * NUMER/DENOM directly -- DIVCNT is already in the right mode, so re-kicking it
 * would only cost cycles. Same spelling as func_01ffcfd0.c's
 * CP_SetDivImm64_64_NS_, which pokes the same pair of registers.
 *
 * Each raw quotient is a 64-bit fixed-point value with 32 fractional bits. When
 * scaleW is not FX32_ONE it is rescaled by scaleW through the 64-bit divide
 * helper func_020201b8; at FX32_ONE that would be an identity and is skipped.
 *
 * The diagonal terms _00/_11/_22 are the reciprocals shifted up 13 (12 fractional
 * bits, plus the doubling a frustum's 2n/(r-l) form needs) and rounded to fx32 by
 * adding half an lsb and taking the high word. The _30/_31/_32 skew terms reuse
 * the same three reciprocals, multiplied by -(right+left), -(top+bottom) and
 * (far+near), rounded the same way but without the shift. _33 is scaleW; every
 * other cell is zero.
 */

typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef s32 fx32;
typedef s64 fx64c;

extern void FX_InvAsync(fx32 x);
extern fx64c func_01ff8ab0(void);
extern fx64c func_020201b8(fx64c numerator, fx64c denom);

typedef struct {
    fx32 _00, _01, _02, _03;
    fx32 _10, _11, _12, _13;
    fx32 _20, _21, _22, _23;
    fx32 _30, _31, _32, _33;
} MtxFx44;

/* NUMER = FX32_ONE << 32 makes the quotient the fx32 reciprocal of DENOM.
 * DIVCNT is deliberately not rewritten: FX_InvAsync already left it in 64/32 mode. */
static inline void CP_SetDivImm64_64_NS_(u64 numerator, u64 denominator)
{
    *(u64 *)0x04000290 = numerator;
    *(u64 *)0x04000298 = denominator;
}

static inline fx32 RoundFx64cToFx32(u64 v)
{
    return (fx32)((v + 0x80000000ULL) >> 32);
}

void func_02004eac(fx32 top, fx32 bottom, fx32 left, fx32 right, fx32 near, fx32 far,
                   fx32 scaleW, MtxFx44 *mtx)
{
    fx64c recipWidth, recipHeight, recipDepth;

    FX_InvAsync(right - left);

    mtx->_01 = 0;
    mtx->_02 = 0;
    mtx->_03 = 0;
    mtx->_10 = 0;
    mtx->_12 = 0;
    mtx->_13 = 0;
    mtx->_20 = 0;
    mtx->_21 = 0;
    mtx->_23 = 0;
    mtx->_33 = scaleW;

    recipWidth = func_01ff8ab0();
    CP_SetDivImm64_64_NS_((u64)0x1000 << 32, (u64)(u32)(top - bottom));
    if (scaleW != 0x1000)
        recipWidth = func_020201b8(recipWidth * scaleW, 0x1000);
    mtx->_00 = RoundFx64cToFx32((u64)recipWidth << 13);

    recipHeight = func_01ff8ab0();
    CP_SetDivImm64_64_NS_((u64)0x1000 << 32, (u64)(u32)(near - far));
    if (scaleW != 0x1000)
        recipHeight = func_020201b8(recipHeight * scaleW, 0x1000);
    mtx->_11 = RoundFx64cToFx32((u64)recipHeight << 13);

    recipDepth = func_01ff8ab0();
    if (scaleW != 0x1000)
        recipDepth = func_020201b8(recipDepth * scaleW, 0x1000);

    mtx->_22 = RoundFx64cToFx32((u64)recipDepth << 13);
    mtx->_30 = RoundFx64cToFx32((u64)(recipWidth * -(right + left)));
    mtx->_31 = RoundFx64cToFx32((u64)(recipHeight * -(top + bottom)));
    mtx->_32 = RoundFx64cToFx32((u64)(recipDepth * (far + near)));
}
