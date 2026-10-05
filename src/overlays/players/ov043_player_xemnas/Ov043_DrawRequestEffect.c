/* Draws one request effect of the mission enemy. The row it belongs to is picked from the
 * mission owner's +0x2e64 rows (stride 0x240) by the effect's +1 slot byte, and its +0x224
 * direction gives the orientation: a yaw whenever the direction has any horizontal part, then
 * a pitch whenever it has a vertical one, each concatenated onto an identity. The result goes
 * into the global orientation matrix, the camera's two targets are set from the effect's scale
 * and position, and the model is submitted. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

struct Effect {
    u8 pad0000;
    signed char nRow;            /* 0x0001 */
    u8 pad0002[0x46];
    u8 renderObj;                /* 0x0048 */
    u8 pad0049[0x83];
    VecFx32 vecPos;              /* 0x00cc */
    VecFx32 vecScale;            /* 0x00d8 */
};

extern char data_02047428[];     /* G3D globals: the base rotation */

extern struct {
    char _p00[0xd4];
    unsigned int flags;          /* 0xd4 */
} NNS_G3dGlb;

extern void MTX_Identity33_(int *m);
extern void VEC_Normalize(const VecFx32 *pIn, VecFx32 *pOut);   /* VEC_Normalize */
extern void MTX_RotY33_(int *m, int nSin, int nCos);
extern void MTX_RotX33_(int *m, int nSin, int nCos);
extern void MTX_Concat33(const int *a, const int *b, int *out);
extern void NNS_G3dGlbSetBaseScale(const VecFx32 *v);   /* NNS_G3dGlbSetBaseScale */
extern void MI_Copy36B(const int *src, void *dst);
extern void NNS_G3dGlbSetBaseTrans(const VecFx32 *v);   /* NNS_G3dGlbSetBaseTrans */
extern void Gfx_ApplyBaseTransform(void);               /* apply the base transform */
extern void NNS_G3dDraw(u8 *pObj);           /* NNS_G3dDraw */
extern char *data_ov043_020b58e0;

void Ov043_DrawRequestEffect(struct Effect *pEffect)
{
    int mYaw[9];
    int mPitch[9];
    int mRot[9];
    VecFx32 vDir;
    char *pRow = data_ov043_020b58e0 + 0x264 + 0x2c00 + pEffect->nRow * 0x240;

    MTX_Identity33_(mRot);
    VEC_Normalize((VecFx32 *)(pRow + 0x224), &vDir);
    if (vDir.x != 0 || vDir.z != 0) {
        MTX_RotY33_(mYaw, vDir.x, vDir.z);
        MTX_Concat33(mYaw, mRot, mRot);
    }
    if (vDir.y != 0) {
        if (vDir.z != 0) {
            MTX_RotX33_(mPitch, -vDir.y, 0x1000);
        } else {
            MTX_RotX33_(mPitch, -vDir.y, 0);
        }
        MTX_Concat33(mPitch, mRot, mRot);
    }
    NNS_G3dGlbSetBaseScale(&pEffect->vecScale);
    MI_Copy36B(mRot, data_02047428);
    NNS_G3dGlb.flags &= ~0xa4;
    NNS_G3dGlbSetBaseTrans(&pEffect->vecPos);
    Gfx_ApplyBaseTransform();
    NNS_G3dDraw(&pEffect->renderObj);
}
