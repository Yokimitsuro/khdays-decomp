/* func_ov025_02090140 -- Ov008_InitGridMenuWidgets: build the grid menu's
 * widget set on the widget context.  The layout template 0208f15c (word 0
 * = slot tag 8) is applied, resource 0 forwarded when present, block tag 9
 * loaded with 0x72 entries and the list nodes walked in mode 1.  Widget 3
 * gets frame 0; widgets 0x65 .. 0x78 (the grid cells), 400 .. 400 + rows
 * and 500 .. 500 + rows (the inventory rows and marks) are released and
 * reframed (rows: frame 0 then 0, marks: 1 then 0); 0x49, 0x4a and 0xc9
 * are released, 0xc9, 100 and 0x60 get frame 0 and 0x50 .. 0x5f frame 2.
 * With a single page (+0x1e78) widget 0x33 hides, and the page tabs of
 * 0208f110 hide past the page count.  Then the update callback (0205d190)
 * and the callbacks of widgets 0x35, 0x36 and 0x50 .. 0x5f are installed.
 * Codegen: the template and the tab pair are struct copies from rodata; the
 * three release loops end on the inclusive bounds; the loops keep their
 * constant arguments in registers.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ROW_WIDGET_BASE  400
#define MARK_WIDGET_BASE 500
#define ROW_WIDGET_LAST  407
#define MARK_WIDGET_LAST 507
#define CELL_WIDGET_FIRST 0x65
#define CELL_WIDGET_LAST  0x78
#define PAGE_WIDGET_FIRST 0x50
#define PAGE_WIDGET_LAST  0x5f

typedef struct Ov008LayoutTemplate {
    u32 words[4];
} Ov008LayoutTemplate;

typedef struct Ov008TabWidgetPair {
    int aWidget[2];           /* tab widgets of pages 2 and 3 */
} Ov008TabWidgetPair;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x1e78];
    int nPageCount;           /* 0x1e78 */
} Ov008MenuContext;

extern const Ov008LayoutTemplate data_ov025_020b3cbc;
extern const Ov008TabWidgetPair data_ov025_020b3c70;
extern int   func_ov025_02084a7c(void);                                 /* Ov008_GetContext */
extern u32   func_ov025_02084d18(int nMember);                          /* Ov008_PackSlotTag */
extern void  func_ov025_020883f8(int nCtx, Ov008LayoutTemplate *pLayout);
extern void *func_ov025_02084d94(int nIndex);                           /* resource by index */
extern void  func_ov025_02088410(int nCtx, void *pResource);
extern void  func_ov025_0208832c(int nCtx, void *pResource, int nCount); /* Ov008_LoadBlockProcessAndFree */
extern void  func_ov025_02088a7c(int nCtx, int nMode);                  /* Ov008_ForEachListNode */
extern void *func_ov025_0208843c(int nCtx, int nId);                    /* FindEntryById */
extern void  func_ov025_02088a38(int nCtx, void *pEntry, int nFrame);   /* set the entry frame */
extern void  func_ov025_020888b0(int nCtx, void *pEntry);               /* Ov008_ReleaseTwoSlots */
extern void  func_ov025_02088928(int nCtx, void *pEntry, int nFrame);   /* Ov008_ReleaseTwoSlotsEx */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  func_ov025_02088430(int nCtx, void *pCallback);            /* ov008_StoreWordAt0x4a50 */
extern void  func_ov025_02088420(int nCtx, int nId, void *pCallback);   /* Ov008_ResolveEntryStoreWord */
extern void  func_ov025_0208f704(void);
extern void  func_ov025_02099550(void);
extern void  func_ov025_02099554(void);
extern void  func_ov025_02099558(void);
extern void  func_ov025_020995cc(void);
extern void  func_ov025_0209962c(void);
extern void  func_ov025_02099658(void);
extern void  func_ov025_02099684(void);
extern void  func_ov025_020996b0(void);
extern void  func_ov025_02099864(void);
extern void  func_ov025_02099900(void);
extern void  func_ov025_02099930(void);
extern void  func_ov025_02099960(void);
extern void  func_ov025_02099a20(void);
extern void  func_ov025_02099990(void);
extern void  func_ov025_020999c0(void);
extern void  func_ov025_020999f0(void);

