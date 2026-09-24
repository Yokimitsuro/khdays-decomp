#pragma thumb on
/* func_0202119c -- build a rotation matrix from X and Y angles, MAIN (THUMB). Starts from identity
 * and concatenates a rotation about X by `angleX`, then one about Y by `angleY` (16-bit angles, sine
 * and cosine from the SDK table). The angles arrive as ints and are cut to 16 bits on entry. */
typedef unsigned short u16;
typedef short fx16;
typedef int fx32;

typedef struct { fx32 _00, _01, _02, _10, _11, _12, _20, _21, _22, _30, _31, _32; } MtxFx43;

extern const fx16 data_0203d210[];      /* FX_SinCosTable_ */
extern void MTX_Identity43_(MtxFx43 *pDst);
extern void MTX_RotX43_(MtxFx43 *pDst, fx32 sinVal, fx32 cosVal);
extern void MTX_RotY43_(MtxFx43 *pDst, fx32 sinVal, fx32 cosVal);
extern void MTX_Concat43(const MtxFx43 *a, const MtxFx43 *b, MtxFx43 *ab);

static inline fx16 FX_SinIdx(int idx)
{
    return data_0203d210[((idx >> 4) << 1)];
}

static inline fx16 FX_CosIdx(int idx)
{
    return data_0203d210[((idx >> 4) << 1) + 1];
}

void func_0202119c(MtxFx43 *m, int angleX, int angleY)
{
    MtxFx43 tmp;

    angleX = (u16)angleX;
    angleY = (u16)angleY;

    MTX_Identity43_(m);
    MTX_Identity43_(&tmp);
    MTX_RotX43_(&tmp, FX_SinIdx(angleX), FX_CosIdx(angleX));
    MTX_Concat43(m, &tmp, m);
    MTX_Identity43_(&tmp);
    MTX_RotY43_(&tmp, FX_SinIdx(angleY), FX_CosIdx(angleY));
    MTX_Concat43(m, &tmp, m);
}
#pragma thumb off
