/* Ov008_CommitSelectedPage -- commit the menu to the selected page and bring up its UI, ov008.
 * Detaches the previous page (d6f8), marks the menu committed (heap+0x18=3), unloads the old
 * UI container (Ov008_ReleaseMenuUi), rebuilds the page's cursor/help/selection widgets
 * (d6a8, 020335ec 0x1f, 02033c24 0x40/10), and for the current player's save slot pushes its
 * title (Ov008_ResetPartyMemberAndLayout from slot+4). Then loads the page layout (0205005c/020511c8) and
 * the difficulty glyph (020511f8 from Ov008_CountOccupiedSlots), and for each of the 4 slots pushes
 * its state icon (bits 1-3 of heap+slot*0x1c+0xbb) and its enabled flag (bit 0). */

#include "game/engine.h"

extern void  Ov008_ResetDisplayForPageList(void);
extern void  Ov008_ReleaseMenuUi(void);
extern void  Ov008_RefreshSeatCharacter(int a);
extern int   Slot4_GetIfOccupied(int slot);
extern void  Ov008_ResetPartyMemberAndLayout(int a, int b);
extern void  Ov008_InitCampaignMenuContext(int a);
extern void  Ov008_SetCtxField967c(unsigned int a);
extern int   Ov008_CountOccupiedSlots(void);
extern void  Ov008_SetCtxField9750(int a);
extern void  Ov008_SetCtxByte9751(unsigned int a, int b);
extern void  Ov008_SetCtxWord9758(unsigned int a, int b);
extern char *data_ov008_02090f00;
extern unsigned short gMissionNumber;
extern void  Ov008_RouteCommittedPageState(void);

struct SlotByte { unsigned char b0 : 1, b123 : 3; };

void *Ov008_CommitSelectedPage(int p1, int p2, int p3, int p4) {
    int slot;
    unsigned int i;
    int off;
    Ov008_ResetDisplayForPageList();
    *(int *)(data_ov008_02090f00 + 0x18) = 3;
    Ov008_ReleaseMenuUi();
    Ov008_RefreshSeatCharacter(Session_GetLocalPlayerIndex());
    SetSelectionIfChanged(0x1f);
    InvokeSubStructAndStampByte(0x40, 10);
    slot = Slot4_GetIfOccupied(Session_GetLocalPlayerIndex());
    if (slot != 0) {
        PartyState_ResetBuffers();
        Ov008_ResetPartyMemberAndLayout(*(int *)(slot + 4), 0);
    }
    Ov008_InitCampaignMenuContext(0);
    Ov008_SetCtxField967c(gMissionNumber);
    Ov008_SetCtxField9750((unsigned char)Ov008_CountOccupiedSlots());
    i = 0;
    off = 0;
    do {
        Ov008_SetCtxByte9751(i & 0xffff, ((struct SlotByte *)(data_ov008_02090f00 + off + 0xbb))->b123);
        Ov008_SetCtxWord9758(i, ((struct SlotByte *)(data_ov008_02090f00 + off + 0xbb))->b0);
        i++;
        off += 0x1c;
    } while ((int)i < 4);
    return (void *)Ov008_RouteCommittedPageState;
}
