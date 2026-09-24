/* Texture SRT matrix for a rotated texture (NNS G3D style): the 2x2 rotation (+0x20 sin, +0x22 cos)
 * is corrected for the texture's aspect ratio (height / width and width / height through the
 * divider) and the translation row keeps the rotation centred on the texture: row 3 is
 * ((1 - sin - cos) * width << 3) - (transS * width << 4) and ((1 + sin - cos) * height << 3) +
 * (transT * height << 4). */
typedef short s16;
typedef unsigned short u16;
typedef int fx32;

typedef struct {
    char pad00[0x20];
    s16 sinR;           /* 0x20 */
    s16 cosR;           /* 0x22 */
    fx32 transS;        /* 0x24 */
    fx32 transT;        /* 0x28 */
    u16 width;          /* 0x2c */
    u16 height;         /* 0x2e */
} TexSRTAnm;

typedef struct {
    fx32 m[4][4];
} MtxFx44;

extern void FX_DivAsync(fx32 numer, fx32 denom);
extern fx32 FX_GetDivResult(void);

static inline fx32 FxOneMinus(fx32 x)
{
    x = -x;
    return x + 0x1000;
}

void func_02019320(MtxFx44 *m, const TexSRTAnm *anm)
{
    fx32 w = anm->width << 12;
    fx32 h = anm->height << 12;

    FX_DivAsync(h, w);
    m->m[0][0] = anm->cosR;
    m->m[1][1] = anm->cosR;
    m->m[0][1] = (-anm->sinR * FX_GetDivResult()) >> 12;
    FX_DivAsync(w, h);
    m->m[3][0] = (FxOneMinus(anm->sinR + anm->cosR) * anm->width << 3) - ((anm->transS * anm->width) << 4);
    m->m[3][1] = ((anm->sinR - anm->cosR + 0x1000) * anm->height << 3) + ((anm->transT * anm->height) << 4);
    m->m[1][0] = (anm->sinR * FX_GetDivResult()) >> 12;
}
