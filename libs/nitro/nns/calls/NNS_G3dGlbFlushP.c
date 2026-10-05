
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MtxFx44 {
    fx32 m[4][4];
} MtxFx44;

typedef struct MtxFx43 {
    fx32 m[4][3];
} MtxFx43;

typedef struct MtxFx33 {
    fx32 m[3][3];
} MtxFx33;

typedef struct NNSG3dGlb {
    u32 cmd0;
    u32 mtxmode_proj;
    MtxFx44 projMtx;
    u32 mtxmode_posvec;
    MtxFx43 cameraMtx;
    u32 cmd1;
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
    u32 prmViewPort;
    u32 cmd4;
    MtxFx33 prmBaseRot;
    VecFx32 prmBaseTrans;
    VecFx32 prmBaseScale;
    u32 prmTexImageParam;
    u32 flag;
} NNSG3dGlb;

extern NNSG3dGlb NNS_G3dGlb;
extern void GX_SendFifoWords(u32 op, const u32 *args, u32 num);

static inline void NNS_G3dGeMtxMode(u32 mode)
{
    GX_SendFifoWords(0x10, &mode, 1);
}

void NNS_G3dGlbFlushP(void)
{
    GX_SendFifoWords(0x00001610,
                  (u32 *)&NNS_G3dGlb.mtxmode_proj,
                  (sizeof(NNS_G3dGlb.mtxmode_proj) + sizeof(NNS_G3dGlb.projMtx)) / 4);

    GX_SendFifoWords(0x19,
                  (u32 *)&NNS_G3dGlb.cameraMtx,
                  sizeof(NNS_G3dGlb.cameraMtx) / 4);

    GX_SendFifoWords(0x00001b19,
                  (u32 *)&NNS_G3dGlb.prmBaseRot,
                  (sizeof(NNS_G3dGlb.prmBaseRot) +
                   sizeof(NNS_G3dGlb.prmBaseTrans) +
                   sizeof(NNS_G3dGlb.prmBaseScale)) / 4);

    NNS_G3dGeMtxMode(2);

    GX_SendFifoWords(NNS_G3dGlb.cmd1, (u32 *)&NNS_G3dGlb.cmd1 + 1, 4);
    GX_SendFifoWords(0x15, (u32 *)0, 0);
    GX_SendFifoWords(0x2a, &NNS_G3dGlb.prmTexImageParam, 1);

    NNS_G3dGlb.flag |= 1u;
    NNS_G3dGlb.flag &= ~2u;
}
