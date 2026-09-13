/* func_ov026_0208cd44 -- Ov008_RefreshShopUnlockParams: recompute the four
 * shop parameter words of the shared table (+0x148 id 0x1c9, +0x14c id 0x1c8,
 * +0x150 id 0x1a0, +0x154 id 0xe8), all set first.  The mission list of
 * descriptor data_ov026_020911c4 is walked while 0x1c9 holds: a mission whose
 * rank (3-bit field 0x28e4 + 3 * id) is below 3 clears 0x1c8, below 2 clears
 * 0x1c9 and 0xe8.  The same descriptor as list kind 6 is walked while 0x1a0
 * holds: kind-4 entries are counted, any other entry whose field 0x2a4c +
 * 3 * id is 0 clears 0xe8.  Then the 200 fields from 0x2ca4 (3 apart) above 1
 * are counted and 0x1a0 becomes "that count >= the kind-4 count".
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define FIELD_RANK_BASE     0x28e4
#define FIELD_PROGRESS_BASE 0x2a4c
#define FIELD_CLEAR_BASE    0x2ca4
#define FIELD_CLEAR_COUNT   200
#define FIELD_BITS          3
#define LIST_KIND_SECOND    6
#define ENTRY_KIND_SPECIAL  4

typedef struct Ov008MissionResourceDescriptor {
    const u8 *resourcePath;
    int selector;
    int listKind;
} Ov008MissionResourceDescriptor;

typedef struct Ov008MissionListState {
    u8 data[0x24];
} Ov008MissionListState;

typedef struct Ov008MissionListEntry {
    u8  pad00[2];
    u16 missionId;            /* 0x02 */
    u8  pad04[0x14];
    int nKind;                /* 0x18 */
} Ov008MissionListEntry;

typedef struct Ov008ParamTable {
    u8  pad_000[0x148];
    int nParam1c9;   /* 0x148 */
    int nParam1c8;   /* 0x14c */
    int nParam1a0;   /* 0x150 */
    int nParam0e8;   /* 0x154 */
} Ov008ParamTable;

extern const Ov008MissionResourceDescriptor data_ov026_020911c4;
extern Ov008ParamTable *data_ov026_0209136c;
extern void func_ov026_02084c70(Ov008MissionListState *pList, Ov008MissionResourceDescriptor *pDescriptor); /* Ov008_InitMissionList */
extern Ov008MissionListEntry *func_ov026_02084d00(Ov008MissionListState *pList, Ov008MissionListEntry *pEntry); /* Ov008_FindNextMissionEntry */
extern void func_ov026_02084cd0(Ov008MissionListState *pList);           /* Ov008_DestroyMissionList */
extern int  func_020235d0(int nField, int nBits);                         /* GameState_GetField */

void func_ov026_0208cd44(void)
{
    Ov008MissionResourceDescriptor descriptor;
    Ov008MissionListState listA;
    Ov008MissionListState listB;
    Ov008MissionListEntry *pEntry;
    int nRank;
    int nSpecial;
    int i;
    int nCleared;
    int nField;

    descriptor = data_ov026_020911c4;
    data_ov026_0209136c->nParam1c9 = 1;
    data_ov026_0209136c->nParam1c8 = 1;
    data_ov026_0209136c->nParam1a0 = 1;
    data_ov026_0209136c->nParam0e8 = 1;
    func_ov026_02084c70(&listA, &descriptor);
    descriptor.listKind = LIST_KIND_SECOND;
    func_ov026_02084c70(&listB, &descriptor);
    pEntry = 0;
    while (data_ov026_0209136c->nParam1c9 != 0 && (pEntry = func_ov026_02084d00(&listA, pEntry)) != 0) {
        nRank = func_020235d0(pEntry->missionId * 3 + FIELD_RANK_BASE, FIELD_BITS);
        if (nRank < 3) {
            data_ov026_0209136c->nParam1c8 = 0;
        }
        if (nRank < 2) {
            data_ov026_0209136c->nParam1c9 = 0;
        }
        if (nRank < 2) {
            data_ov026_0209136c->nParam0e8 = 0;
        }
    }
    pEntry = 0;
    nSpecial = 0;
    while (data_ov026_0209136c->nParam1a0 != 0 && (pEntry = func_ov026_02084d00(&listB, pEntry)) != 0) {
        if (pEntry->nKind == ENTRY_KIND_SPECIAL) {
            nSpecial++;
        } else if (func_020235d0(pEntry->missionId * 3 + FIELD_PROGRESS_BASE, FIELD_BITS) == 0) {
            data_ov026_0209136c->nParam0e8 = 0;
        }
    }
    i = 0;
    nCleared = 0;
    nField = FIELD_CLEAR_BASE;
    for (; i < FIELD_CLEAR_COUNT; i++) {
        if ((u32)func_020235d0(nField, FIELD_BITS) > 1) {
            nCleared++;
        }
        nField += 3;
    }
    data_ov026_0209136c->nParam1a0 = nCleared >= nSpecial;
    func_ov026_02084cd0(&listB);
    func_ov026_02084cd0(&listA);
}
