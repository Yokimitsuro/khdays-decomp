/* func_ov106_020b8838 -- Ov106_DrawNoiseQuad: draw one tile of the noise overlay as a textured
 * quad.  After the tile's state is set (Ov023_DrawNoiseTile 02089a38) the geometry engine gets
 * BEGIN_VTXS (quads) and four TEXCOORD / VTX_16 pairs around the unit square (-0.5..0.5 as
 * 4.12) with the texture's width and height (+0x7c / +0x80 of the noise state, in 1/16 texel
 * units) as the coordinates, then END_VTXS (GX_SendFifoWords 01ff9f00).
 * PROVENANCE: byte-identical twin of ov023's Ov023_DrawNoiseQuad (func_ov023_02089ae0), same code and
 * pool layout in the ov106 event scene; the ov023 source is the analysed one. */
typedef unsigned int   u32;
typedef signed short   s16;
typedef unsigned short u16;

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
    int  nWidth;              /* 0x7c */
    int  nHeight;             /* 0x80 */
} Ov023NoiseState;

extern void func_ov106_020b8790(Fx32Pair *pTile);                   /* Ov023_DrawNoiseTile */
extern void func_01ff9f00(u32 nCommand, const void *pWords, u32 nCount); /* GX_SendFifoWords */
extern Ov023NoiseState *data_ov106_020b8b68;                        /* the noise overlay state */

void func_ov106_020b8838(Fx32Pair *pTile)
{
    u32 nBegin;
    u32 nTexCoord0;
    u32 aVtx0[2];
    u32 nTexCoord1;
    u32 aVtx1[2];
    u32 nTexCoord2;
    u32 aVtx2[2];
    u32 nTexCoord3;
    u32 aVtx3[2];
    int nWidth;
    int nHeight;
    u32 nS;
    u32 nT;

    nWidth = data_ov106_020b8b68->nWidth;
    nHeight = data_ov106_020b8b68->nHeight;
    func_ov106_020b8790(pTile);
    nBegin = 1;
    func_01ff9f00(0x40, &nBegin, 1);
    nTexCoord0 = 0;
    func_01ff9f00(0x22, &nTexCoord0, 1);
    aVtx0[0] = 0xf800f800;
    aVtx0[1] = 0;
    func_01ff9f00(0x23, aVtx0, 2);
    nS = (u16)(s16)(nWidth << 4);
    nTexCoord1 = nS;
    func_01ff9f00(0x22, &nTexCoord1, 1);
    aVtx1[0] = 0xf8000800;
    aVtx1[1] = 0;
    func_01ff9f00(0x23, aVtx1, 2);
    nT = (u16)(s16)(nHeight << 4);
    nTexCoord2 = nS | (nT << 16);
    func_01ff9f00(0x22, &nTexCoord2, 1);
    aVtx2[0] = 0x08000800;
    aVtx2[1] = 0;
    func_01ff9f00(0x23, aVtx2, 2);
    nTexCoord3 = nT << 16;
    func_01ff9f00(0x22, &nTexCoord3, 1);
    aVtx3[0] = 0x0800f800;
    aVtx3[1] = 0;
    func_01ff9f00(0x23, aVtx3, 2);
    func_01ff9f00(0x41, 0, 0);
}
