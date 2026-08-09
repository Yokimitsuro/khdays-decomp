typedef unsigned char u8;
typedef unsigned long u32;
typedef long fx32;

typedef struct MtxFx44 {
    fx32 m[4][4];
} MtxFx44;

typedef struct MtxFx43 {
    fx32 m[4][3];
} MtxFx43;

typedef struct MtxFx33 {
    fx32 m[3][3];
} MtxFx33;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

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

extern NNSG3dGlb data_02047394;
extern void func_01ff9f00(u32 op, const u32 *args, u32 num);

static inline void NNS_G3dGeMtxMode(u32 mode)
{
    func_01ff9f00(0x10, &mode, 1);
}

void func_020157c4(void)
{
    func_01ff9f00(0x00001610,
                  (u32 *)&data_02047394.mtxmode_proj,
                  (sizeof(data_02047394.mtxmode_proj) + sizeof(data_02047394.projMtx)) / 4);

    func_01ff9f00(0x19,
                  (u32 *)&data_02047394.cameraMtx,
                  sizeof(data_02047394.cameraMtx) / 4);

    func_01ff9f00(0x00001b19,
                  (u32 *)&data_02047394.prmBaseRot,
                  (sizeof(data_02047394.prmBaseRot) +
                   sizeof(data_02047394.prmBaseTrans) +
                   sizeof(data_02047394.prmBaseScale)) / 4);

    NNS_G3dGeMtxMode(2);

    func_01ff9f00(data_02047394.cmd1, (u32 *)&data_02047394.cmd1 + 1, 4);
    func_01ff9f00(0x15, (u32 *)0, 0);
    func_01ff9f00(0x2a, &data_02047394.prmTexImageParam, 1);

    data_02047394.flag |= 1u;
    data_02047394.flag &= ~2u;
}
