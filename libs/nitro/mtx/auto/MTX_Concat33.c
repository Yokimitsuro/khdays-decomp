typedef signed long fx32;
typedef signed long long fx64;

typedef struct MtxFx33 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
} MtxFx33;

void MTX_Concat33(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *ab)
{
    MtxFx33 tmp;
    MtxFx33 *p;
    register fx32 x, y, z;
    register fx32 xx, yy, zz;

    if (ab == b) {
        p = &tmp;
    } else {
        p = ab;
    }

    x = a->_00;
    y = a->_01;
    z = a->_02;
    p->_00 = (fx32)(((fx64)x * b->_00 + (fx64)y * b->_10 + (fx64)z * b->_20) >> 12);
    p->_01 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21) >> 12);
    xx = b->_02;
    yy = b->_12;
    zz = b->_22;
    p->_02 = (fx32)(((fx64)x * xx + (fx64)y * yy + (fx64)z * zz) >> 12);

    x = a->_10;
    y = a->_11;
    z = a->_12;
    p->_12 = (fx32)(((fx64)x * xx + (fx64)y * yy + (fx64)z * zz) >> 12);
    p->_11 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21) >> 12);
    xx = b->_00;
    yy = b->_10;
    zz = b->_20;
    p->_10 = (fx32)(((fx64)x * xx + (fx64)y * yy + (fx64)z * zz) >> 12);

    x = a->_20;
    y = a->_21;
    z = a->_22;
    p->_20 = (fx32)(((fx64)x * xx + (fx64)y * yy + (fx64)z * zz) >> 12);
    p->_21 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21) >> 12);
    p->_22 = (fx32)(((fx64)x * b->_02 + (fx64)y * b->_12 + (fx64)z * b->_22) >> 12);

    if (p == &tmp) {
        *ab = tmp;
    }
}