void func_ov025_02090140(Ov008MenuContext *pCtx)
{
    Ov008LayoutTemplate layout;
    Ov008TabWidgetPair tabs;
    int nCtx;
    void *pResource;
    void *pEntry;
    int i;

    layout = data_ov025_020b3cbc;
    tabs = data_ov025_020b3c70;
    nCtx = func_ov025_02084a7c();
    layout.words[0] = func_ov025_02084d18(8);
    func_ov025_020883f8(nCtx, &layout);
    pResource = func_ov025_02084d94(0);
    if (pResource != 0) {
        func_ov025_02088410(nCtx, pResource);
    }
    func_ov025_0208832c(nCtx, (void *)func_ov025_02084d18(9), 0x72);
    func_ov025_02088a7c(nCtx, 1);
    func_ov025_02088a38(nCtx, func_ov025_0208843c(nCtx, 3), 0);
    for (i = CELL_WIDGET_FIRST; i <= CELL_WIDGET_LAST; i++) {
        pEntry = func_ov025_0208843c(nCtx, i);
        func_ov025_020888b0(nCtx, pEntry);
        func_ov025_02088a38(nCtx, pEntry, 0);
    }
    for (i = ROW_WIDGET_BASE; i <= ROW_WIDGET_LAST; i++) {
        pEntry = func_ov025_0208843c(nCtx, i);
        func_ov025_020888b0(nCtx, pEntry);
        func_ov025_02088928(nCtx, pEntry, 0);
        func_ov025_02088a38(nCtx, pEntry, 0);
    }
    for (i = MARK_WIDGET_BASE; i <= MARK_WIDGET_LAST; i++) {
        pEntry = func_ov025_0208843c(nCtx, i);
        func_ov025_020888b0(nCtx, pEntry);
        func_ov025_02088928(nCtx, pEntry, 1);
        func_ov025_02088a38(nCtx, pEntry, 0);
    }
    func_ov025_020888b0(nCtx, func_ov025_0208843c(nCtx, 0x49));
    func_ov025_020888b0(nCtx, func_ov025_0208843c(nCtx, 0x4a));
    func_ov025_020888b0(nCtx, func_ov025_0208843c(nCtx, 0xc9));
    func_ov025_02088a38(nCtx, func_ov025_0208843c(nCtx, 0xc9), 0);
    func_ov025_02088a38(nCtx, func_ov025_0208843c(nCtx, 100), 0);
    func_ov025_02088a38(nCtx, func_ov025_0208843c(nCtx, 0x60), 0);
    for (i = PAGE_WIDGET_FIRST; i <= PAGE_WIDGET_LAST; i++) {
        func_ov025_02088a38(nCtx, func_ov025_0208843c(nCtx, i), 2);
    }
    if (pCtx->nPageCount == 1) {
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x33), 0);
    }
    for (i = 0; i < 2; i++) {
        if (i + 2 > pCtx->nPageCount) {
            func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, tabs.aWidget[i]), 0);
        }
    }
    func_ov025_02088430(nCtx, func_ov025_0208f704);
    func_ov025_02088420(nCtx, 0x35, func_ov025_02099550);
    func_ov025_02088420(nCtx, 0x36, func_ov025_02099554);
    func_ov025_02088420(nCtx, 0x50, func_ov025_02099558);
    func_ov025_02088420(nCtx, 0x51, func_ov025_020995cc);
    func_ov025_02088420(nCtx, 0x52, func_ov025_0209962c);
    func_ov025_02088420(nCtx, 0x53, func_ov025_02099658);
    func_ov025_02088420(nCtx, 0x54, func_ov025_02099684);
    func_ov025_02088420(nCtx, 0x55, func_ov025_020996b0);
    func_ov025_02088420(nCtx, 0x56, func_ov025_02099864);
    func_ov025_02088420(nCtx, 0x59, func_ov025_02099900);
    func_ov025_02088420(nCtx, 0x5a, func_ov025_02099930);
    func_ov025_02088420(nCtx, 0x5b, func_ov025_02099960);
    func_ov025_02088420(nCtx, 0x5c, func_ov025_02099a20);
    func_ov025_02088420(nCtx, 0x5d, func_ov025_02099990);
    func_ov025_02088420(nCtx, 0x5e, func_ov025_020999c0);
    func_ov025_02088420(nCtx, 0x5f, func_ov025_020999f0);
}
