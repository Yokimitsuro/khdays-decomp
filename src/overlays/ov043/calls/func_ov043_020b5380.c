/* Draws one request effect of the mission enemy. The row it belongs to is picked from the
 * mission owner's +0x2e64 rows (stride 0x240) by the effect's +1 slot byte, and its +0x224
 * direction gives the orientation: a yaw whenever the direction has any horizontal part, then
 * a pitch whenever it has a vertical one, each concatenated onto an identity. The result goes
 * into the global orientation matrix, the camera's two targets are set from the effect's scale
 * and position, and the model is submitted. */
typedef unsigned char u8;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

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
} data_02047394;

extern void MTX_Identity33_(int *m);
extern void func_01ff8d18(const VecFx32 *pIn, VecFx32 *pOut);   /* VEC_Normalize */
extern void MTX_RotY33_(int *m, int nSin, int nCos);
extern void MTX_RotX33_(int *m, int nSin, int nCos);
extern void MTX_Concat33(const int *a, const int *b, int *out);
extern void func_020158b0(const VecFx32 *v);   /* NNS_G3dGlbSetBaseScale */
extern void MI_Copy36B(const int *src, void *dst);
extern void func_02015880(const VecFx32 *v);   /* NNS_G3dGlbSetBaseTrans */
extern void func_0201574c(void);               /* apply the base transform */
extern void func_020279e0(u8 *pObj);           /* Obj_InitChannelsAndRun */
extern char *data_ov043_020b58e0;

void func_ov043_020b5380(struct Effect *pEffect)
{
    int mYaw[9];
    int mPitch[9];
    int mRot[9];
    VecFx32 vDir;
    char *pRow = data_ov043_020b58e0 + 0x264 + 0x2c00 + pEffect->nRow * 0x240;

    MTX_Identity33_(mRot);
    func_01ff8d18((VecFx32 *)(pRow + 0x224), &vDir);
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
    func_020158b0(&pEffect->vecScale);
    MI_Copy36B(mRot, data_02047428);
    data_02047394.flags &= ~0xa4;
    func_02015880(&pEffect->vecPos);
    func_0201574c();
    func_020279e0(&pEffect->renderObj);
}
