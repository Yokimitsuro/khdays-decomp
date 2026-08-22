/*
 * Ov002_DrawSpriteQuad - draw one textured billboard quad through the GX FIFO.
 *
 * Sets the camera's two targets from the sprite's position and scale, builds a
 * 3x3 rotation (Z always, Y as well when the sprite carries a Y angle), copies
 * it into the global orientation matrix, then streams the polygon: texture
 * image and palette base, polygon attributes, vertex colour, a begin, and the
 * four corners as texcoord/vertex pairs before the end command.
 *
 * The quad is a unit square from -0.5 to +0.5 in both axes; the frame index at
 * +0x25 selects a horizontal strip of the texture, so the U coordinates are
 * frame*width and (frame+1)*width.
 */

typedef struct { int x, y, z; } VecFx32;

typedef struct {
    char           _p00[4];
    short          nWidth;      /* +0x04 */
    short          nHeight;     /* +0x06 */
    unsigned int   nTexParam;   /* +0x08, streamed as a pair with the palette */
    unsigned int   nPltBase;    /* +0x0c */
    int            nX;          /* +0x10 */
    int            nY;          /* +0x14 */
    int            nScaleX;     /* +0x18 */
    int            nScaleY;     /* +0x1c */
    int            nDepth;      /* +0x20 */
    unsigned char  nPolyId;     /* +0x24 */
    unsigned char  nFrame;      /* +0x25 */
    unsigned short nAngleY;     /* +0x26 */
    unsigned short nAngleZ;     /* +0x28 */
    unsigned char  nAlpha : 5;  /* +0x2a, low 5 bits */
} Sprite;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern short data_0203d210[];   /* shared sin/cos table, [i*2]=sin, [i*2+1]=cos */
extern char data_02047428[];    /* global 3x3 orientation matrix */

extern struct {
    char         _p00[0xd4];
    unsigned int flags;         /* +0xd4 */
} data_02047394;

extern void func_02015880(const VecFx32 *v);   /* set primary camera target */
extern void func_020158b0(const VecFx32 *v);   /* set secondary camera target */
extern void MTX_RotZ33_(int *m, int nSin, int nCos);
extern void MTX_Identity33_(int *m);
extern void MTX_RotY33_(int *m, int nSin, int nCos);
extern void MTX_Concat33(const int *a, const int *b, int *out);
extern void MI_Copy36B(const int *src, void *dst);
extern void func_020157c4(void);
extern void func_01ff9f00(unsigned int nCmd, const void *pSrc,
                          unsigned int nWords);   /* GX_SendFifoWords */

void func_ov002_02050f50(Sprite *p, int bBlend)
{
    VecFx32 vPos;
    VecFx32 vScale;
    int mRot[9];
    /* The Y matrix is preceded by two halfwords the ROM clears at the top of
     * the function, so they belong to one object with it. */
    short aPad[2] = {0, 0};
    struct {
        int m[9];
    } yaw;
    unsigned int nAttr;
    unsigned int nColour;
    unsigned int nBegin;
    unsigned int nTexA;
    unsigned int nVtxA[2];
    unsigned int nTexB;
    unsigned int nVtxB[2];
    unsigned int nTexC;
    unsigned int nVtxC[2];
    unsigned int nTexD;
    unsigned int nVtxD[2];
    int nIdx;
    int nDepth;
    int nPosX;
    int nPosY;
    int nHeight;
    int nFrame;
    int nWidth;
    unsigned int nPoly;
    unsigned int nAlpha;
    int nW12;
    int nH12;
    unsigned int nU0;
    unsigned int nU1;
    unsigned int nV;

    nH12 = (int)p->nHeight << 12;
    nW12 = (int)p->nWidth << 12;
    vScale.z = 0x1000;
    vScale.x = nW12;
    vScale.y = nH12;
    vScale.x = FX_Mul(p->nScaleX, nW12);
    vScale.y = FX_Mul(p->nScaleY, nH12);
    func_020158b0(&vScale);

    nDepth = p->nDepth;
    nPosY = p->nY;
    nPosX = p->nX;
    if (nDepth > 0x1000) {
        nDepth = 0x1000;
    }
    vPos.x = nPosX;
    vPos.y = nPosY;
    vPos.z = 0x400000 - nDepth;
    func_02015880(&vPos);

    nIdx = p->nAngleZ >> 4;
    MTX_RotZ33_(mRot, data_0203d210[nIdx * 2], data_0203d210[nIdx * 2 + 1]);
    if (p->nAngleY != 0) {
        MTX_Identity33_(yaw.m);
        nIdx = p->nAngleY >> 4;
        MTX_RotY33_(yaw.m, data_0203d210[nIdx * 2],
                      data_0203d210[nIdx * 2 + 1]);
        MTX_Concat33(mRot, yaw.m, mRot);
    }
    MI_Copy36B(mRot, data_02047428);
    data_02047394.flags &= ~0xa4;
    func_020157c4();

    func_01ff9f00(0x2b2a, &p->nTexParam, 2);
    nPoly = p->nPolyId;
    nAlpha = p->nAlpha;
    nAttr = (bBlend != 0 ? 0x800u : 0u) | 0xc0u
            | ((unsigned int)nPoly << 24)
            | ((unsigned int)nAlpha << 16);
    func_01ff9f00(0x29, &nAttr, 1);
    nColour = 0x7fff;
    func_01ff9f00(0x20, &nColour, 1);
    nWidth = (int)p->nWidth << 12;
    nFrame = p->nFrame;
    nHeight = p->nHeight;
    nBegin = 1;
    func_01ff9f00(0x40, &nBegin, 1);

    nU0 = (unsigned short)(nWidth * nFrame * 0x100 >> 16);
    nTexA = nU0;
    func_01ff9f00(0x22, &nTexA, 1);
    nVtxA[0] = 0xf800f800;
    nVtxA[1] = 0;
    func_01ff9f00(0x23, nVtxA, 2);

    nU1 = (unsigned short)(nWidth * (nFrame + 1) * 0x100 >> 16);
    nTexB = nU1;
    func_01ff9f00(0x22, &nTexB, 1);
    nVtxB[0] = 0xf8000800;
    nVtxB[1] = 0;
    func_01ff9f00(0x23, nVtxB, 2);

    nV = (unsigned short)(nHeight << 20 >> 16);
    nTexC = nU1 | nV << 16;
    func_01ff9f00(0x22, &nTexC, 1);
    nVtxC[0] = 0x08000800;
    nVtxC[1] = 0;
    func_01ff9f00(0x23, nVtxC, 2);

    nTexD = nU0 | nV << 16;
    func_01ff9f00(0x22, &nTexD, 1);
    nVtxD[0] = 0x08000800 + 0xf000;
    nVtxD[1] = 0;
    func_01ff9f00(0x23, nVtxD, 2);

    func_01ff9f00(0x41, 0, 0);
}
