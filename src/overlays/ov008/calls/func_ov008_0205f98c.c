/* func_ov008_0205f98c -- Ov008_InitGridMenuTextures: load the 3D panel icon
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
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

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

extern char data_ov008_02090408[];                                        /* "ui/pnl/3d_&.pak.z" */
extern void  func_02010e80(int a, int b);
extern void  func_02011174(int a, int b);
extern void *func_0201ef9c(const char *pPath, int nHeap);                 /* Archive_LoadFile */
extern void  func_02025464(void *pFile, int bEnableDispatch);             /* Obj_RelocateSections */
extern void  func_0201f390(int bPhase);                                   /* InstallHandlerPairByFlag */
extern u32   func_02010f7c(int nSize, int a, int b);                      /* texture VRAM slot */
extern u32   func_020111c0(int nSize, int a, int b);                      /* palette VRAM slot */
extern void *func_020255d4(void *pFile, int nMember, int nSub);           /* Archive_GetMember */
extern NNSG3dResTex *func_02017088(void *pResource);                      /* NNS_G3dGetTex */
extern void  func_02014e70(NNSG3dResTex *pTex, u32 hTexSlot, int nArg);
extern void  func_02014ee4(NNSG3dResTex *pTex, u32 hPalSlot);
extern void  func_02025364(NNSG3dResTex *pTex);
extern void  func_02025420(NNSG3dResTex *pTex);
extern void  func_ov008_0205f944(Ov008GridCell *pCell, short nX, short nY, short nTile, short nPalette); /* Ov008_InitGridCell */

void func_ov008_0205f98c(Ov008MenuContext *pCtx)
{
    int i;
    Ov008TextureSlot *pSlot;
    NNSG3dResTex *pTex;
    int nRow;
    int nCol;
    int nX;
    int nY;
    Ov008GridCell *pCell;

    func_02010e80(1, 1);
    func_02011174(0x8000, 1);
    pCtx->pIconArchive = func_0201ef9c(data_ov008_02090408, 0xe);
    func_02025464(pCtx->pIconArchive, 0);
    func_0201f390(0);
    for (i = 0; i < TEXTURE_COUNT; i++) {
        pSlot = &pCtx->aTexture[i];
        pSlot->hTexSlot = func_02010f7c(0x100, 0, 0);
        pSlot->hPalSlot = func_020111c0(0x40, 0, 1);
        pSlot->nIndex = i;
        pSlot->pResource = func_020255d4(pCtx->pIconArchive, TEXTURE_MEMBER, pSlot->nIndex);
        pTex = func_02017088(pSlot->pResource);
        func_02014e70(pTex, pSlot->hTexSlot, 0);
        func_02014ee4(pTex, pSlot->hPalSlot);
        func_02025364(pTex);
        func_02025420(pTex);
    }
    func_0201f390(1);
    for (nRow = 0; nRow < GRID_ROWS; nRow++) {
        for (nCol = 0; nCol < GRID_COLS; nCol++) {
            func_ov008_0205f944(&pCtx->gridDisplayCells[nRow][nCol], 8 + nCol * 0x10, 0x17 + nRow * 0x10, 0, PALETTE_GRID);
        }
    }
    for (i = 0; i < GRID_ROWS; i++) {
        func_ov008_0205f944(&pCtx->aRowCell[i], 0x6a, 0x18 + i * 0x10, 0, PALETTE_GRID);
    }
    for (i = 0; i < DRAG_CELLS; i++) {
        func_ov008_0205f944(&pCtx->aDragCell[i], 0, 0, 1, PALETTE_DRAG);
    }
    func_ov008_0205f944(&pCtx->currentCell, 0, 0, 1, PALETTE_DRAG);
}
