/* func_ov008_02072114 -- Ov008_MissionListOpen: prepare the mission list.  Of
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
extern void func_ov008_0205b7d0(int nSlot, u32 nValue, u32 nKind);        /* set a mission slot */
extern int  func_ov008_02050ff8(void);                                    /* Ov008_GetCtxObject9630 */
extern int  func_ov008_02051028(void);                                    /* page transition active */
extern u32  func_ov008_02051064(void);                                    /* Ov008_GetCtxField9638 */
extern void func_ov008_0205b770(u32 nWord);                               /* Ov008_FeedScrollInput */
extern u32  func_ov008_020511e0(void);                                    /* Ov008_GetCtxField967c */
extern Ov008MissionListEntry *func_ov008_0205b6e8(u32 nMissionId);        /* find the listed mission */
extern void func_ov008_0205b720(int nSlot);                               /* cursor pick */
extern void func_ov008_0205b4ec(int nSlot, int nArg);                     /* Ov008_MainMenu_UpdateSelectionText */
extern u16  func_ov008_0205b708(void);                                    /* mission entry count */
extern u32  func_ov008_0206fce0(Ov008MissionList *pList, int nCell);      /* Ov008_StepCursorToAcceptedSlot */

void func_ov008_02072114(Ov008MissionList *pList)
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
            func_ov008_0205b7d0(nSlot, SLOT_LOCKED, 0);
        }
    }
    if (func_ov008_02050ff8() == 0) {
        return;
    }
    if (func_ov008_02051028() == 0) {
        func_ov008_0205b770((u16)func_ov008_02051064());
        return;
    }
    if (func_ov008_02051028() == 0) {
        return;
    }
    pEntry = func_ov008_0205b6e8(func_ov008_020511e0());
    if (pEntry != 0) {
        pList->nCursorSlot = pEntry->nSlot;
        func_ov008_0205b720(pList->nCursorSlot);
        func_ov008_0205b4ec(pList->nCursorSlot, 0);
        return;
    }
    pList->nCursorSlot = 0;
    func_ov008_0205b720(0);
    if (func_ov008_0205b708() == 0 && pEntry == 0) {
        pList->nCursorSlot = func_ov008_0206fce0(pList, 1);
    }
}
