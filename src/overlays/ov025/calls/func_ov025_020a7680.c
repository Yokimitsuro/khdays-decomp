/* func_ov025_020a7680 -- Ov008_MissionListOpen: prepare the mission list.  Of
 * the twelve mission slots, 0 and 4 are always open; the others lock (slot
 * value 0x333, kind 0) unless their game flag (0x3bc9 + slot) is set.  With a
 * modal object up: outside a page transition the current scroll word (u16) is
 * fed to the list; during one the mission named by the context is looked up --
 * found: its slot byte (+4) becomes the cursor slot and its selection text is
 * updated; not found: the cursor slot is cleared, and when the list has no
 * entries either, the cursor steps to the first accepted slot.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define SLOT_COUNT     12
#define FLAG_SLOT_BASE 0x3bc9
#define SLOT_LOCKED    0x333

typedef struct Ov008MissionListEntry {
    u8  pad_00[4];
    u16 nSlot;                /* 0x04 */
} Ov008MissionListEntry;

typedef struct Ov008MissionList {
    u8  pad_00[0x54];
    u8  nCursorSlot;          /* 0x54 */
} Ov008MissionList;

extern int  func_02023588(int nFlag);                                     /* GameState_IsFlagSet */
extern void func_ov025_0208dd48(int nSlot, u32 nValue, u32 nKind);        /* set a mission slot */
extern int  func_ov025_02084e08(void);                                    /* Ov008_GetCtxObject9630 */
extern int  func_ov025_02084e38(void);                                    /* page transition active */
extern u32  func_ov025_02084e74(void);                                    /* Ov008_GetCtxField9638 */
extern void func_ov025_0208dcdc(u32 nWord);                               /* Ov008_FeedScrollInput */
extern u32  func_ov025_02084ff0(void);                                    /* Ov008_GetCtxField967c */
extern Ov008MissionListEntry *func_ov025_0208dc54(u32 nMissionId);        /* find the listed mission */
extern void func_ov025_0208dc8c(int nSlot);                               /* cursor pick */
extern void func_ov025_0208da58(int nSlot, int nArg);                     /* Ov008_MainMenu_UpdateSelectionText */
extern u16  func_ov025_0208dc74(void);                                    /* mission entry count */
extern u32  func_ov025_020a5284(Ov008MissionList *pList, int nCell);      /* Ov008_StepCursorToAcceptedSlot */

void func_ov025_020a7680(Ov008MissionList *pList)
{
    int nSlot;
    int bOpen;
    Ov008MissionListEntry *pEntry;

    for (nSlot = 0; nSlot < SLOT_COUNT; nSlot++) {
        if (nSlot == 0) {
            bOpen = 1;
        } else if (nSlot == 4) {
            bOpen = 1;
        } else {
            bOpen = func_02023588(nSlot + FLAG_SLOT_BASE);
        }
        if (bOpen == 0) {
            func_ov025_0208dd48(nSlot, SLOT_LOCKED, 0);
        }
    }
    if (func_ov025_02084e08() == 0) {
        return;
    }
    if (func_ov025_02084e38() == 0) {
        func_ov025_0208dcdc((u16)func_ov025_02084e74());
        return;
    }
    if (func_ov025_02084e38() == 0) {
        return;
    }
    pEntry = func_ov025_0208dc54(func_ov025_02084ff0());
    if (pEntry != 0) {
        pList->nCursorSlot = pEntry->nSlot;
        func_ov025_0208dc8c(pList->nCursorSlot);
        func_ov025_0208da58(pList->nCursorSlot, 0);
        return;
    }
    pList->nCursorSlot = 0;
    func_ov025_0208dc8c(0);
    if (func_ov025_0208dc74() == 0 && pEntry == 0) {
        pList->nCursorSlot = func_ov025_020a5284(pList, 1);
    }
}
