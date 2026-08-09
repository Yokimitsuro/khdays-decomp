typedef signed long fx32;
typedef signed long long fx64;
typedef signed long long fx64c;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

typedef struct MtxFx44 {
    fx32 _00, _01, _02, _03;
    fx32 _10, _11, _12, _13;
    fx32 _20, _21, _22, _23;
    fx32 _30, _31, _32, _33;
} MtxFx44;

extern void func_02015ca0(int *px1, int *py1, int *px2, int *py2);
extern fx32 FX_Inv(fx32 numerator, fx32 denominator);
extern const MtxFx44 *func_02015c38(void);
extern void FX_InvAsync(fx32 value);
extern fx64c func_01ff8ab0(void);

static inline fx32 FX_Mul32x64c(fx32 x, fx64c y)
{
    return (fx32)((y * (fx64)x + 0x80000000LL) >> 32);
}

int func_020166c4(int px, int py, VecFx32 *pNear, VecFx32 *pFar)
{
    int rval;
    int x1, y1, x2, y2;
    int dx, dy;
    fx32 x, y;
    const MtxFx44 *m;
    VecFx32 vNear, vFar;
    fx64c invWNear, invWFar;
    fx32 wNear, wFar;

    func_02015ca0(&x1, &y1, &x2, &y2);
    dx = x2 - x1;
    dy = y2 - y1;

    x = FX_Inv((px - x1) << 12, dx << 12);
    y = FX_Inv((py + y1 - 191) << 12, -dy << 12);

    if (x < 0 || y < 0 || x > 0x1000 || y > 0x1000) {
        rval = -1;
    } else {
        rval = 0;
    }

    x = (x - 0x800) * 2;
    y = (y - 0x800) * 2;

    m = func_02015c38();

    wNear = m->_33 + (fx32)(((fx64)x * m->_03 + (fx64)y * m->_13) >> 12);
    FX_InvAsync(wNear - m->_23);

    vNear.x = m->_30 + (fx32)(((fx64)x * m->_00 + (fx64)y * m->_10) >> 12);
    vNear.y = m->_31 + (fx32)(((fx64)x * m->_01 + (fx64)y * m->_11) >> 12);
    vNear.z = m->_32 + (fx32)(((fx64)x * m->_02 + (fx64)y * m->_12) >> 12);

    if (pFar) {
        vFar.x = vNear.x + m->_20;
        vFar.y = vNear.y + m->_21;
        vFar.z = vNear.z + m->_22;
        wFar = wNear + m->_23;
    }

    vNear.x -= m->_20;
    vNear.y -= m->_21;
    vNear.z -= m->_22;

    invWNear = func_01ff8ab0();
    if (pFar)
        FX_InvAsync(wFar);

    pNear->x = FX_Mul32x64c(vNear.x, invWNear);
    pNear->y = FX_Mul32x64c(vNear.y, invWNear);
    pNear->z = FX_Mul32x64c(vNear.z, invWNear);

    if (pFar) {
        invWFar = func_01ff8ab0();

        pFar->x = FX_Mul32x64c(vFar.x, invWFar);
        pFar->y = FX_Mul32x64c(vFar.y, invWFar);
        pFar->z = FX_Mul32x64c(vFar.z, invWFar);
    }

    return rval;
}
