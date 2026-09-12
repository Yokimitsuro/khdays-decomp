/* func_ov008_02072c7c -- Ov008_RefreshMissionRows: unless the list is animating,
 * fill the six visible rows from the mission entries in list order; then mark
 * the list dirty and queue the upload of the three surfaces of every row that
 * was left unfilled.
 */
typedef unsigned char u8;

#define ROW_COUNT 6

typedef struct TileSurface {
    u8 pad[0x3c];
} TileSurface;

typedef struct Ov008MissionListEntry Ov008MissionListEntry;

typedef struct Ov008MissionList {
    u8          pad_000[0x48];
    int         bDirty;                  /* 0x048 */
    u8          pad_04c[0x68 - 0x4c];
    int         bAnimating;              /* 0x068 */
    u8          pad_06c[0x84 - 0x6c];
    TileSurface aRowNameSurface[ROW_COUNT];   /* 0x084 */
    TileSurface aRowInfoSurface[ROW_COUNT];   /* 0x1ec */
    TileSurface aRowExtraSurface[ROW_COUNT];  /* 0x354 */
} Ov008MissionList;

extern Ov008MissionListEntry *func_ov008_0205b650(Ov008MissionListEntry *pEntry); /* Ov008_GetNextMissionEntry */
extern void func_ov008_0206ff24(Ov008MissionList *pList, int nRow, Ov008MissionListEntry *pEntry);
extern void func_020300f8(void *pSurface);                                   /* EnqueueObjGfxCommand */

void func_ov008_02072c7c(Ov008MissionList *pList)
{
    int nRow = 0;
    Ov008MissionListEntry *pEntry;

    if (pList->bAnimating == 0) {
        for (pEntry = func_ov008_0205b650(0); pEntry != 0; pEntry = func_ov008_0205b650(pEntry)) {
            func_ov008_0206ff24(pList, nRow, pEntry);
            nRow++;
            if (nRow >= ROW_COUNT) {
                break;
            }
        }
    }
    pList->bDirty = 1;
    for (; nRow < ROW_COUNT; nRow++) {
        func_020300f8(&pList->aRowNameSurface[nRow]);
        func_020300f8(&pList->aRowInfoSurface[nRow]);
        func_020300f8(&pList->aRowExtraSurface[nRow]);
    }
}
