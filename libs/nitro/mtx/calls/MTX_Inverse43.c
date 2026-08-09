typedef signed long fx32;
typedef signed long long fx64;

typedef struct MtxFx43 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
    fx32 _30, _31, _32;
} MtxFx43;

extern void FX_InvAsync(fx32 x);
extern fx32 FX_GetDivResult(void);
extern void MI_Copy48B(const void *src, void *dst);

int MTX_Inverse43(const MtxFx43 *src, MtxFx43 *dst)
{
    MtxFx43 tmp;
    MtxFx43 *p;
    fx32 det;
    fx32 det00, det10, det20;
    fx32 tmp01, tmp02, tmp11, tmp12;
    fx32 tmp21, tmp22;

    if (src == dst) {
        p = &tmp;
    } else {
        p = dst;
    }

    det00 = (fx32)(((fx64)src->_11 * src->_22 -
                    (fx64)src->_12 * src->_21 + (fx64)(0x1000 >> 1)) >> 12);

    det10 = (fx32)(((fx64)src->_10 * src->_22 -
                    (fx64)src->_12 * src->_20 + (fx64)(0x1000 >> 1)) >> 12);

    det20 = (fx32)(((fx64)src->_10 * src->_21 -
                    (fx64)src->_11 * src->_20 + (fx64)(0x1000 >> 1)) >> 12);

    det = (fx32)(((fx64)src->_00 * det00 -
                  (fx64)src->_01 * det10 +
                  (fx64)src->_02 * det20 + (fx64)(0x1000 >> 1)) >> 12);

    if (0 == det) {
        return -1;
    }

    FX_InvAsync(det);

    tmp01 = (fx32)(((fx64)src->_01 * src->_22 - (fx64)src->_21 * src->_02) >> 12);
    tmp02 = (fx32)(((fx64)src->_01 * src->_12 - (fx64)src->_11 * src->_02) >> 12);
    tmp11 = (fx32)(((fx64)src->_00 * src->_22 - (fx64)src->_20 * src->_02) >> 12);
    tmp12 = (fx32)(((fx64)src->_00 * src->_12 - (fx64)src->_10 * src->_02) >> 12);

    det = FX_GetDivResult();
    p->_00 = (fx32)(((fx64)det * det00) >> 12);
    p->_01 = -(fx32)(((fx64)det * tmp01) >> 12);
    p->_02 = (fx32)(((fx64)det * tmp02) >> 12);

    p->_10 = -(fx32)(((fx64)det * det10) >> 12);
    p->_11 = (fx32)(((fx64)det * tmp11) >> 12);
    p->_12 = -(fx32)(((fx64)det * tmp12) >> 12);

    p->_20 = (fx32)(((fx64)det * det20) >> 12);

    tmp21 = (fx32)(((fx64)src->_00 * src->_21 - (fx64)src->_20 * src->_01) >> 12);
    p->_21 = -(fx32)(((fx64)det * tmp21) >> 12);

    tmp22 = (fx32)(((fx64)src->_00 * src->_11 - (fx64)src->_10 * src->_01) >> 12);
    p->_22 = (fx32)(((fx64)det * tmp22) >> 12);

    p->_30 = -(fx32)(((fx64)p->_00 * src->_30 +
                      (fx64)p->_10 * src->_31 + (fx64)p->_20 * src->_32) >> 12);

    p->_31 = -(fx32)(((fx64)p->_01 * src->_30 +
                      (fx64)p->_11 * src->_31 + (fx64)p->_21 * src->_32) >> 12);

    p->_32 = -(fx32)(((fx64)p->_02 * src->_30 +
                      (fx64)p->_12 * src->_31 + (fx64)p->_22 * src->_32) >> 12);

    if (p == &tmp) {
        MI_Copy48B(&tmp, dst);
    }

    return 0;
}
