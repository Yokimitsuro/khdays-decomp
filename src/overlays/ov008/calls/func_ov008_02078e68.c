/* func_ov008_02078e68 -- Ov008_DestroyPageB: tear page B down.  The seven
 * row lists (+0x38, 0x3c each) drop their sub-buffers, the text cache
 * (+0x1dc) is released, the tag-tracker nodes 0x15..0x17 of block 954c are
 * disarmed and its element list cleared, the ov025 list (+0x200) destroyed,
 * the archive buffer (+0x1fc) freed and the two archive handles (+0x34,
 * +0x30) released.  Without a cue request (word 3 of the request block) the
 * main master brightness goes to 0 unless the page's flag at +0x8 is set, and
 * slot bit 0x1b is cleared; with one, control value 1 is applied and 02050ab8
 * called.  Finally the 32 x 24 grids of slots 0x18..0x1b are cleared and the
 * sub engine's four BG screens wiped.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ROW_LIST_COUNT 7
#define GRID_W 0x20
#define GRID_H 0x18
#define SCREEN_BYTES 0x800

typedef struct Ov008CueRequest {
    int aWord[4];
} Ov008CueRequest;

typedef struct Ov008RowList {
    u8 pad[0x3c];
} Ov008RowList;

typedef struct Ov008PageB {
    u8  pad_000[8];
    int bKeepBrightness;      /* 0x008 */
    u8  pad_00c[0x30 - 0xc];
    void *hArchive;           /* 0x030 */
    void *hArchiveAlt;        /* 0x034 */
    Ov008RowList aRowList[ROW_LIST_COUNT]; /* 0x038 */
    u8  textCache[0xc];       /* 0x1dc */
    u8  pad_1e8[0x1fc - 0x1e8];
    void *pArchive;           /* 0x1fc */
    u8  list[4];              /* 0x200: ov025 list */
} Ov008PageB;

extern Ov008PageB *func_ov008_02050cec(void);                             /* Ov008_GetPageB */
extern int  func_ov008_02050c3c(void);                                    /* Ov008_GetCtxBlock954c */
extern void func_0202ffbc(void *pList);                                   /* FreeAllListNodeSubBuffers */
extern void func_ov008_02055c74(void *pCache);                            /* release a text cache */
extern int  func_ov008_02055a8c(int nOwner, u32 nTag);                    /* ov008_FindActiveEntryByTag */
extern void func_ov008_02055aec(int nOwner, int nEntry, int bArmed);      /* SetTagTrackerNodeArmed */
extern void func_ov008_020559a8(int nBlock);                              /* clear the element list */
extern void func_ov025_020b0814(void *pList);                             /* destroy the list */
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_02024fd4(void *hResource);                               /* ZeroHalfThenFree */
extern Ov008CueRequest *func_ov008_02051198(void);                        /* Ov008_GetCueRequest */
extern void func_0201e374(int nBrightness);                               /* SetMasterBrightnessMain */
extern void func_ov008_02050b74(int nSlot);                               /* Ov008_ClearSlotBit */
extern void func_ov008_02050a64(int nValue);                              /* Ov008_ApplyControlValue */
extern void func_ov008_02050ab8(int nValue);
extern void func_ov008_02050bb0(int nSlot, int nX, int nY, int nW, int nH); /* Ov008_ClearGridRows */
extern void *G2S_GetBG0ScrPtr(void);
extern void *G2S_GetBG1ScrPtr(void);
extern void *G2S_GetBG2ScrPtr(void);
extern void *G2S_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);

void func_ov008_02078e68(void)
{
    u8 i;
    Ov008PageB *pPage;
    int nOwner;

    pPage = func_ov008_02050cec();
    nOwner = func_ov008_02050c3c();
    for (i = 0; i < ROW_LIST_COUNT; i++) {
        func_0202ffbc(&pPage->aRowList[i]);
    }
    func_ov008_02055c74(pPage->textCache);
    func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, 0x15), 0);
    func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, 0x16), 0);
    func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, 0x17), 0);
    func_ov008_020559a8(nOwner);
    func_ov025_020b0814(pPage->list);
    if (pPage->pArchive != 0) {
        NNSi_FndFreeFromDefaultHeap(pPage->pArchive);
        pPage->pArchive = 0;
    }
    func_02024fd4(pPage->hArchiveAlt);
    func_02024fd4(pPage->hArchive);
    if (func_ov008_02051198()->aWord[3] == 0) {
        if (pPage->bKeepBrightness == 0) {
            func_0201e374(0);
        }
        func_ov008_02050b74(0x1b);
    } else {
        func_ov008_02050a64(1);
        func_ov008_02050ab8(1);
    }
    func_ov008_02050bb0(0x18, 0, 0, GRID_W, GRID_H);
    func_ov008_02050bb0(0x19, 0, 0, GRID_W, GRID_H);
    func_ov008_02050bb0(0x1a, 0, 0, GRID_W, GRID_H);
    func_ov008_02050bb0(0x1b, 0, 0, GRID_W, GRID_H);
    MIi_CpuClearFast(0, G2S_GetBG0ScrPtr(), SCREEN_BYTES);
    MIi_CpuClearFast(0, G2S_GetBG1ScrPtr(), SCREEN_BYTES);
    MIi_CpuClearFast(0, G2S_GetBG2ScrPtr(), SCREEN_BYTES);
    MIi_CpuClearFast(0, G2S_GetBG3ScrPtr(), SCREEN_BYTES);
}
