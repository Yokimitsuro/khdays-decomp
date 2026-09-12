/* func_ov008_02072bc0 -- Ov008_MissionListSelectCurrent: re-select the mission the
 * context currently names (field 0x967c).  If that mission is not listed, or is
 * not found in the entry chain, fall back to the first open mission.  Otherwise
 * restore the remembered scroll (field 0x35df, 8 bits: (v + 16) / 32 rows) when
 * one is stored and select the found row.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008MissionList Ov008MissionList;

typedef struct Ov008MissionListEntry {
    u8  pad_00[2];
    u16 missionId;            /* 0x02 */
} Ov008MissionListEntry;

#define FIELD_SCROLL_B 0x35df
#define ROW_UNITS      32

extern u32 func_ov008_020511e0(void);                                    /* Ov008_GetCtxField967c: current mission id */
extern int func_ov008_0205b6e8(u32 nMissionId);                          /* is the mission listed */
extern void func_ov008_02072790(Ov008MissionList *pList);                /* Ov008_MissionListSelectFirstOpen */
extern Ov008MissionListEntry *func_ov008_0205b650(Ov008MissionListEntry *pEntry); /* Ov008_GetNextMissionEntry */
extern u16 func_ov008_0205b708(void);                                    /* mission entry count */
extern int func_020235d0(int nField, int nBits);                         /* GameState_GetField */
extern void func_ov008_02071618(Ov008MissionList *pList, u32 nWord, int nTarget);

void func_ov008_02072bc0(Ov008MissionList *pList)
{
    int nRow;
    Ov008MissionListEntry *pEntry;
    int nScroll;

    if (func_ov008_0205b6e8(func_ov008_020511e0()) == 0) {
        func_ov008_02072790(pList);
        return;
    }
    nRow = 0;
    for (pEntry = func_ov008_0205b650(0); pEntry != 0; pEntry = func_ov008_0205b650(pEntry)) {
        if (pEntry->missionId == func_ov008_020511e0()) {
            break;
        }
        nRow++;
    }
    if (nRow < func_ov008_0205b708()) {
        nScroll = func_020235d0(FIELD_SCROLL_B, 8);
        if (nScroll >= 0) {
            func_ov008_02071618(pList, (nScroll + ROW_UNITS / 2) / ROW_UNITS, -1);
        }
        func_ov008_02071618(pList, nRow, -1);
    } else {
        func_ov008_02072790(pList);
    }
}
