typedef long s32;
typedef long fx32;
typedef long long fx64;
typedef long long fx64c;

typedef struct MtxFx44 {
    fx32 m[4][4];
} MtxFx44;

extern void MI_Copy64B(const void *src, void *dst);
extern void MTX_Identity44_(MtxFx44 *dst);
extern fx64c func_01ff8a50(fx32 x);

static inline fx32 FX_Mul32x64c(fx32 x, fx64c y)
{
    return (fx32)((y * (fx64)x + 0x80000000LL) >> 32);
}

s32 func_02015924(const MtxFx44 *pSrc, MtxFx44 *pDst)
{
    MtxFx44 gjm;
    int i, j, k;
    fx64c ww;
    fx32 w;

    MI_Copy64B(pSrc, &gjm);
    MTX_Identity44_(pDst);

    for (i = 0; i < 4; ++i) {
        fx32 max = 0;
        int swp = i;

        for (k = i; k < 4; k++) {
            fx32 ftmp = (gjm.m[k][i] < 0) ? -gjm.m[k][i] : gjm.m[k][i];

            if (ftmp > max) {
                max = ftmp;
                swp = k;
            }
        }

        if (max == 0) {
            return -1;
        }

        if (swp != i) {
            for (k = 0; k < 4; k++) {
                fx32 tmp;
                tmp = gjm.m[i][k];
                gjm.m[i][k] = gjm.m[swp][k];
                gjm.m[swp][k] = tmp;

                tmp = pDst->m[i][k];
                pDst->m[i][k] = pDst->m[swp][k];
                pDst->m[swp][k] = tmp;
            }
        }

        ww = func_01ff8a50(gjm.m[i][i]);
        for (j = 0; j < 4; ++j) {
            gjm.m[i][j] = FX_Mul32x64c(gjm.m[i][j], ww);
            pDst->m[i][j] = FX_Mul32x64c(pDst->m[i][j], ww);
        }

        for (k = 0; k < 4; ++k) {
            if (k == i)
                continue;

            w = gjm.m[k][i];
            for (j = 0; j < 4; ++j) {
                gjm.m[k][j] -= (fx32)(((fx64)w * gjm.m[i][j]) >> 12);
                pDst->m[k][j] -= (fx32)(((fx64)w * pDst->m[i][j]) >> 12);
            }
        }
    }
    return 0;
}
