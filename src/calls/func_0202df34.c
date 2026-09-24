/* func_0202df34 -- draw a shadow volume, MAIN. With a model (+0x10), the G3D base transform is set
 * straight in NNS_G3dGlb: uniform scale +0xc, translation from +0x0 and a rotation about Y by the
 * +0x16 angle (the base-derived matrices are marked stale), then flushed. The model is drawn twice
 * in shadow polygon mode with alpha +0x14: first as the mask (polygon id 0, front faces culled),
 * then as the shadow itself (polygon id 0x3f, no culling). The base scale is reset to 1.0 after. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int fx32;

typedef struct { fx32 x, y, z; } VecFx32;
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

extern NNSG3dGlb data_02047394;         /* NNS_G3dGlb */
extern const short data_0203d210[];     /* FX_SinCosTable_ */
extern void MTX_RotY33_(MtxFx33 *m, fx32 sinVal, fx32 cosVal);
extern void func_0201571c(void);                                  /* NNS_G3dGlbFlushP */
extern void func_02016b60(void *mdl, u32 matID, int polygonID);   /* NNS_G3dMdlSetMdlPolygonID */
extern void func_02016ae8(void *mdl, u32 matID, int cullMode);    /* NNS_G3dMdlSetMdlCullMode */
extern void func_02016bd8(void *mdl, u32 matID, int alpha);       /* NNS_G3dMdlSetMdlAlpha */
extern void func_02016a70(void *mdl, u32 matID, int polyMode);    /* NNS_G3dMdlSetMdlPolygonMode */
extern void func_01ffcc1c(void *mdl, u32 matID, u32 shpID, int sendMat);   /* NNS_G3dDraw1Mat1Shp */

void func_0202df34(ShadowVolume *sv)
{
    void *mdl = sv->resMdl;
    int idx;

    if (mdl == 0) {
        return;
    }
    data_02047394.prmBaseScale.x = data_02047394.prmBaseScale.y = data_02047394.prmBaseScale.z = sv->scale;
    data_02047394.prmBaseTrans = sv->pos;
    idx = sv->rotY >> 4;
    MTX_RotY33_(&data_02047394.prmBaseRot, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    data_02047394.flag &= ~(NNS_G3D_GLB_FLAG_INVBASE_UPTODATE | NNS_G3D_GLB_FLAG_INVBASECAMERA_UPTODATE |
                            NNS_G3D_GLB_FLAG_BASECAMERA_UPTODATE);
    func_0201571c();

    func_02016b60(mdl, 0, 0);
    func_02016ae8(mdl, 0, GX_CULL_FRONT);
    func_02016bd8(mdl, 0, sv->alpha);
    func_02016a70(mdl, 0, GX_POLYGONMODE_SHADOW);
    func_01ffcc1c(mdl, 0, 0, 1);

    func_02016b60(mdl, 0, 0x3f);
    func_02016ae8(mdl, 0, GX_CULL_NONE);
    func_02016bd8(mdl, 0, sv->alpha);
    func_02016a70(mdl, 0, GX_POLYGONMODE_SHADOW);
    func_01ffcc1c(mdl, 0, 0, 1);

    data_02047394.prmBaseScale.x = data_02047394.prmBaseScale.y = data_02047394.prmBaseScale.z = 0x1000;
    data_02047394.flag &= ~(NNS_G3D_GLB_FLAG_INVBASE_UPTODATE | NNS_G3D_GLB_FLAG_INVBASECAMERA_UPTODATE |
                            NNS_G3D_GLB_FLAG_BASECAMERA_UPTODATE);
}
