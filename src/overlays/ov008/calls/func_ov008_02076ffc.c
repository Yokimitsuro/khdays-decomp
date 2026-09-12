/* func_ov008_02076ffc -- Ov008_MissionMenuRefreshEntries: recount the mission
 * menu's entries.  During a transfer (+0x150) the current mission's entry (by
 * id) gets its text slot picked (0205b720) and shown, and the mission summary
 * is recalculated.  Then the entry count (+0x178) is taken from the list, the
 * "all locked" word (+0x17c) is set, and every listed entry is walked: the
 * entry of the current mission id becomes the cursor (+0x179); a normal entry
 * (not special, flag bit 1 clear) clears "all locked"; and an entry that is
 * selectable -- see Ov008_MissionMenuStep for the same gates: status field
 * 0x28e4 + 3 * id below 2 without a modal object, or during a transition the
 * rank cap / helper 020742ec -- bumps the selectable count (+0x17a).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define FIELD_MISSION_STATUS 0x28e4
#define ENTRY_FLAG_LOCKED    2

typedef struct Ov008MissionListEntry {
    u8  pad_00[2];
    u16 missionId;            /* 0x02 */
    u16 nTextSlot;            /* 0x04 */
    u8  pad_06[6];
    u8  bSpecial;             /* 0x0c */
    u8  pad_0d[7];
    u8  nFlags;               /* 0x14 */
} Ov008MissionListEntry;

typedef struct Ov008MissionMenu {
    u8  pad_000[0x150];
    int bTransfer;            /* 0x150 */
    u8  pad_154[0x178 - 0x154];
    u8  nCount;               /* 0x178 */
    u8  nCursor;              /* 0x179 */
    u8  nSelectable;          /* 0x17a */
    u8  pad_17b;
    int bAllLocked;           /* 0x17c */
} Ov008MissionMenu;

extern u32  func_ov008_020511e0(void);                                    /* Ov008_GetCtxField967c: current mission id */
extern int  func_ov008_02050ff8(void);                                    /* Ov008_GetCtxObject9630 */
extern int  func_ov008_02051028(void);                                    /* page transition active */
extern Ov008MissionListEntry *func_ov008_0205b6e8(u32 nMissionId);        /* find the listed mission */
extern void func_ov008_0205b720(int nSlot);                               /* cursor pick */
extern void func_ov008_0205b4ec(int nSlot, int bLocked);                  /* Ov008_MainMenu_UpdateSelectionText */
extern void func_ov008_0205b7fc(void);                                    /* Ov008_MainMenu_RecalculateMissionSummary */
extern u16  func_ov008_0205b708(void);                                    /* mission entry count */
extern Ov008MissionListEntry *func_ov008_0205b650(Ov008MissionListEntry *pEntry); /* Ov008_GetNextMissionEntry */
extern u32  func_020235d0(int nField, int nBits);                         /* GameState_GetField */
extern int  func_ov008_020742f4(Ov008MissionMenu *pMenu, Ov008MissionListEntry *pEntry); /* rank <= cap */
extern int  func_ov008_020742ec(Ov008MissionMenu *pMenu, Ov008MissionListEntry *pEntry); /* helper (ignores its arguments) */

void func_ov008_02076ffc(Ov008MissionMenu *pMenu)
{
    u32 nMissionId;
    int i;
    int bModal;
    int bTransition;
    int nSlot;
    Ov008MissionListEntry *pEntry;
    int bOk;
    int bDone;

    nMissionId = func_ov008_020511e0();
    bModal = func_ov008_02050ff8();
    bTransition = func_ov008_02051028();
    if (pMenu->bTransfer != 0) {
        pEntry = func_ov008_0205b6e8(nMissionId);
        if (pEntry != 0) {
            nSlot = pEntry->nTextSlot;
            func_ov008_0205b720(nSlot);
            func_ov008_0205b4ec(nSlot, 0);
        }
        func_ov008_0205b7fc();
    }
    pMenu->nCount = func_ov008_0205b708();
    i = 0;
    pMenu->bAllLocked = 1;
    for (pEntry = func_ov008_0205b650(0); pEntry != 0; pEntry = func_ov008_0205b650(pEntry)) {
        if (pEntry->missionId == nMissionId) {
            pMenu->nCursor = i;
        }
        if (pEntry->bSpecial == 0 && (pEntry->nFlags & ENTRY_FLAG_LOCKED) == 0) {
            pMenu->bAllLocked = 0;
        }
        bOk = 1;
        if (bModal == 0) {
            bDone = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
            if (bDone) {
                bOk = 0;
            }
        }
        if (bModal != 0 && bTransition != 0) {
            if (pMenu->bTransfer != 0) {
                if (func_ov008_020742f4(pMenu, pEntry) == 0) {
                    bOk = 0;
                }
            }
            if (pMenu->bTransfer == 0) {
                if (func_ov008_020742ec(pMenu, pEntry) == 0) {
                    bOk = 0;
                }
            }
        }
        if (bOk) {
            pMenu->nSelectable++;
        }
        i++;
    }
}
