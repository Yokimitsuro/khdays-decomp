/* Selects three mission-summary tier values from the day-threshold table and sums completion
 * weights for missions with progress greater than one. */

#include "nitro/types.h"

typedef struct Ov008MissionListEntry {
    u8 pad00[2];
    u16 missionId;
    u8 pad04[0x11];
    u8 completionWeight;
} Ov008MissionListEntry;

typedef struct Ov008MenuContext {
    u8 pad0000[0x14f0];
    u8 missionSummaryTiers[3];
    u8 completedMissionWeight;
} Ov008MenuContext;

extern Ov008MenuContext *Ov025_GetPageA(void);
extern u32 GameState_GetField(u32 field, int selector);
extern int Ov025_GetCtxObject9630(void);
extern int Ov025_GetCtxObject9634(void);
extern u32 Ov025_GetCtxField9638(void);
extern Ov008MissionListEntry *Ov025_GetNextMissionEntry(Ov008MissionListEntry *entry);
extern u8 data_ov025_020b39e4[];
extern u8 data_ov025_020b39e8[];
extern u8 data_ov025_020b39e9[];
extern u8 data_ov025_020b39ea[];

void Ov025_WorldMap_RecalculateMissionSummary(void)
{
    Ov008MenuContext *menuContext = Ov025_GetPageA();
    u16 dayValue = (u16)GameState_GetField(0, 9);
    u16 tierIndex;
    int rowOffset;
    Ov008MissionListEntry *missionEntry;
    int isCompleted;

    if (Ov025_GetCtxObject9630() != 0 && Ov025_GetCtxObject9634() == 0) {
        dayValue = (u16)Ov025_GetCtxField9638();
    }

    menuContext->missionSummaryTiers[0] = 4;
    menuContext->missionSummaryTiers[1] = 4;
    menuContext->missionSummaryTiers[2] = 4;

    tierIndex = 0;
    do {
        rowOffset = tierIndex * 8;
        if (dayValue < *(u16 *)(data_ov025_020b39e4 + tierIndex * 8 + 8)) {
            menuContext->missionSummaryTiers[0] = data_ov025_020b39e8[rowOffset];
            menuContext->missionSummaryTiers[1] = data_ov025_020b39e9[rowOffset];
            menuContext->missionSummaryTiers[2] = data_ov025_020b39ea[rowOffset];
            break;
        }
        tierIndex++;
    } while (tierIndex < 0x37);

    menuContext->completedMissionWeight = 0;
    missionEntry = Ov025_GetNextMissionEntry(0);
    if (missionEntry == 0) {
        return;
    }
    do {
        isCompleted =
            GameState_GetField(missionEntry->missionId * 3 + 0x28e4, 3) >= 2;
        if (isCompleted != 0) {
            menuContext->completedMissionWeight += missionEntry->completionWeight;
        }
        GameState_GetField(missionEntry->missionId * 3 + 0x28e4, 3);
        missionEntry = Ov025_GetNextMissionEntry(missionEntry);
    } while (missionEntry != 0);
}
