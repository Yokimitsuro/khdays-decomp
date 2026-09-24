/* func_020287e8 -- draw a list of camera-facing sprites through the geometry engine, MAIN. For
 * each node (next at +0): loads its texture image / palette words (+8), moves the shared
 * billboard matrix data_020428e0 to the node's +0xc position seen through the view matrix
 * data_020473e0 and loads it, sets the polygon attributes (alpha +0x20, polygon id +0x22, both
 * faces) and emits one textured quad, width +0x18 centred and height +0x1a, with texture
 * corners (+0x1c,+0x1d) and (+0x1e,+0x1f). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef short fx16;
typedef int fx32;
typedef volatile u32 REGType32v;

typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx32 _00, _01, _02, _10, _11, _12, _20, _21, _22, _30, _31, _32; } MtxFx43;

#define reg_G3_TEXCOORD       (*(REGType32v *)0x04000488)
#define reg_G3_VTX_16         (*(REGType32v *)0x0400048c)
#define reg_G3_VTX_XY         (*(REGType32v *)0x04000494)
#define reg_G3_POLYGON_ATTR   (*(REGType32v *)0x040004a4)
#define reg_G3_TEXIMAGE_PARAM (*(REGType32v *)0x040004a8)
#define reg_G3_TEXPLTT_BASE   (*(REGType32v *)0x040004ac)
#define reg_G3_BEGIN_VTXS     (*(REGType32v *)0x04000500)
#define reg_G3_END_VTXS       (*(REGType32v *)0x04000504)

#define GX_FX16PAIR(a, b) ((u32)(((u32)(u16)(a)) | ((u32)(u16)(b) << 16)))
#define GX_BEGIN_QUADS 1
#define GX_CULL_NONE 3

static inline void G3_Vtx(fx16 x, fx16 y, fx16 z)
{
    reg_G3_VTX_16 = GX_FX16PAIR(x, y);
    reg_G3_VTX_16 = (u32)(u16)z;
}

static inline void G3_VtxXY(fx16 x, fx16 y)
{
    reg_G3_VTX_XY = GX_FX16PAIR(x, y);
}

static inline void G3_TexCoordPx(int s, int t)
{
    reg_G3_TEXCOORD = ((u32)s << 4) | ((u32)t << 20);
}

typedef struct SpriteTex {
    u32 texImageParam;
    u32 plttBase;
} SpriteTex;

typedef struct Billboard {
    struct Billboard *next;             /* +0x00 */
    int pad04;
    const SpriteTex *pTex;              /* +0x08 */
    VecFx32 pos;                        /* +0x0c */
    s16 width;                          /* +0x18 */
    fx16 height;                        /* +0x1a */
    u8 s0;                              /* +0x1c */
    u8 t0;                              /* +0x1d */
    u8 s1;                              /* +0x1e */
    u8 t1;                              /* +0x1f */
    s16 alpha;                          /* +0x20 */
    s16 polygonId;                      /* +0x22 */
} Billboard;

extern MtxFx43 data_020473e0;   /* view matrix */
extern MtxFx43 data_020428e0;   /* billboard matrix */
extern void MTX_MultVec43(const VecFx32 *vec, const MtxFx43 *m, VecFx32 *dst);
extern void G3_LoadMtx43(const MtxFx43 *m);

void func_020287e8(Billboard **ppList)
{
    Billboard *node;

    for (node = *ppList; node != 0; node = node->next) {
        fx16 hw = (fx16)(node->width / 2);

        reg_G3_TEXIMAGE_PARAM = node->pTex->texImageParam;
        reg_G3_TEXPLTT_BASE = node->pTex->plttBase;
        MTX_MultVec43(&node->pos, &data_020473e0, (VecFx32 *)((char *)&data_020428e0 + 0x24));
        G3_LoadMtx43(&data_020428e0);
        reg_G3_POLYGON_ATTR = (node->alpha << 16) | ((node->polygonId << 24) | (GX_CULL_NONE << 6));
        reg_G3_BEGIN_VTXS = GX_BEGIN_QUADS;
        G3_TexCoordPx(node->s0, node->t0);
        G3_Vtx(-hw, node->height, 0);
        G3_TexCoordPx(node->s0, node->t1);
        G3_VtxXY(-hw, 0);
        G3_TexCoordPx(node->s1, node->t1);
        G3_VtxXY(hw, 0);
        G3_TexCoordPx(node->s1, node->t0);
        G3_VtxXY(hw, node->height);
        reg_G3_END_VTXS = 0;
    }
}
