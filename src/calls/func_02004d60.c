/*
 * Builds a perspective 4x4 projection matrix (the NitroSDK MTX_PerspectiveW
 * shape: a vertical-FOV perspective whose w row is scaled by scaleW). Direct
 * sibling of func_02004eac, the frustum form, and written from it -- see that
 * file for the full explanation of the pipelined hardware-divider idiom, the
 * 64-bit fixed-point rounding, and the scaleW rescale through func_020201b8.
 *
 * Identified by behavior, not by name: the argument list, the cotangent divide,
 * the -scaleW in _23 and the zero cells all agree with pret/pokediamond's matched
 * arm9/lib/NitroSDK/src/GX_g3_util.c (G3i_PerspectiveW_), which is the same SDK
 * routine with the load-to-hardware path still present. This copy has no load
 * path and takes 7 arguments, so it is the MTX_ form, not the G3i_ one. The
 * statement ORDER differs from that reference (the two divides are pipelined the
 * other way round here); this file follows OUR disassembly.
 *
 * Verified byte-exact against this ROM: 332 bytes, 4 relocs.
 */
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef s32 fx32;
typedef s64 fx64c;

/* The symbol named FX_Inv in this tree is really the two-argument divide: every
 * existing caller externs it with (numerator, denominator). Its own one-argument
 * definition in libs/nitro/fx/calls/FX_Inv.c is the known, pre-existing
 * FX_Inv/FX_Div arity disagreement, not something introduced here. */
extern fx32 FX_Inv(fx32 numerator, fx32 denominator);
extern fx64c func_01ff8ab0(void);
extern fx64c func_020201b8(fx64c numerator, fx64c denom);
extern fx32 FX_GetDivResult(void);

typedef struct {
    fx32 _00, _01, _02, _03;
    fx32 _10, _11, _12, _13;
    fx32 _20, _21, _22, _23;
    fx32 _30, _31, _32, _33;
} MtxFx44;

/* NUMER/DENOM are poked directly; DIVCNT is deliberately not rewritten because
 * the preceding divide already left it in 64/32 mode. Same spelling as
 * func_02004eac.c's copy of CP_SetDivImm64_64_NS_. */
static inline void CP_SetDivImm64_64_NS_(u64 numerator, u64 denominator)
{
    *(u64 *)0x04000290 = numerator;
    *(u64 *)0x04000298 = denominator;
}

static inline fx32 RoundFx64cToFx32(u64 v)
{
    return (fx32)((v + 0x80000000ULL) >> 32);
}

static inline fx32 FX_Mul(fx32 a, fx32 b)
{
    return (fx32)(((fx64c)a * b + 0x800) >> 12);
}

void func_02004d60(fx32 fovySin, fx32 fovyCos, fx32 aspect, fx32 near, fx32 far,
                   fx32 scaleW, MtxFx44 *mtx)
{
    fx64c recipDepth;
    fx32 fovCot;

    fovCot = FX_Inv(fovyCos, fovySin);
    CP_SetDivImm64_64_NS_((u64)0x1000 << 32, (u64)(u32)(near - far));
    if (scaleW != 0x1000)
        fovCot = (fovCot * scaleW) / 0x1000;

    mtx->_01 = 0;
    mtx->_02 = 0;
    mtx->_03 = 0;
    mtx->_10 = 0;
    mtx->_11 = fovCot;
    mtx->_12 = 0;
    mtx->_13 = 0;
    mtx->_20 = 0;
    mtx->_21 = 0;
    mtx->_23 = -scaleW;
    mtx->_30 = 0;
    mtx->_31 = 0;
    mtx->_33 = 0;

    recipDepth = func_01ff8ab0();
    CP_SetDivImm64_64_NS_((u64)fovCot << 32, (u64)(u32)aspect);
    if (scaleW != 0x1000)
        recipDepth = func_020201b8(recipDepth * scaleW, 0x1000);

    mtx->_22 = RoundFx64cToFx32((u64)(recipDepth * (far + near)));
    mtx->_32 = RoundFx64cToFx32((u64)(recipDepth * FX_Mul(near * 2, far)));
    mtx->_00 = FX_GetDivResult();
}
