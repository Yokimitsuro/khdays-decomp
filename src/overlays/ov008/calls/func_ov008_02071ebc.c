/* func_ov008_02071ebc -- Ov008_MissionListSelect: start the selected mission.
 * Nothing with no selection.  The pick is refused (cue 4) when: without a modal
 * object the mission's status field (0x28e4 + 3 * id) is already 2 or more;
 * with one, during a page transition, either the list's entry gate (+0x40) is
 * set and the entry's rank (+8) exceeds the list's cap byte (+0x57), or the
 * gate is clear and the helper 0206fb2c answers 0.  Otherwise the mission id is
 * stored in the context, the selected row and the scroll (+0xc) are saved to
 * the 8-bit fields 0x35cd / 0x35df, global config 2 is initialised and cue 1
 * plays.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define FIELD_MISSION_STATUS 0x28e4
#define FIELD_SCROLL_A       0x35cd
#define FIELD_SCROLL_B       0x35df

typedef struct Ov008MissionListEntry {
    u8  pad_00[2];
    u16 missionId;            /* 0x02 */
} Ov008MissionListEntry;

typedef struct Ov008MissionList {
    int nSelected;            /* 0x000 */
    u8  pad_004[8];
    int nScroll;              /* 0x00c */
    u8  pad_010[0x40 - 0x10];
    int bEntryGate;           /* 0x040 */
} Ov008MissionList;

extern Ov008MissionListEntry *func_ov008_0205b670(int nIndex);
extern int  func_ov008_02050ff8(void);                                    /* Ov008_GetCtxObject9630 */
extern u32  func_020235d0(int nField, int nBits);                         /* GameState_GetField */
extern int  func_ov008_02051028(void);                                    /* page transition active */
extern int  func_ov008_0206fb34(Ov008MissionList *pList, Ov008MissionListEntry *pEntry); /* IsField8LeField57 */
extern int  func_ov008_0206fb2c(Ov008MissionList *pList, Ov008MissionListEntry *pEntry); /* ov008_helper_6fb2c (ignores its arguments) */
extern void func_ov008_020511c8(u32 nMissionId);                          /* Ov008_SetCtxField967c */
extern void func_020235e8(int nField, int nBits, int nValue);             /* GameState_SetField */
extern void func_ov008_02050a08(int nEntry);                              /* Ov008_SetGlobalConfigAndInit */
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */

void func_ov008_02071ebc(Ov008MissionList *pList)
{
    Ov008MissionListEntry *pEntry;
    int bRefused;

    if (pList->nSelected < 0) {
        return;
    }
    bRefused = 0;
    pEntry = func_ov008_0205b670(pList->nSelected);
    if (func_ov008_02050ff8() == 0) {
        if (func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2) {
            bRefused = 1;
        }
    } else if (func_ov008_02051028() != 0) {
        if (pList->bEntryGate != 0) {
            if (func_ov008_0206fb34(pList, pEntry) == 0) {
                bRefused = 1;
            }
        } else {
            if (func_ov008_0206fb2c(pList, pEntry) == 0) {
                bRefused = 1;
            }
        }
    }
    if (bRefused == 0) {
        func_ov008_020511c8(func_ov008_0205b670(pList->nSelected)->missionId);
        func_020235e8(FIELD_SCROLL_A, 8, (u16)pList->nSelected);
        func_020235e8(FIELD_SCROLL_B, 8, (u16)pList->nScroll);
        func_ov008_02050a08(2);
        func_02033b78(0, 1);
    } else {
        func_02033b78(0, 4);
    }
}
