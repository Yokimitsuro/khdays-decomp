/* func_ov025_020a73e0 -- Ov025_MissionList_Confirm: the A button on the mission list.  With no
 * selection (+0 < 0) the list's back entry (0208dbfc) leaves the menu when it is one (ov002
 * 0206d970 with its negated payload +0xa, target -1 / -1; 02084798) with the confirm sound
 * (02033b78 0 / 1), else the refusal sound (0 / 4).  Otherwise the selected entry (0208dbdc) is
 * refused when its rank (game-state field 0x28e4 + 3 * id) is 2 or more outside the 9630
 * object (02084e08), or, during a page transition (02084e38), when 020a50d8 (entry gate up,
 * +0x40) / 020a50d0 reject it; else it becomes the current mission (02084fd8), the selection and
 * scroll are saved to fields 0x35cd / 0x35df (8 bits each) and entry 2 opens (02084830) with
 * the confirm sound. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008MissionListEntry {
    u16  nWord;               /* 0x00 */
    u16  missionId;           /* 0x02 */
    u8   pad_04[6];
    u16  nBackPayload;        /* 0x0a: the payload of the back entry, negated for ov002 */
    u8   pad_0c[4];
    int  bBackEntry;          /* 0x10 */
} Ov008MissionListEntry;

typedef struct Ov008MissionList {
    int  nSelected;           /* 0x000 */
    int  nPrevSelected;       /* 0x004 */
    int  nCursorRow;          /* 0x008 */
    int  nScroll;             /* 0x00c: in pixels, 32 a row */
    u8   pad_010[0x40 - 0x10];
    int  bEntryGate;          /* 0x040 */
} Ov008MissionList;

extern Ov008MissionListEntry *func_ov025_0208dbfc(void);            /* the back entry of the list */
extern Ov008MissionListEntry *func_ov025_0208dbdc(int nIndex);      /* mission list entry */
extern void  func_ov002_0206d970(int nPayload);                     /* leave the menu */
extern void  func_ov025_02084798(int nEntry, int nTarget);          /* Ov008_SetTargetSlot */
extern void  func_02033b78(int nKind, int nSound);                  /* PlaySound */
extern int   func_ov025_02084e08(void);                             /* Ov008_GetCtxObject9630 */
extern int   func_ov025_02084e38(void);                             /* Ov025_GetCtxObject9634: page transition */
extern u32   func_020235d0(int nField, int nBits);                  /* GameState_GetField */
extern int   func_ov025_020a50d8(Ov008MissionList *pList, Ov008MissionListEntry *pEntry); /* IsField8LeField57 */
extern int   func_ov025_020a50d0(Ov008MissionList *pList, Ov008MissionListEntry *pEntry); /* ov008_helper_6fb2c (ignores its arguments) */
extern void  func_ov025_02084fd8(int nMission);                     /* Ov025_SetCtxField967c */
extern void  func_020235e8(int nField, int nBits, u32 nValue);      /* GameState_SetField */
extern void  func_ov025_02084830(int nEntry);                       /* Ov025_SetGlobalConfigAndInit */

void func_ov025_020a73e0(Ov008MissionList *pList)
{
    Ov008MissionListEntry *pEntry;
    int bLocked;

    if (pList->nSelected >= 0) {
        bLocked = 0;
        pEntry = func_ov025_0208dbdc(pList->nSelected);
        if (func_ov025_02084e08() == 0) {
            if (func_020235d0(pEntry->missionId * 3 + 0x28e4, 3) >= 2) {
                bLocked = 1;
            }
        } else if (func_ov025_02084e38() != 0) {
            if (pList->bEntryGate != 0) {
                if (func_ov025_020a50d8(pList, pEntry) == 0) {
                    bLocked = 1;
                }
            } else {
                if (func_ov025_020a50d0(pList, pEntry) == 0) {
                    bLocked = 1;
                }
            }
        }
        if (bLocked == 0) {
            func_ov025_02084fd8(func_ov025_0208dbdc(pList->nSelected)->missionId);
            func_020235e8(0x35cd, 8, (u16)pList->nSelected);
            func_020235e8(0x35df, 8, (u16)pList->nScroll);
            func_ov025_02084830(2);
            func_02033b78(0, 1);
        } else {
            func_02033b78(0, 4);
        }
    } else {
        pEntry = func_ov025_0208dbfc();
        if (pEntry->bBackEntry != 0) {
            func_ov002_0206d970(-pEntry->nBackPayload);
            func_ov025_02084798(-1, -1);
            func_02033b78(0, 1);
        } else {
            func_02033b78(0, 4);
        }
    }
}
