/* Ov025_InitGridMenuTextures -- Ov008_InitGridMenuTextures: load the 3D panel icon
 * archive "ui/pnl/3d_&.pak.z" (+0x364) and register its 0xd1 textures
 * (+0x390, 0x10 each: index, resource = archive member 7 / index, texture
 * and palette VRAM slots of 0x100 / 0x40), with handler pair 0 installed
 * during the loop and pair 1 after; then reset the 8 x 5 grid display cells
 * (+0x10a0) at (8 + 0x10 * col, 0x17 + 0x10 * row) with tile 0 / palette
 * 0x1f, the 8 row cells (+0x16e0) at (0x6a, 0x18 + 0x10 * row), the 9 drag
 * cells (+0x184c) and the current cell (+0x1820) at (0, 0) with tile 1 /
 * palette 0x10.  Codegen: cell x / y are written as expressions of the
 * counters (mwcc strength-reduces them into its own induction registers).
 */

#include "nitro/types.h"

#define GRID_ROWS      8
#define GRID_COLS      5
#define DRAG_CELLS     9
#define TEXTURE_COUNT  0xd1
#define TEXTURE_MEMBER 7
#define PALETTE_GRID   0x1f
#define PALETTE_DRAG   0x10

typedef struct NNSG3dResTex NNSG3dResTex;

typedef struct Ov008GridCell {
    u8 pad_00[0x28];
} Ov008GridCell;

typedef struct Ov008TextureSlot {
    u16   nIndex;             /* 0x00 */
    u8    pad_02[2];
    void *pResource;          /* 0x04 */
    u32   hTexSlot;           /* 0x08 */
    u32   hPalSlot;           /* 0x0c */
} Ov008TextureSlot;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x364];
    void *pIconArchive;       /* 0x0364 */
    u8  pad_0368[0x390 - 0x368];
    Ov008TextureSlot aTexture[TEXTURE_COUNT]; /* 0x0390 */
    Ov008GridCell gridDisplayCells[GRID_ROWS][GRID_COLS]; /* 0x10a0 */
    Ov008GridCell aRowCell[GRID_ROWS]; /* 0x16e0 */
    Ov008GridCell currentCell; /* 0x1820 */
    Ov008GridCell *pCurrentCell; /* 0x1848 */
    Ov008GridCell aDragCell[DRAG_CELLS]; /* 0x184c */
} Ov008MenuContext;

extern char gOv025UiPnl3DPackPath[];                                        /* "ui/pnl/3d_&.pak.z" */
extern void  NNS_GfdInitFrmTexVramManager(int a, int b);
extern void  NNS_GfdInitFrmPlttVramManager(int a, int b);
extern void *Archive_LoadFile(const char *pPath, int nHeap);                 /* Archive_LoadFile */
extern void  Obj_RelocateSections(void *pFile, int bEnableDispatch);             /* Obj_RelocateSections */
extern void  InstallHandlerPairByFlag(int bPhase);                                   /* InstallHandlerPairByFlag */
extern u32   NNS_GfdAllocFrmTexVram(int nSize, int a, int b);                      /* texture VRAM slot */
extern u32   func_020111c0(int nSize, int a, int b);                      /* palette VRAM slot */
extern void *Archive_GetMember(void *pFile, int nMember, int nSub);           /* Archive_GetMember */
extern NNSG3dResTex *NNS_G3dGetTex(void *pResource);                      /* NNS_G3dGetTex */
extern void  NNS_G3dTexSetTexKey(NNSG3dResTex *pTex, u32 hTexSlot, int nArg);
extern void  NNSG2d_SetOamManExDrawOrderType(NNSG3dResTex *pTex, u32 hPalSlot);
extern void  Tex_LoadVram(NNSG3dResTex *pTex);
extern void  Gfx_UploadBlock(NNSG3dResTex *pTex);
extern void  Ov025_InitGridCell(Ov008GridCell *pCell, short nX, short nY, short nTile, short nPalette); /* Ov008_InitGridCell */

void Ov025_InitGridMenuTextures(Ov008MenuContext *pCtx)
{
    int i;
    Ov008TextureSlot *pSlot;
    NNSG3dResTex *pTex;
    int nRow;
    int nCol;
    int nX;
    int nY;
    Ov008GridCell *pCell;

    NNS_GfdInitFrmTexVramManager(1, 1);
    NNS_GfdInitFrmPlttVramManager(0x8000, 1);
    pCtx->pIconArchive = Archive_LoadFile(gOv025UiPnl3DPackPath, 0xe);
    Obj_RelocateSections(pCtx->pIconArchive, 0);
    InstallHandlerPairByFlag(0);
    for (i = 0; i < TEXTURE_COUNT; i++) {
        pSlot = &pCtx->aTexture[i];
        pSlot->hTexSlot = NNS_GfdAllocFrmTexVram(0x100, 0, 0);
        pSlot->hPalSlot = func_020111c0(0x40, 0, 1);
        pSlot->nIndex = i;
        pSlot->pResource = Archive_GetMember(pCtx->pIconArchive, TEXTURE_MEMBER, pSlot->nIndex);
        pTex = NNS_G3dGetTex(pSlot->pResource);
        NNS_G3dTexSetTexKey(pTex, pSlot->hTexSlot, 0);
        NNSG2d_SetOamManExDrawOrderType(pTex, pSlot->hPalSlot);
        Tex_LoadVram(pTex);
        Gfx_UploadBlock(pTex);
    }
    InstallHandlerPairByFlag(1);
    for (nRow = 0; nRow < GRID_ROWS; nRow++) {
        for (nCol = 0; nCol < GRID_COLS; nCol++) {
            Ov025_InitGridCell(&pCtx->gridDisplayCells[nRow][nCol], 8 + nCol * 0x10, 0x17 + nRow * 0x10, 0, PALETTE_GRID);
        }
    }
    for (i = 0; i < GRID_ROWS; i++) {
        Ov025_InitGridCell(&pCtx->aRowCell[i], 0x6a, 0x18 + i * 0x10, 0, PALETTE_GRID);
    }
    for (i = 0; i < DRAG_CELLS; i++) {
        Ov025_InitGridCell(&pCtx->aDragCell[i], 0, 0, 1, PALETTE_DRAG);
    }
    Ov025_InitGridCell(&pCtx->currentCell, 0, 0, 1, PALETTE_DRAG);
}
