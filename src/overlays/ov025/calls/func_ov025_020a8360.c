/* func_ov025_020a8360 -- Ov008_BuildMissionListRows: build the mission list's
 * row surfaces.  Clears the 32 x 32 grid of slot 0x1a and takes its handle;
 * for each of the six rows builds the name surface at x = 2 + 4 * i, y = 6,
 * the info surface at x = 4 * i, y = 6, and the extra surface at x = 4 * i
 * with y = 0x19 while the entry gate (+0x40) is clear or 0x16 while it is set
 * (both tests are kept, as the ROM re-reads the gate).  Rows beyond the
 * mission count get their three surfaces refreshed instead; then the scroll
 * geometry is initialised, row 0 selected with cue 2, and unless the list is
 * dirty (+0x48) the rows are refilled.
 * NOTE: the row loop is written with plain indexing (&aRow[i], i * 4 + 2); mwcc
 * strength-reduces it into the ROM's six induction registers itself -- explicit
 * walking pointers / counters colour them differently.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

#define ROW_COUNT 6
#define GRID_SLOT 0x1a

typedef struct TileSurface {
    u8 pad[0x3c];
} TileSurface;

typedef struct Ov008MissionList {
    u8  pad_000[0x40];
    int bEntryGate;           /* 0x040 */
    u8  pad_044[4];
    int bDirty;               /* 0x048 */
    u8  pad_04c[0x84 - 0x4c];
    TileSurface aRowNameSurface[ROW_COUNT];  /* 0x084 */
    TileSurface aRowInfoSurface[ROW_COUNT];  /* 0x1ec */
    TileSurface aRowExtraSurface[ROW_COUNT]; /* 0x354 */
} Ov008MissionList;

extern void func_ov025_020849d8(int nSlot, int nX, int nY, int nW, int nH); /* Ov008_ClearGridRows */
extern int  func_ov025_02084aa4(int nSlot);                               /* Ov008_ResetEntry: slot handle */
extern void func_0203034c(TileSurface *pSurface, int hLayer, int nX, int nY, int nPalette); /* Draw_ScaledValue */
extern u16  func_ov025_0208dc74(void);                                    /* mission entry count */
extern void func_02030158(TileSurface *pSurface);                         /* Obj_InvokeInnerVtable4 */
extern void func_ov025_020a6e68(Ov008MissionList *pList);                 /* Ov008_InitMissionListLayout */
extern void func_ov025_020a6b10(Ov008MissionList *pList, int nRow, int nSound); /* Ov008_MissionListSelectRow */
extern void func_ov025_020a6750(Ov008MissionList *pList);                 /* Ov008_RefillListRows */

void func_ov025_020a8360(Ov008MissionList *pList)
{
    int hLayer;
    int i;

    func_ov025_020849d8(GRID_SLOT, 0, 0, 0x20, 0x20);
    hLayer = func_ov025_02084aa4(GRID_SLOT);
    for (i = 0; i < ROW_COUNT; i++) {
        func_0203034c(&pList->aRowNameSurface[i], hLayer, i * 4 + 2, 6, 0);
        func_0203034c(&pList->aRowInfoSurface[i], hLayer, i * 4, 6, 0);
        if (pList->bEntryGate == 0) {
            func_0203034c(&pList->aRowExtraSurface[i], hLayer, i * 4, 0x19, 0);
        }
        if (pList->bEntryGate != 0) {
            func_0203034c(&pList->aRowExtraSurface[i], hLayer, i * 4, 0x16, 0);
        }
    }
    for (i = func_ov025_0208dc74(); i < ROW_COUNT; i++) {
        func_02030158(&pList->aRowNameSurface[i]);
        func_02030158(&pList->aRowInfoSurface[i]);
        func_02030158(&pList->aRowExtraSurface[i]);
    }
    func_ov025_020a6e68(pList);
    func_ov025_020a6b10(pList, 0, 2);
    if (pList->bDirty == 0) {
        func_ov025_020a6750(pList);
    }
}
