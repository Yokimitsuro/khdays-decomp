/* func_ov106_020b8790 -- Ov106_DrawNoiseTile: draw one tile of the noise overlay at its
 * position (z 0x400000): the base translation is set (NNS_G3dGlbSetBaseTrans 02015880) and
 * flushed (NNS_G3dGlbFlushP 020157c4), then the geometry engine gets the texture parameter and
 * palette base of the noise state (data_ov106_020b8b68 +0x74 / +0x78, commands 0x2a / 0x2b in
 * one word), a polygon attribute 0x3d0000c0 with the active screen's light level (+0x68 by
 * data_0204be04) as alpha, and the colour 0x7fff (GX_SendFifoWords 01ff9f00).
 * PROVENANCE: byte-identical twin of ov023's Ov023_DrawNoiseTile (func_ov023_02089a38), same code and
 * pool layout in the ov106 event scene; the ov023 source is the analysed one. */
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Fx32Pair {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} Fx32Pair;

typedef struct Ov023NoiseState {
    Fx32Pair aTile[12];       /* 0x00 */
    int  aFlag[2];            /* 0x60 */
    int  aLight[2];           /* 0x68 */
    int  nScroll;             /* 0x70 */
    u32  nTexImageParam;      /* 0x74 */
    u32  nPlttBase;           /* 0x78 */
} Ov023NoiseState;

extern void func_02015880(const VecFx32 *pTrans);                  /* NNS_G3dGlbSetBaseTrans */
extern void func_020157c4(void);                                    /* NNS_G3dGlbFlushP */
extern void func_01ff9f00(u32 nCommand, const void *pWords, u32 nCount); /* GX_SendFifoWords */
extern Ov023NoiseState *data_ov106_020b8b68;                        /* the noise overlay state */
extern u8   data_0204be04;                                          /* the published active screen */

void func_ov106_020b8790(Fx32Pair *pTile)
{
    VecFx32 vPos;
    u32 nPolygonAttr;
    u32 nColor;
    int nX;
    int nY;

    nX = pTile->x;
    nY = pTile->y;
    vPos.x = nX;
    vPos.y = nY;
    vPos.z = 0x400000;
    func_02015880(&vPos);
    func_020157c4();
    func_01ff9f00(0x2b2a, &data_ov106_020b8b68->nTexImageParam, 2);
    nPolygonAttr = 0x3d0000c0 | (data_ov106_020b8b68->aLight[data_0204be04] << 16);
    func_01ff9f00(0x29, &nPolygonAttr, 1);
    nColor = 0x7fff;
    func_01ff9f00(0x20, &nColor, 1);
}
