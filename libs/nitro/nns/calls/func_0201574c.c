typedef unsigned char u8;
typedef unsigned long u32;
typedef long fx32;

typedef struct MtxFx44 {
    fx32 m[4][4];
} MtxFx44;

typedef struct MtxFx43 {
    fx32 m[4][3];
} MtxFx43;

typedef struct NNSG3dGlb {
    u32 cmd0;
    u32 mtxmode_proj;
    MtxFx44 projMtx;
    u32 mtxmode_posvec;
    MtxFx43 cameraMtx;
    u32 cmd1;
    u8 pad80_d4[0x54];
    u32 flag;
} NNSG3dGlb;

extern NNSG3dGlb data_02047394;
extern void func_01ff9f00(u32 op, const u32 *args, u32 num);

static inline void NNS_G3dGeMtxMode(u32 mode)
{
    func_01ff9f00(0x10, &mode, 1);
}

void func_0201574c(void)
{
    func_01ff9f00(0x00001610,
                  (u32 *)&data_02047394.mtxmode_proj,
                  (sizeof(data_02047394.mtxmode_proj) + sizeof(data_02047394.projMtx)) / 4);

    func_01ff9f00(0x19,
                  (u32 *)&data_02047394.cameraMtx,
                  sizeof(data_02047394.cameraMtx) / 4);

    NNS_G3dGeMtxMode(2);
    func_01ff9f00(0x15, (u32 *)&data_02047394.cmd1, 0x16);

    data_02047394.flag &= ~1u;
    data_02047394.flag |= 2u;
}
