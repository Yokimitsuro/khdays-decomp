/* func_ov025_020ad654 -- Ov008_MissionMenuConfirm: the mission menu's "confirm"
 * handler (its address sits in the handler table at 02090900).  Blocked while a
 * transfer is in flight but not yet acknowledged.  With no selection pending it
 * arms one: clears the cursor mode, expands the info panel and plays the select
 * sound, then clears the acknowledge word.  With a selection pending but not yet
 * armed it collapses the panel with the cancel sound; an armed selection goes
 * through to the mission start.  The middle arm re-tests the pending word (the ROM
 * keeps the redundant beq).
 */
typedef unsigned char u8;

typedef struct Ov008MissionMenu {
    u8  pad_000[8];
    int nCursorMode;          /* 0x008 */
    u8  pad_00c[0x150 - 0xc];
    int bTransfer;            /* 0x150 */
    int bTransferAcked;       /* 0x154 */
    int nAckWord;             /* 0x158 */
    u8  pad_15c[0x180 - 0x15c];
    int bSelectionPending;    /* 0x180 */
    int bSelectionArmed;      /* 0x184 */
} Ov008MissionMenu;

#define SOUND_SELECT 1
#define SOUND_CANCEL 3

extern void func_ov025_020ac2a0(Ov008MissionMenu *pMenu, int bExpand);   /* info panel slide */
extern void func_02033b78(int nKind, int nSound);                        /* PlaySound */
extern void func_ov025_020a9bc4(void);                                   /* start the mission */

void func_ov025_020ad654(Ov008MissionMenu *pMenu)
{
    if (pMenu->bTransfer != 0 && pMenu->bTransferAcked == 0) {
        return;
    }
    if (pMenu->bSelectionPending == 0) {
        pMenu->nCursorMode = 0;
        func_ov025_020ac2a0(pMenu, 1);
        func_02033b78(0, SOUND_SELECT);
        pMenu->nAckWord = 0;
    } else if (pMenu->bSelectionPending != 0 && pMenu->bSelectionArmed == 0) {
        func_ov025_020ac2a0(pMenu, 0);
        func_02033b78(0, SOUND_CANCEL);
    } else {
        func_ov025_020a9bc4();
    }
}
