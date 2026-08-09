typedef signed long fx32;
typedef signed long long fx64;
typedef signed long long fx64c;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

typedef struct MtxFx43 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
    fx32 _30, _31, _32;
} MtxFx43;

typedef struct MtxFx44 {
    fx32 _00, _01, _02, _03;
    fx32 _10, _11, _12, _13;
    fx32 _20, _21, _22, _23;
    fx32 _30, _31, _32, _33;
} MtxFx44;

typedef unsigned long u32;

typedef struct NNSG3dGlb {
    u32 cmd0;
    u32 mtxmode_proj;
    MtxFx44 projMtx;
    u32 mtxmode_posvec;
    MtxFx43 cameraMtx;
} NNSG3dGlb;

extern NNSG3dGlb data_02047394;

extern void MTX_MultVec43(const VecFx32 *src, const MtxFx43 *mtx, VecFx32 *dst);
extern void FX_InvAsync(fx32 value);
extern fx64c func_01ff8ab0(void);
extern void func_02015ca0(int *x1, int *y1, int *x2, int *y2);

static inline fx32 FX_Mul32x64c(fx32 x, fx64c y)
{
    return (fx32)((y * (fx64)x + 0x80000000LL) >> 32);
}

static inline const MtxFx44 *NNS_G3dGlbGetProjectionMtx(void)
{
    return &data_02047394.projMtx;
}

static inline const MtxFx43 *NNS_G3dGlbGetCameraMtx(void)
{
    return &data_02047394.cameraMtx;
}

int func_0201653c(const VecFx32 *pWorld, int *px, int *py)
{
    const MtxFx44 *proj;
    const MtxFx43 *camera;
    VecFx32 tmp;
    VecFx32 vec;
    fx32 w;
    fx64c invW;
    int x1, y1, x2, y2;
    int dx, dy;
    int rval;

    proj = NNS_G3dGlbGetProjectionMtx();
    camera = NNS_G3dGlbGetCameraMtx();

    MTX_MultVec43(pWorld, camera, &tmp);

    w = (fx32)(((fx64)tmp.x * proj->_03 +
                (fx64)tmp.y * proj->_13 +
                (fx64)tmp.z * proj->_23) >> 12);
    w += proj->_33;

    FX_InvAsync(w);

    vec.x = (fx32)(((fx64)tmp.x * proj->_00 +
                    (fx64)tmp.y * proj->_10 +
                    (fx64)tmp.z * proj->_20) >> 12);
    vec.x += proj->_30;

    vec.y = (fx32)(((fx64)tmp.x * proj->_01 +
                    (fx64)tmp.y * proj->_11 +
                    (fx64)tmp.z * proj->_21) >> 12);
    vec.y += proj->_31;

    invW = func_01ff8ab0();

    vec.x = (FX_Mul32x64c(vec.x, invW) + 0x1000) / 2;
    vec.y = (FX_Mul32x64c(vec.y, invW) + 0x1000) / 2;

    if (vec.x < 0 || vec.y < 0 || vec.x > 0x1000 || vec.y > 0x1000) {
        rval = -1;
    } else {
        rval = 0;
    }

    func_02015ca0(&x1, &y1, &x2, &y2);
    dx = x2 - x1;
    dy = y2 - y1;

    *px = x1 + ((vec.x * dx + 0x800) >> 12);
    *py = 191 - y1 - ((vec.y * dy + 0x800) >> 12);

    return rval;
}
