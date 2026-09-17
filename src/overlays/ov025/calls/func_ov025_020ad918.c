/* func_ov025_020ad918 -- Ov025_ScrollList_BuildRows: build the day rows of the scrolling list
 * (+4, 16 bytes each, one per entry of the day table: 0208df94 entries, first day 0208df9c, name
 * string 0208dfb0).  The days go up to the current day (game-state field 9; 400 once the story
 * chapter, field 3, has reached 6; at least 8): each table entry whose successor starts within
 * the limit becomes the span first day .. next first day - 1, kept (with its name from the
 * string set +0x1c, 02089894) only when a visible mission falls inside it
 * (Ov025_MissionList_HasVisibleMissionInDays through 0208dd20); +8 counts the rows kept. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov025ScrollRow {
    int  nFirstDay;           /* 0x00: the day span of the row */
    int  nLastDay;            /* 0x04 */
    const u16 *pName;         /* 0x08 */
    int  nField0c;            /* 0x0c */
} Ov025ScrollRow;             /* 0x10 */

typedef struct Ov025ScrollList {
    int  nField000;           /* 0x000 */
    Ov025ScrollRow *pRows;    /* 0x004: the day rows */
    int  nCount;              /* 0x008 */
    int  bTouching;           /* 0x00c: the stylus holds the scroll bar */
    int  bPressed;            /* 0x010 */
    int  bRowsDirty;          /* 0x014: re-upload the row surfaces */
    int  bMarkersDirty;       /* 0x018: re-upload the marker screen */
    u8   strings[0x10];       /* 0x01c: the row name strings */
    void *pNode;              /* 0x02c: the shared UI list node */
} Ov025ScrollList;

extern int   func_ov025_0208df94(void);                             /* Ov025_DayTable_Count */
extern u16   func_ov025_0208df9c(u16 nEntry);                       /* Ov025_DayTable_FirstDay */
extern u16   func_ov025_0208dfb0(u16 nEntry);                       /* Ov025_DayTable_NameString */
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern u32   func_020235d0(int nField, int nBits);                  /* GameState_GetField */
extern int   func_ov025_0208dd20(u16 nFirstDay, u16 nLastDay);      /* Ov025_HasVisibleMissionInDays */
extern const u16 *func_ov025_02089894(void *pStrings, int nIndex);  /* Ov025_GetString */

void func_ov025_020ad918(Ov025ScrollList *pList)
{
    int nEntries;
    Ov025ScrollRow *pRow;
    int i;
    int nDayLimit;
    int nNextDay;

    nEntries = func_ov025_0208df94();
    pList->nCount = 0;
    pList->pRows = NNSi_FndAllocFromDefaultExpHeap(nEntries * sizeof(Ov025ScrollRow));
    if (func_020235d0(0x44e, 3) < 6) {
        nDayLimit = func_020235d0(0, 9);
    } else {
        nDayLimit = 400;
    }
    pRow = pList->pRows;
    if (nDayLimit < 8) {
        nDayLimit = 8;
    }
    for (i = 0; i < nEntries - 1; i++) {
        nNextDay = func_ov025_0208df9c(i + 1);
        if (nDayLimit < nNextDay) {
            return;
        }
        pRow->nFirstDay = func_ov025_0208df9c(i);
        pRow->nLastDay = nNextDay - 1;
        if (func_ov025_0208dd20(pRow->nFirstDay, pRow->nLastDay) != 0) {
            pRow->pName = func_ov025_02089894(pList->strings, func_ov025_0208dfb0(i));
            pRow++;
            pList->nCount++;
        }
    }
}
