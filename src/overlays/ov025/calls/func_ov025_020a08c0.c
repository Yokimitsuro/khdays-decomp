/* func_ov025_020a08c0 -- Ov025_Reports_Teardown: leave the reports / enemy profiles page.  The
 * sprite file (+0x234), string set (+0x6c; 02089884), text surface (+0x78; 0202ffbc), tag
 * tracker (+0xb4; 020895b8) and entry context (+0xb8; 020883a0 / 020883d4) are released, the
 * main BG1..BG3 screens blanked, and the eight seen words (+0x248) or-ed with the owned words
 * (+0x238) are written back to game-state field 0x45b (reports) / 0x3c6a (enemy profiles), 16
 * bits each, 0x10 apart (GameState_SetField 020235e8).  In enemy-profile mode the six lines
 * allocated per record (+0x28) are freed; then the records (+0x1e8) and the table (+0x230), and
 * the 3D offset is reset (G3X_SetHOffset). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov025ReportsEntry {
    u16  nId : 9;             /* 0x00 bits 0-8 */
    u16  nFlag9 : 1;          /* 0x00 bit 9 */
    u16  nPending : 6;        /* 0x00 bits 10-15: enemies still to defeat */
    u8   pad_02[0xa];
    struct Ov025ReportsEntry *pRead; /* 0x0c: the read variant of the record, if any */
    u8   pad_10[0x18];
    void *apLine[6];          /* 0x28: one line per chapter (enemy profiles: allocated) */
} Ov025ReportsEntry;          /* 0x40 */

typedef struct Ov025ReportsPage {
    s16  nTop;                /* 0x000: the first visible report */
    s16  nCursor;             /* 0x002 */
    s16  nCount;              /* 0x004 */
    s16  nField06;            /* 0x006 */
    u8   list[0x64];          /* 0x008 */
    u8   text[0xc];           /* 0x06c: the report / enemy strings */
    u8   surface[0x3c];       /* 0x078 */
    int  nTracker;            /* 0x0b4: the tag tracker */
    int  nCtx;                /* 0x0b8: the entry context */
    u8   pad_0bc[0x1e8 - 0xbc];
    Ov025ReportsEntry *pEntries; /* 0x1e8: the per-report records */
    u8   pad_1ec[0x230 - 0x1ec];
    const u32 *pTable;        /* 0x230: the report table file (its first word counts the records) */
    void *pSpriteFile;        /* 0x234: the report sprite file */
    u16  aOwned[8];           /* 0x238: the owned bits per group (Ov025_QueryItemFlags) */
    u16  aSeen[8];            /* 0x248: the seen bits per group */
    int  bMissionMode;        /* 0x258: enemy profiles rather than reports */
} Ov025ReportsPage;

extern Ov025ReportsPage *func_ov025_02084afc(void);                 /* Ov008_GetPageA */
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void  func_ov025_02089884(void *pText);                      /* Ov025_ReleaseStringSet */
extern void  func_0202ffbc(void *pSurface);                         /* TileSurface_Release */
extern void  func_ov025_020895b8(int nTracker);                     /* Ov025_TagTracker_Clear */
extern void  func_ov025_020883a0(int nCtx);                         /* Ov025_ReleaseEntryList */
extern void  func_ov025_020883d4(int nCtx);                         /* Ov025_ReleaseEntryLayout */
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void  MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);
extern void  func_020235e8(int nField, int nBits, u32 nValue);      /* GameState_SetField */
extern void  G3X_SetHOffset(int nOffset);

void func_ov025_020a08c0(void)
{
    Ov025ReportsPage *pPage;
    int i;
    u16 *pSeen;
    u16 *pOwned;
    int nGroups;
    int nField;
    u32 j;
    Ov025ReportsEntry *pEntry;

    pPage = func_ov025_02084afc();
    if (pPage->bMissionMode == 0) {
        nField = 0x45b;
        nGroups = 8;
    } else {
        nField = 0x3c6a;
        nGroups = 8;
    }
    NNSi_FndFreeFromDefaultHeap(pPage->pSpriteFile);
    func_ov025_02089884(pPage->text);
    func_0202ffbc(pPage->surface);
    func_ov025_020895b8(pPage->nTracker);
    func_ov025_020883a0(pPage->nCtx);
    func_ov025_020883d4(pPage->nCtx);
    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
    pSeen = pPage->aSeen;
    pOwned = pPage->aOwned;
    for (i = 0; i < nGroups; i++) {
        func_020235e8(nField, 0x10, *pSeen | *pOwned);
        pSeen++;
        pOwned++;
        nField += 0x10;
    }
    if (pPage->bMissionMode == 1) {
        pEntry = pPage->pEntries;
        for (j = 0; j < *pPage->pTable; j++) {
            for (i = 0; i < 6; i++) {
                if (pEntry->apLine[i] != 0) {
                    NNSi_FndFreeFromDefaultHeap(pEntry->apLine[i]);
                }
            }
            pEntry++;
        }
    }
    NNSi_FndFreeFromDefaultHeap(pPage->pEntries);
    NNSi_FndFreeFromDefaultHeap(pPage->pTable);
    G3X_SetHOffset(0);
}
