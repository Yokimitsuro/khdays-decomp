/* func_ov008_02073014 -- Ov008_MissionListRevealTick: reveal the mission
 * list's rows one by one during its opening animation.  With no entry left
 * at the reveal row (+0x6e), once 0x7fd88 ticks passed since the last step
 * (+0x70) the cursor widget 1 is shown, the animation phase (+0x6c) and flag
 * (+0x68) cleared and -- unless a prompt is pending (+0x78) -- the row is
 * selected (-1 when rows are tracked, else 0) and, without a scroll drag
 * (+0x48), the rows refilled.  Otherwise, in phase 1: with a pending prompt
 * every entry up to the first mission in progress (field 0x379f + 2 * tag
 * == 1) is revealed at once (row = reveal row mod 6, surfaces +0x84 / +0x1ec
 * / +0x354 queued); then, once the delay passed, the entry's mission that is
 * in progress is set to 2, the animation flag cleared, +0x7c set, the reveal
 * row selected (mode 0x17), the rows refilled without a scroll drag, the
 * flag raised again, +0x7c cleared, the reveal row advanced and the tick
 * stored.  Codegen: materialised bools for the two field tests; the second
 * delay is a u64 local chosen by a (degenerate) row test.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long long u64;

#define REVEAL_TICKS  0x7fd88
#define ROW_COUNT     6
#define FIELD_MISSION_BASE 0x379f
#define MISSION_STARTED 1
#define MISSION_DONE    2
#define SELECT_REVEAL   0x17
#define WIDGET_CURSOR   1

typedef struct TileSurface {
    u8 pad_00[0x3c];
} TileSurface;

typedef struct Ov008MissionList {
    u8  pad_000[0x38];
    int nTrackedRows;         /* 0x038 */
    u8  pad_03c[0x48 - 0x3c];
    int nScrollA;             /* 0x048 */
    u8  pad_04c[0x68 - 0x4c];
    int bAnimating;           /* 0x068 */
    u16 nAnimPhase;           /* 0x06c */
    u16 nRevealRow;           /* 0x06e */
    u64 nAnimTick;            /* 0x070 */
    int bPendingPrompt;       /* 0x078 */
    int bRevealing;           /* 0x07c */
    u8  pad_080[4];
    TileSurface aRowNameSurface[ROW_COUNT];  /* 0x084 */
    TileSurface aRowExtraSurface[ROW_COUNT]; /* 0x1ec */
    TileSurface aRowDotSurface[ROW_COUNT];   /* 0x354 */
} Ov008MissionList;

extern void *func_ov008_0205b670(int nIndex);                            /* mission list entry */
extern long long func_020031d4(void);                                    /* GetTick64 */
extern int   func_ov008_02050c64(void);                                  /* Ov008_GetCtxBlock4a80 */
extern void *func_ov008_02054788(int nCtx, int nId);                     /* FindEntryById */
extern void  func_ov008_02054ba4(int nCtx, void *pEntry, int bVisible);  /* SetEntrySlotsVisible */
extern void  func_ov008_02071618(Ov008MissionList *pList, u32 nRow, int nMode); /* Ov008_MissionListSelectRow */
extern void  func_ov008_0207126c(Ov008MissionList *pList);               /* Ov008_RefillListRows */
extern int   func_ov008_02072fe4(void *pEntry);                          /* Ov008_GetTagIndex */
extern u32   func_020235d0(int nField, int nBits);                       /* GameState_GetField */
extern void  func_020235e8(int nField, int nBits, u32 nValue);           /* GameState_SetField */
extern void  func_ov008_0206ff24(Ov008MissionList *pList, u16 nRow, void *pEntry, int nCount); /* draw a row */
extern void  func_020300f8(void *pSurface);                              /* EnqueueObjGfxCommand */

void func_ov008_02073014(Ov008MissionList *pList)
{
    void *pEntry;
    u64 nNow;
    int nCtx;
    int nTag;
    int nField;
    u16 nRow;
    int bStarted;
    int bDone;
    u64 nDelay;

    pEntry = func_ov008_0205b670(pList->nRevealRow);
    nNow = func_020031d4();
    if (pEntry == 0) {
        if (nNow < pList->nAnimTick + REVEAL_TICKS) {
            return;
        }
        nCtx = func_ov008_02050c64();
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, WIDGET_CURSOR), 1);
        pList->nAnimPhase = 0;
        pList->bAnimating = 0;
        if (pList->bPendingPrompt != 0) {
            return;
        }
        if (pList->nTrackedRows != 0) {
            func_ov008_02071618(pList, -1, -1);
        }
        if (pList->nTrackedRows == 0) {
            func_ov008_02071618(pList, 0, -1);
        }
        if (pList->nScrollA != 0) {
            return;
        }
        func_ov008_0207126c(pList);
        return;
    }
    if (pList->nAnimPhase != 1) {
        return;
    }
    if (pList->bPendingPrompt != 0) {
        do {
            nTag = func_ov008_02072fe4(pEntry);
            if (nTag >= 0) {
                nField = FIELD_MISSION_BASE + nTag * 2;
                bStarted = func_020235d0(nField, 2) >= MISSION_STARTED;
                if (bStarted) {
                    bDone = func_020235d0(nField, 2) >= MISSION_DONE;
                    if (!bDone) {
                        break;
                    }
                }
            }
            nRow = pList->nRevealRow % ROW_COUNT;
            func_ov008_0206ff24(pList, nRow, pEntry, ROW_COUNT);
            func_020300f8(&pList->aRowNameSurface[nRow]);
            func_020300f8(&pList->aRowExtraSurface[nRow]);
            func_020300f8(&pList->aRowDotSurface[nRow]);
            pList->nRevealRow++;
            pEntry = func_ov008_0205b670(pList->nRevealRow);
        } while (pEntry != 0);
    } else {
        nTag = func_ov008_02072fe4(pEntry);
    }
    if (pEntry == 0) {
        return;
    }
    /* the first row's delay is the same as the rest in this build; the retail
     * code still tests the row (its dead cmp survives in the ROM) */
    nDelay = REVEAL_TICKS;
    if (pList->nRevealRow != 0) {
        nDelay = REVEAL_TICKS;
    }
    if (nNow < pList->nAnimTick + nDelay) {
        return;
    }
    if (nTag >= 0) {
        nField = FIELD_MISSION_BASE + nTag * 2;
        bStarted = func_020235d0(nField, 2) >= MISSION_STARTED;
        if (bStarted) {
            bDone = func_020235d0(nField, 2) >= MISSION_DONE;
            if (!bDone) {
                if ((u16)func_020235d0(nField, 2) < MISSION_DONE) {
                    func_020235e8(nField, 2, MISSION_DONE);
                }
            }
        }
    }
    pList->bAnimating = 0;
    pList->bRevealing = 1;
    func_ov008_02071618(pList, pList->nRevealRow, SELECT_REVEAL);
    if (pList->nScrollA == 0) {
        func_ov008_0207126c(pList);
    }
    pList->bAnimating = 1;
    pList->bRevealing = 0;
    pList->nRevealRow++;
    pList->nAnimTick = nNow;
}
