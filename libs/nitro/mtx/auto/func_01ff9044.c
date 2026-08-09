typedef signed long fx32;
typedef signed long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct MtxFx33 {
    fx32 m[9];
} MtxFx33;

void func_01ff9044(MtxFx33 *dst, const VecFx32 *axis, fx32 sinVal, fx32 cosVal)
{
    fx64 t, ss, cc, xx, yy, zz;
    fx32 t01;
    fx32 s2;

    t = (fx64)(0x1000 - (fx32)cosVal);
    ss = (fx64)sinVal;
    cc = (fx64)cosVal;
    xx = (fx64)axis->x;
    yy = (fx64)axis->y;
    zz = (fx64)axis->z;

    t01 = (fx32)((xx * xx * t) >> 24);
    dst->m[0] = t01 + cosVal;

    t01 = (fx32)((yy * yy * t) >> 24);
    dst->m[4] = t01 + cosVal;

    t01 = (fx32)((zz * zz * t) >> 24);
    dst->m[8] = t01 + cosVal;

    t01 = (fx32)((t * xx * yy) >> 24);
    s2 = (fx32)((ss * zz) >> 12);
    dst->m[1] = t01 + s2;
    dst->m[3] = t01 - s2;

    t01 = (fx32)((t * xx * zz) >> 24);
    s2 = (fx32)((ss * yy) >> 12);
    dst->m[2] = t01 - s2;
    dst->m[6] = t01 + s2;

    t01 = (fx32)((t * yy * zz) >> 24);
    s2 = (fx32)((ss * xx) >> 12);
    dst->m[5] = t01 + s2;
    dst->m[7] = t01 - s2;
}
