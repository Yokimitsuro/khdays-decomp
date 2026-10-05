/* ShadowVolume_Draw -- draw a shadow volume, MAIN. With a model (+0x10), the G3D base transform is set
 * straight in NNS_G3dGlb: uniform scale +0xc, translation from +0x0 and a rotation about Y by the
 * +0x16 angle (the base-derived matrices are marked stale), then flushed. The model is drawn twice
 * in shadow polygon mode with alpha +0x14: first as the mask (polygon id 0, front faces culled),
 * then as the shadow itself (polygon id 0x3f, no culling). The base scale is reset to 1.0 after. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct { fx32 m[9]; } MtxFx33;

typedef struct NNSG3dGlb {
    char pad000[0x94];
    MtxFx33 prmBaseRot;                 /* +0x94 */
    VecFx32 prmBaseTrans;               /* +0xb8 */
    VecFx32 prmBaseScale;               /* +0xc4 */
    int padd0;
    u32 flag;                           /* +0xd4 */
} NNSG3dGlb;

#define NNS_G3D_GLB_FLAG_INVBASE_UPTODATE       0x00000004
#define NNS_G3D_GLB_FLAG_INVBASECAMERA_UPTODATE 0x00000020
#define NNS_G3D_GLB_FLAG_BASECAMERA_UPTODATE    0x00000080
#define GX_CULL_FRONT          1
#define GX_CULL_NONE           3
#define GX_POLYGONMODE_SHADOW  3

typedef struct ShadowVolume {
    VecFx32 pos;                        /* +0x00 */
    fx32 scale;                         /* +0x0c */
    void *resMdl;                       /* +0x10 */
    u8 alpha;                           /* +0x14 */
    u8 pad15;
    u16 rotY;                           /* +0x16 */
} ShadowVolume;

extern NNSG3dGlb NNS_G3dGlb;         /* NNS_G3dGlb */
extern const short data_0203d210[];     /* FX_SinCosTable_ */
extern void MTX_RotY33_(MtxFx33 *m, fx32 sinVal, fx32 cosVal);
extern void NNS_G3dGlbFlush(void);                                  /* NNS_G3dGlbFlushP */
extern void NNS_G3dMdlSetMdlPolygonID(void *mdl, u32 matID, int polygonID);   /* NNS_G3dMdlSetMdlPolygonID */
extern void NNS_G3dMdlSetMdlCullMode(void *mdl, u32 matID, int cullMode);    /* NNS_G3dMdlSetMdlCullMode */
extern void NNS_G3dMdlSetMdlAlpha(void *mdl, u32 matID, int alpha);       /* NNS_G3dMdlSetMdlAlpha */
extern void NNS_G3dMdlSetMdlPolygonMode(void *mdl, u32 matID, int polyMode);    /* NNS_G3dMdlSetMdlPolygonMode */
extern void NNS_G3dDraw1Mat1Shp(void *mdl, u32 matID, u32 shpID, int sendMat);   /* NNS_G3dDraw1Mat1Shp */

void ShadowVolume_Draw(ShadowVolume *sv)
{
    void *mdl = sv->resMdl;
    int idx;

    if (mdl == 0) {
        return;
    }
    NNS_G3dGlb.prmBaseScale.x = NNS_G3dGlb.prmBaseScale.y = NNS_G3dGlb.prmBaseScale.z = sv->scale;
    NNS_G3dGlb.prmBaseTrans = sv->pos;
    idx = sv->rotY >> 4;
    MTX_RotY33_(&NNS_G3dGlb.prmBaseRot, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    NNS_G3dGlb.flag &= ~(NNS_G3D_GLB_FLAG_INVBASE_UPTODATE | NNS_G3D_GLB_FLAG_INVBASECAMERA_UPTODATE |
                            NNS_G3D_GLB_FLAG_BASECAMERA_UPTODATE);
    NNS_G3dGlbFlush();

    NNS_G3dMdlSetMdlPolygonID(mdl, 0, 0);
    NNS_G3dMdlSetMdlCullMode(mdl, 0, GX_CULL_FRONT);
    NNS_G3dMdlSetMdlAlpha(mdl, 0, sv->alpha);
    NNS_G3dMdlSetMdlPolygonMode(mdl, 0, GX_POLYGONMODE_SHADOW);
    NNS_G3dDraw1Mat1Shp(mdl, 0, 0, 1);

    NNS_G3dMdlSetMdlPolygonID(mdl, 0, 0x3f);
    NNS_G3dMdlSetMdlCullMode(mdl, 0, GX_CULL_NONE);
    NNS_G3dMdlSetMdlAlpha(mdl, 0, sv->alpha);
    NNS_G3dMdlSetMdlPolygonMode(mdl, 0, GX_POLYGONMODE_SHADOW);
    NNS_G3dDraw1Mat1Shp(mdl, 0, 0, 1);

    NNS_G3dGlb.prmBaseScale.x = NNS_G3dGlb.prmBaseScale.y = NNS_G3dGlb.prmBaseScale.z = 0x1000;
    NNS_G3dGlb.flag &= ~(NNS_G3D_GLB_FLAG_INVBASE_UPTODATE | NNS_G3D_GLB_FLAG_INVBASECAMERA_UPTODATE |
                            NNS_G3D_GLB_FLAG_BASECAMERA_UPTODATE);
}
