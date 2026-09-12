/* func_ov008_0206cdb4 -- Ov008_SetScrollGaugePos: place the scroll gauge knob for
 * scroll position nPos.  With more than eight entries in the list (+0x1cc) the
 * knob offset (+0x40) is nPos * (count - 8) * 16 / (0x80 - scale), the gauge's
 * dirty slot bit is cleared and the up/down arrows (entries 3 and 4) are shown
 * while there is room to scroll in that direction.  The row content is then
 * refreshed for nPos.
 */
typedef unsigned char u8;

#define ROWS_VISIBLE  8
#define ROW_UNITS     16
#define GAUGE_SPAN    0x80
#define SLOT_GAUGE    0x1a
#define ENTRY_ARROW_UP   3
#define ENTRY_ARROW_DOWN 4

typedef struct Ov008ScrollMenu {
    u8  pad_000[0x40];
    int nKnobOffset;          /* 0x040 */
    u8  pad_044[0x4c - 0x44];
    int nGaugeScale;          /* 0x04c */
    u8  pad_050[0x1cc - 0x50];
    u8  list[12];             /* 0x1cc: NNSFndList of entries */
} Ov008ScrollMenu;

extern int  func_ov008_02050c64(void);                                   /* Ov008_GetCtxBlock4a80 */
extern void *NNS_FndGetNextListObject(void *pList, void *pObject);
extern int  func_02020400(int nNum, int nDen);                           /* _s32_div_f */
extern void func_ov008_02050b74(int nSlot);                              /* Ov008_ClearSlotBit */
extern void *func_ov008_02054788(int nBlock, int nId);                   /* FindEntryById */
extern void func_ov008_02054ba4(int nBlock, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void func_ov008_0206c7a0(Ov008ScrollMenu *pMenu, int nPos);       /* refresh rows */

void func_ov008_0206cdb4(Ov008ScrollMenu *pMenu, int nPos)
{
    int nCount;
    void *pObject;
    int nRange;
    int nSpan;
    int nBlock;
    int bShow;
    void *pEntry;

    nCount = 0;
    nBlock = func_ov008_02050c64();
    for (pObject = NNS_FndGetNextListObject(pMenu->list, 0); pObject != 0;
         pObject = NNS_FndGetNextListObject(pMenu->list, pObject)) {
        nCount++;
    }
    nSpan = GAUGE_SPAN - pMenu->nGaugeScale;
    nRange = (nCount - ROWS_VISIBLE) * ROW_UNITS;
    if (nRange > 0) {
        pMenu->nKnobOffset = func_02020400(nPos * nRange, nSpan);
        func_ov008_02050b74(SLOT_GAUGE);
        bShow = nPos > 0 ? 1 : 0;
        pEntry = func_ov008_02054788(nBlock, ENTRY_ARROW_UP);
        func_ov008_02054ba4(nBlock, pEntry, bShow);
        bShow = nPos < nSpan ? 1 : 0;
        pEntry = func_ov008_02054788(nBlock, ENTRY_ARROW_DOWN);
        func_ov008_02054ba4(nBlock, pEntry, bShow);
    }
    func_ov008_0206c7a0(pMenu, nPos);
}
