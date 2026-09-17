/* func_ov025_0209e8c4 -- Ov025_Reports_InitPage: reset the reports / enemy profiles page (the first 0x278 bytes
 * of page A) and remember which set it shows: the mission-mode set (context word 02085078,
 * kept at +0x258) reads the eight 16-bit "seen" words of game field 0x3c6a, the story set those
 * of field 0x45b (GameState_GetField, 16 bits each, 0x10 apart) into +0x248; the page starts in
 * state 1 (+0xc8). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov025ReportsRow {
    void *pTitle;             /* 0x00: entry 0x33 + row */
    void *pMark1;             /* 0x04: entry 0x3d + row */
    void *pMark2;             /* 0x08: entry 0x47 + row */
    void *pMark3;             /* 0x0c: entry 0x51 + row */
    void *pMark4;             /* 0x10: entry 0x5b + row */
    void *pBadge;             /* 0x14: entry 0x6f + row */
    void *pNumber;            /* 0x18: entry 0x65 + row */
} Ov025ReportsRow;            /* 0x1c */

typedef struct Ov025ReportsPage {
    u8   pad_000[0x6c];
    u8   text[0xc];           /* 0x06c: the report / enemy strings */
    u8   surface[0x3c];       /* 0x078 */
    int  nTracker;            /* 0x0b4: the tag tracker */
    int  nCtx;                /* 0x0b8: the entry context */
    u8   pad_0bc[0xc8 - 0xbc];
    int  nState;              /* 0x0c8 */
    u8   pad_0cc[0xd0 - 0xcc];
    Ov025ReportsRow aRow[10]; /* 0x0d0 */
    void *pEntries;           /* 0x1e8: the per-report records (0x40 bytes each) */
    u8   pad_1ec[0x230 - 0x1ec];
    void *pTable;             /* 0x230: the report table file */
    void *pSpriteFile;        /* 0x234: the report sprite file */
    u8   pad_238[0x248 - 0x238];
    u16  aSeen[8];            /* 0x248: the seen bits per group */
    int  bMissionMode;        /* 0x258: enemy profiles rather than reports */
    int  nField25c;           /* 0x25c */
    void *pCell3;             /* 0x260 */
    void *pCell4;             /* 0x264 */
    void *pSelectCell;        /* 0x268 */
    void *pUpArrow;           /* 0x26c */
    void *pDownArrow;         /* 0x270 */
    void *pKnob;              /* 0x274 */
} Ov025ReportsPage;           /* 0x278: a view of page A (Ov008_GetPageA) */

extern Ov025ReportsPage *func_ov025_02084afc(void);                /* Ov008_GetPageA */
extern void  MI_CpuFill8(void *pDst, u8 nValue, u32 nSize);
extern int   func_ov025_02085078(void);                             /* Ov008_GetCtxField9768 */
extern u32   func_020235d0(int nField, int nBits);                  /* GameState_GetField */

void func_ov025_0209e8c4(void)
{
    Ov025ReportsPage *pPage;
    int i;
    u16 *pSeen;
    int nGroups;
    int nField;
    int bMissionMode;

    pPage = func_ov025_02084afc();
    pSeen = pPage->aSeen;
    MI_CpuFill8(pPage, 0, 0x278);
    bMissionMode = func_ov025_02085078();
    if (bMissionMode == 0) {
        nField = 0x45b;
        nGroups = 8;
    } else {
        nField = 0x3c6a;
        nGroups = 8;
    }
    pPage->bMissionMode = bMissionMode;
    for (i = 0; i < nGroups; i++) {
        *pSeen = func_020235d0(nField, 0x10);
        pSeen++;
        nField += 0x10;
    }
    pPage->nState = 1;
}
