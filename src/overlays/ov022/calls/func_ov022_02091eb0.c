/* ov022: draw one projectile.
 *
 * Builds the orientation the shot is drawn with from its own direction: a yaw
 * whenever the direction has any horizontal part, then a pitch whenever it has
 * a vertical one, each concatenated onto an identity. The result goes into the
 * global orientation matrix, the camera's two targets are set from the shot's
 * scale and position, and the model is submitted.
 */

typedef unsigned char u8;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

struct Shot {
    u8 pad0000[0x1c];
    VecFx32 vecDir;              /* 0x001c */
    u8 pad0028[0x20];
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

void func_ov022_02091eb0(struct Shot *pShot)
{
    int mYaw[9];
    int mPitch[9];
    int mRot[9];
    VecFx32 vDir;

    MTX_Identity33_(mRot);
    func_01ff8d18(&pShot->vecDir, &vDir);
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
    func_020158b0(&pShot->vecScale);
    MI_Copy36B(mRot, data_02047428);
    data_02047394.flags &= ~0xa4;
    func_02015880(&pShot->vecPos);
    func_0201574c();
    func_020279e0(&pShot->renderObj);
}
