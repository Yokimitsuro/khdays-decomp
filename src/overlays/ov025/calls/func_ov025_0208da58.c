/*
 * Ov008_MainMenu_UpdateSelectionText - update the selected menu entry and redraw its caption.
 * Before the delayed refresh is armed, or when the same entry remains selected, it only caches
 * the pending entry and transition mode. Otherwise it starts the selection transition, chooses
 * the locked fallback text or the entry-specific record, remeasures it, draws it, and flushes
 * the tile-text surface.
 */
typedef unsigned char u8;
typedef unsigned int u32;

extern u8 *func_ov025_02084afc(void);
extern void func_ov025_0208eae0(void *state, u32 entryId, int fastTransition);
extern void func_02030158(void *surface);
extern int func_02023588(int flagId);
extern void *func_ov025_02089894(void *records, int index);
extern void func_ov025_0208d408(void *surface, void *text);
extern void *WM_EndKeySharing_0x0208a26c(void *list, u32 entryId);
extern void func_02030278(void *surface, int x, int y, int mode,
                          void *text, int shadow);
extern void func_020300f8(void *surface);

void func_ov025_0208da58(u32 entryId, int fastTransition)
{
    u8 *menuContext = func_ov025_02084afc();
    int isEntryUnlocked;
    void *textRecord;

    if (*(int *)(menuContext + 0x14dc) == 0 ||
        *(u32 *)(menuContext + 0x14ec) == entryId) {
        goto cache_only;
    }

    func_ov025_0208eae0(menuContext + 4, entryId, fastTransition);
    *(u32 *)(menuContext + 0x14ec) = entryId;
    func_02030158(menuContext + 0x145c);

    isEntryUnlocked = func_02023588(entryId + 0x3bc9);
    if (entryId == 0) {
        isEntryUnlocked = 1;
    }
    if (entryId == 4) {
        isEntryUnlocked = 1;
    }

    if (isEntryUnlocked == 0) {
        textRecord = func_ov025_02089894(menuContext + 0x14f4, 4);
        func_ov025_0208d408(menuContext + 0x145c, textRecord);
    }
    if (isEntryUnlocked == 0) {
        textRecord = func_ov025_02089894(menuContext + 0x14f4, 4);
        func_02030278(menuContext + 0x145c, 2, 3, 1, textRecord, 0);
    }
    if (isEntryUnlocked != 0) {
        textRecord = WM_EndKeySharing_0x0208a26c(menuContext + 0x13fc, entryId);
        func_ov025_0208d408(menuContext + 0x145c, textRecord);
    }
    if (isEntryUnlocked != 0) {
        textRecord = WM_EndKeySharing_0x0208a26c(menuContext + 0x13fc, entryId);
        func_02030278(menuContext + 0x145c, 2, 3, 1, textRecord, 0);
    }
    func_020300f8(menuContext + 0x145c);
    return;

cache_only:
    *(u32 *)(menuContext + 0x14e8) = entryId;
    *(int *)(menuContext + 0x14e4) = fastTransition;
}
