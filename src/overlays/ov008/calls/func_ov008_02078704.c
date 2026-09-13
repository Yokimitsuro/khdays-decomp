/* func_ov008_02078704 -- Ov008_RefreshPageBRow: redraw page B's current row
 * and re-arm its scroll trackers.  Slot 0x1a's 32 x 24 grid and the sub BG2
 * screen are cleared, the row graphics uploaded, and the tag-tracker nodes
 * 0x15 (up), 0x16 (down) and 0x17 (select) of block 954c disarmed.  With a
 * cue request pending (word 3) both scroll nodes are rewound and re-armed
 * when the ov025 list (+0x200) holds more than one entry.  Otherwise the up
 * node is rewound and armed when the row (+0x1e8) is not the first, the
 * select node armed when it is the last, or the down node rewound and armed
 * when more rows follow.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define TAG_UP     0x15
#define TAG_DOWN   0x16
#define TAG_SELECT 0x17

typedef struct Ov008CueRequest {
    int aWord[4];
} Ov008CueRequest;

typedef struct Ov008PageB {
    u8  pad_000[0x1e8];
    int nRow;                 /* 0x1e8 */
    u8  pad_1ec[0x200 - 0x1ec];
    u8  list[4];              /* 0x200: ov025 list */
} Ov008PageB;

extern Ov008PageB *func_ov008_02050cec(void);                             /* Ov008_GetPageB */
extern int   func_ov008_02050c3c(void);                                   /* Ov008_GetCtxBlock954c */
extern void  func_ov008_02050bb0(int nSlot, int nX, int nY, int nW, int nH); /* Ov008_ClearGridRows */
extern void *G2S_GetBG2ScrPtr(void);
extern void  MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);
extern void  func_ov008_020785cc(void);                                   /* Ov008_LoadPageBRowGraphics */
extern int   func_ov008_02055a8c(int nOwner, u32 nTag);                   /* ov008_FindActiveEntryByTag */
extern void  func_ov008_02055aec(int nOwner, int nEntry, int bArmed);     /* SetTagTrackerNodeArmed */
extern void  func_ov008_02055b64(int nOwner, int nEntry);                 /* RewindTagTrackerNode */
extern short func_ov025_020b0850(void *pList);                            /* list entry count */
extern Ov008CueRequest *func_ov008_02051198(void);                        /* Ov008_GetCueRequest */

void func_ov008_02078704(void)
{
    int nOwner;
    u32 nCount;
    Ov008PageB *pPage;

    pPage = func_ov008_02050cec();
    nOwner = func_ov008_02050c3c();
    func_ov008_02050bb0(0x1a, 0, 0, 0x20, 0x18);
    MIi_CpuClearFast(0, G2S_GetBG2ScrPtr(), 0x800);
    func_ov008_020785cc();
    func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, TAG_UP), 0);
    func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, TAG_DOWN), 0);
    func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, TAG_SELECT), 0);
    nCount = func_ov025_020b0850(pPage->list);
    if (func_ov008_02051198()->aWord[3] != 0) {
        if (nCount > 1) {
            func_ov008_02055b64(nOwner, func_ov008_02055a8c(nOwner, TAG_UP));
            func_ov008_02055b64(nOwner, func_ov008_02055a8c(nOwner, TAG_DOWN));
            func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, TAG_UP), 1);
            func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, TAG_DOWN), 1);
        }
        return;
    }
    if (pPage->nRow != 0) {
        func_ov008_02055b64(nOwner, func_ov008_02055a8c(nOwner, TAG_UP));
        func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, TAG_UP), 1);
    }
    if (pPage->nRow + 1 == nCount) {
        func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, TAG_SELECT), 1);
    } else if (pPage->nRow + 1 < nCount) {
        func_ov008_02055b64(nOwner, func_ov008_02055a8c(nOwner, TAG_DOWN));
        func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, TAG_DOWN), 1);
    }
}
