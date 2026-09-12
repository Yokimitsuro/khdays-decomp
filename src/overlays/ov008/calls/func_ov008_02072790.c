/* func_ov008_02072790 -- Ov008_MissionListSelectFirstOpen: select the first
 * mission whose 3-bit status field (0x28e4 + 3 * id) is below 2 (not yet
 * cleared); with a modal object up or touch enabled the selection is entry 0.
 * Then clears the two 8-bit scroll memories (0x35cd, 0x35df).
 *
 * When every mission is cleared nSel is never written: the ROM hands whatever
 * r4 held to the commit -- an original bug, kept as is.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008MissionList {
    u8  pad_000[0x38];
    int bTouchEnabled;        /* 0x038 */
} Ov008MissionList;

typedef struct Ov008MissionListEntry {
    u8  pad_00[2];
    u16 missionId;            /* 0x02 */
} Ov008MissionListEntry;

#define FIELD_MISSION_STATUS 0x28e4
#define FIELD_SCROLL_A       0x35cd
#define FIELD_SCROLL_B       0x35df

extern int func_ov008_02050ff8(void);                                    /* Ov008_GetCtxObject9630 */
extern u16 func_ov008_0205b708(void);                                    /* mission entry count */
extern Ov008MissionListEntry *func_ov008_0205b670(int nIndex);
extern u32 func_020235d0(int nField, int nBits);                         /* GameState_GetField */
extern void func_020235e8(int nField, int nBits, int nValue);            /* GameState_SetField */
extern void func_ov008_02071618(Ov008MissionList *pList, u32 nWord, int nTarget);

static inline int Ov008_IsMissionCleared(Ov008MissionListEntry *pEntry)
{
    return func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
}

void func_ov008_02072790(Ov008MissionList *pList)
{
    int nSel;
    int i;

    if (func_ov008_02050ff8() != 0) {
        nSel = 0;
    } else if (pList->bTouchEnabled != 0) {
        nSel = 0;
    } else {
        for (i = 0; i <= (int)func_ov008_0205b708(); i++) {
            if (!Ov008_IsMissionCleared(func_ov008_0205b670(i))) {
                nSel = i;
                break;
            }
        }
    }
    func_ov008_02071618(pList, nSel, -1);
    func_020235e8(FIELD_SCROLL_A, 8, 0);
    func_020235e8(FIELD_SCROLL_B, 8, 0);
}
