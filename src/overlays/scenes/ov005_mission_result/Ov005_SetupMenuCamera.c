/* Sets up the menu's 3D camera: an orthographic projection, unit base scale, identity base rotation
 * and zero translation, and a camera on the z axis looking at the origin; then flushes the G3D
 * state. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MtxFx33 {int m[9];} MtxFx33;
typedef struct MtxFx43 {int m[12];} MtxFx43;
typedef struct MtxFx44 {int m[16];} MtxFx44;
typedef struct NNSG3dGlb {
    u32 cmd0,mtxmode_proj;
    MtxFx44 projMtx;
    u32 mtxmode_posvec;
    MtxFx43 cameraMtx;
    unsigned char opaque7c[0x18];
    MtxFx33 prmBaseRot;
    VecFx32 prmBaseTrans,prmBaseScale;
    u32 prmTexImageParam,flag;
    unsigned char opaqueD8[0x140];
    VecFx32 cameraPos,cameraUp,cameraTarget;
} NNSG3dGlb;
extern NNSG3dGlb NNS_G3dGlb;
extern void MTX_OrthoW(int,int,int,int,int,int,int,MtxFx44 *);
extern void NNS_G3dGlbSetBaseScale(const VecFx32 *);
extern void MTX_Identity33_(MtxFx33 *);
extern void MI_Copy36B(const void *,void *);
extern void NNS_G3dGlbSetBaseTrans(const VecFx32 *);
extern void MTX_LookAt(const VecFx32 *,const VecFx32 *,const VecFx32 *,MtxFx43 *);
extern void NNS_G3dGlbFlushP(void);

static inline void setProjection(int top,int bottom,int left,int right,int near,int far) {
    MTX_OrthoW(top,bottom,left,right,near,far,0x1000,&NNS_G3dGlb.projMtx);
    NNS_G3dGlb.flag &= ~0x50u;
}

void Ov005_SetupMenuCamera(void) {
    VecFx32 base;
    VecFx32 camera;
    VecFx32 target;
    VecFx32 up;
    MtxFx33 rotation;
    setProjection(0x1800,-0x1800,0x2000,-0x2000,0x1000,0x190000);
    base.x = base.y = base.z = 0x1000;
    NNS_G3dGlbSetBaseScale(&base);
    MTX_Identity33_(&rotation);
    MI_Copy36B(&rotation,&NNS_G3dGlb.prmBaseRot);
    NNS_G3dGlb.flag &= ~0xa4u;
    base.x = base.y = base.z = 0;
    NNS_G3dGlbSetBaseTrans(&base);
    up.x = up.z = target.x = target.y = target.z = camera.x = camera.y = 0;
    camera.z = 0xa000;
    up.y = -0x1000;
    NNS_G3dGlb.cameraPos = camera;
    NNS_G3dGlb.cameraUp = up;
    NNS_G3dGlb.cameraTarget = target;
    MTX_LookAt(&camera,&up,&target,&NNS_G3dGlb.cameraMtx);
    NNS_G3dGlb.flag &= ~0xe8u;
    NNS_G3dGlbFlushP();
}
