/* func_ov023_02089880 -- Ov023_SetupNoiseDraw: set the G3D globals up for the noise overlay.
 * An orthographic projection over 0..0xc0 x 0..0x100 (near -0x400000, far 0x400000, scale
 * 1.0; MTX_OrthoW 02004eac into data_0204739c) and a camera at the origin looking down +z
 * with y up (MTX_LookAt 01ff9c04 into data_020473e0, the three vectors cached in the G3D
 * global state data_02047394) are installed, the base scale becomes the texture's width and
 * height (+0x7c / +0x80 of the noise state) in 4.12 (NNS_G3dGlbSetBaseScale 020158b0) and the
 * base rotation a Z rotation by the scroll (+0x70; MTX_RotZ33_ from FX_SinCosTable_ copied
 * into data_02047428 with MI_Copy36B); the matching dirty bits are cleared each time. */
typedef unsigned int   u32;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct MtxFx33 {
    int  a[9];                /* 0x00 */
} MtxFx33;

typedef struct Ov023NoiseState {
    char pad_00[0x70];
    int  nScroll;             /* 0x70 */
    u32  nTexImageParam;      /* 0x74 */
    u32  nPlttBase;           /* 0x78 */
    int  nWidth;              /* 0x7c */
    int  nHeight;             /* 0x80 */
} Ov023NoiseState;

/* Global camera-commit state (GX dirty flags + cached vectors, data_02047394). */
extern struct {
    char    _p00[0xd4];
    int     flags;          /* +0xd4 */
    char    _pd8[0x218 - 0xd8];
    VecFx32 cachePos;       /* +0x218 (data_020475ac) */
    VecFx32 cacheUp;        /* +0x224 (data_020475b8) */
    VecFx32 cacheTarget;    /* +0x230 (data_020475c4) */
} data_02047394;

extern char data_0204739c[];                                        /* projection matrix output */
extern char data_020473e0[];                                        /* view (look-at) matrix output */
extern char data_02047428[];                                        /* G3D globals: the base rotation */
extern void func_02004eac(int a, int b, int c, int d, int e, int f, int g, void *projOut); /* MTX_OrthoW */
extern void func_01ff9c04(const VecFx32 *pos, const VecFx32 *up, const VecFx32 *target, void *viewOut); /* MTX_LookAt */
extern void func_020158b0(const VecFx32 *pScale);                   /* NNS_G3dGlbSetBaseScale */
extern void MTX_RotZ33_(MtxFx33 *pMtx, int nSin, int nCos);
extern void MI_Copy36B(const void *pSrc, void *pDst);
extern const short data_0203d210[];                                 /* FX_SinCosTable_: sin, cos pairs */
extern Ov023NoiseState *data_ov023_0208a7c0;                        /* the noise overlay state */

void func_ov023_02089880(void)
{
    VecFx32 vPos;
    VecFx32 vTarget;
    VecFx32 vUp;
    VecFx32 vScale;
    MtxFx33 mtxRot;
    int nWidth;
    int nHeight;
    int nScroll;

    func_02004eac(0, 0xc0000, 0, 0x100000, -0x400000, 0x400000, 0x1000, data_0204739c);
    data_02047394.flags &= ~0x50;
    vPos.y = 0;
    vPos.x = 0;
    vPos.z = 0x1000;
    data_02047394.cachePos = vPos;
    vUp.y = 0x1000;
    vUp.z = 0;
    vUp.x = 0;
    data_02047394.cacheUp = vUp;
    vTarget.z = 0;
    vTarget.y = 0;
    vTarget.x = 0;
    data_02047394.cacheTarget = vTarget;
    func_01ff9c04(&vPos, &vUp, &vTarget, data_020473e0);
    data_02047394.flags &= ~0xe8;
    nHeight = data_ov023_0208a7c0->nHeight << 12;
    nWidth = data_ov023_0208a7c0->nWidth << 12;
    vScale.z = 0x1000;
    vScale.x = (int)(((long long)nWidth * 0x1000 + 0x800) >> 12);
    vScale.y = (int)(((long long)nHeight * 0x1000 + 0x800) >> 12);
    func_020158b0(&vScale);
    nScroll = data_ov023_0208a7c0->nScroll >> 4;
    MTX_RotZ33_(&mtxRot, data_0203d210[nScroll * 2], data_0203d210[nScroll * 2 + 1]);
    MI_Copy36B(&mtxRot, data_02047428);
    data_02047394.flags &= ~0xa4;
}
