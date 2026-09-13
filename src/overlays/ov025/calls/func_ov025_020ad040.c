/* func_ov025_020ad040 -- Ov008_MissionMenuStep: move the mission menu's cursor
 * (+0x179) by nStep entries, wrapping over the entry count (+0x178), to the
 * next selectable entry.  A candidate is refused when its list entry is null;
 * without a modal object when the mission's status field (0x28e4 + 3 * id) is
 * already 2 or more; with one during a page transition when the transfer flag
 * (+0x150) is set and the entry's rank exceeds the menu's cap byte, or when it
 * is clear and the helper 020742ec answers 0.  The first accepted entry becomes
 * the cursor and its mission id goes into the context; then the selection text
 * is refreshed for the entry's text slot, and the menu's rows and the panel
 * for the current page (+0x4) are redrawn.  The wrap uses _s32_div_f's
 * remainder (the high word of the 64-bit return); the status test is kept as a
 * materialised bool (cmp/movcs/movcc).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define FIELD_MISSION_STATUS 0x28e4

typedef struct Ov008MissionListEntry {
    u8  pad_00[2];
    u16 missionId;            /* 0x02 */
    u16 nTextSlot;            /* 0x04 */
} Ov008MissionListEntry;

typedef struct Ov008MissionMenu {
    u8  pad_000[4];
    int nPage;                /* 0x004 */
    u8  pad_008[0x150 - 0x8];
    int bTransfer;            /* 0x150 */
    u8  pad_154[0x178 - 0x154];
    u8  nCount;               /* 0x178 */
    u8  nCursor;              /* 0x179 */
} Ov008MissionMenu;

extern int  func_ov025_02084e08(void);                                    /* Ov008_GetCtxObject9630 */
extern int  func_ov025_02084e38(void);                                    /* page transition active */
extern long long func_02020400(int nNum, int nDen);                       /* _s32_div_f: remainder in the high word */
extern Ov008MissionListEntry *func_ov025_0208dbdc(int nIndex);
extern u32  func_020235d0(int nField, int nBits);                         /* GameState_GetField */
extern int  func_ov025_020a98f4(Ov008MissionMenu *pMenu, Ov008MissionListEntry *pEntry); /* rank <= cap */
extern int  func_ov025_020a98ec(Ov008MissionMenu *pMenu, Ov008MissionListEntry *pEntry); /* helper (ignores its arguments) */
extern void func_ov025_02084fd8(u32 nMissionId);                          /* Ov008_SetCtxField967c */
extern void func_ov025_0208da58(int nSlot, int bLocked);                  /* Ov008_MainMenu_UpdateSelectionText */
extern void func_ov025_020ab7b0(Ov008MissionMenu *pMenu);                 /* redraw rows */
extern void func_ov025_020abdd8(Ov008MissionMenu *pMenu, int nPage);      /* redraw page panel */

void func_ov025_020ad040(Ov008MissionMenu *pMenu, int nStep)
{
    Ov008MissionListEntry *pEntry;
    int bModal;
    int i;
    int bOk;
    int bTransition;
    int nIndex;
    int bDone;

    bModal = func_ov025_02084e08();
    bTransition = func_ov025_02084e38();
    nIndex = pMenu->nCursor + nStep;
    for (i = 0; i < pMenu->nCount; i++) {
        bOk = 1;
        nIndex = (int)(func_02020400(nIndex + pMenu->nCount, pMenu->nCount) >> 32);
        pEntry = func_ov025_0208dbdc(nIndex);
        if (pEntry == 0) {
            bOk = 0;
        }
        if (bModal == 0) {
            bDone = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
            if (bDone) {
                bOk = 0;
            }
        }
        if (bModal != 0 && bTransition != 0) {
            if (pMenu->bTransfer != 0) {
                if (func_ov025_020a98f4(pMenu, pEntry) == 0) {
                    bOk = 0;
                }
            }
            if (pMenu->bTransfer == 0) {
                if (func_ov025_020a98ec(pMenu, pEntry) == 0) {
                    bOk = 0;
                }
            }
        }
        if (bOk) {
            pMenu->nCursor = nIndex;
            func_ov025_02084fd8(pEntry->missionId);
            break;
        }
        nIndex += nStep;
    }
    func_ov025_0208da58(pEntry->nTextSlot, 0);
    func_ov025_020ab7b0(pMenu);
    func_ov025_020abdd8(pMenu, pMenu->nPage);
}
