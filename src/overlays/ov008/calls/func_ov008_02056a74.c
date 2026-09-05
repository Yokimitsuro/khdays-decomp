typedef unsigned int u32;

typedef struct VecFx32 {
    int x, y, z;
} VecFx32;

typedef struct MtxFx33 {
    int m[9];
} MtxFx33;

typedef struct MtxFx43 {
    int m[12];
} MtxFx43;

typedef struct MtxFx44 {
    int m[16];
} MtxFx44;

typedef struct NNSG3dGlb {
    u32 cmd0, mtxmode_proj;
    MtxFx44 projMtx;
    u32 mtxmode_posvec;
    MtxFx43 cameraMtx;
    unsigned char opaque7c[0x18];
    MtxFx33 prmBaseRot;
    VecFx32 prmBaseTrans, prmBaseScale;
    u32 prmTexImageParam, flag;
    unsigned char opaqueD8[0x140];
    VecFx32 cameraPos, cameraUp, cameraTarget;
} NNSG3dGlb;

extern NNSG3dGlb data_02047394;
extern void func_02004eac(int, int, int, int, int, int, int, MtxFx44 *);
extern void func_020158b0(const VecFx32 *);
extern void MTX_Identity33_(MtxFx33 *);
extern void MI_Copy36B(const void *, void *);
extern void func_02015880(const VecFx32 *);
extern void func_01ff9c04(const VecFx32 *, const VecFx32 *,
                          const VecFx32 *, MtxFx43 *);
extern void func_020157c4(void);

static inline void
setProjection(int top, int bottom, int left, int right, int near, int far)
{
    func_02004eac(top, bottom, left, right, near, far, 0x1000,
                  &data_02047394.projMtx);
    data_02047394.flag &= ~0x50u;
}

void
func_ov008_02056a74(void)
{
    VecFx32 base;
    VecFx32 camera;
    VecFx32 target;
    VecFx32 up;
    MtxFx33 rotation;

    setProjection(0x1800, -0x1800, 0x2000, -0x2000, 0x1000, 0x190000);
    base.x = base.y = base.z = 0x1000;
    func_020158b0(&base);
    MTX_Identity33_(&rotation);
    MI_Copy36B(&rotation, &data_02047394.prmBaseRot);
    data_02047394.flag &= ~0xa4u;
    base.x = base.y = base.z = 0;
    func_02015880(&base);
    up.x = up.z = target.x = target.y = target.z =
        camera.x = camera.y = 0;
    camera.z = 0xa000;
    up.y = -0x1000;
    data_02047394.cameraPos = camera;
    data_02047394.cameraUp = up;
    data_02047394.cameraTarget = target;
    func_01ff9c04(&camera, &up, &target, &data_02047394.cameraMtx);
    data_02047394.flag &= ~0xe8u;
    func_020157c4();
}
