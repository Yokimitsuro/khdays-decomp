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

extern Ov008MenuContext *Ov008_GetMenuContext(void);
extern u32 GameState_GetField(u32 field, int selector);
extern int Ov008_GetCtxObject9630(void);
extern int Ov008_GetCtxObject9634(void);
extern u32 Ov008_GetCtxField9638(void);
extern Ov008MissionListEntry *Ov008_GetNextMissionEntry(Ov008MissionListEntry *entry);
extern u8 data_ov008_0208ee84[];
extern u8 data_ov008_0208ee88[];
extern u8 data_ov008_0208ee89[];
extern u8 data_ov008_0208ee8a[];

void Ov008_WorldMap_RecalculateMissionSummary(void)
{
    Ov008MenuContext *menuContext = Ov008_GetMenuContext();
    u16 dayValue = (u16)GameState_GetField(0, 9);
    u16 tierIndex;
    int rowOffset;
    Ov008MissionListEntry *missionEntry;
    int isCompleted;

    if (Ov008_GetCtxObject9630() != 0 && Ov008_GetCtxObject9634() == 0) {
        dayValue = (u16)Ov008_GetCtxField9638();
    }

    menuContext->missionSummaryTiers[0] = 4;
    menuContext->missionSummaryTiers[1] = 4;
    menuContext->missionSummaryTiers[2] = 4;

    tierIndex = 0;
    do {
        rowOffset = tierIndex * 8;
        if (dayValue < *(u16 *)(data_ov008_0208ee84 + tierIndex * 8 + 8)) {
            menuContext->missionSummaryTiers[0] = data_ov008_0208ee88[rowOffset];
            menuContext->missionSummaryTiers[1] = data_ov008_0208ee89[rowOffset];
            menuContext->missionSummaryTiers[2] = data_ov008_0208ee8a[rowOffset];
            break;
        }
        tierIndex++;
    } while (tierIndex < 0x37);

    menuContext->completedMissionWeight = 0;
    missionEntry = Ov008_GetNextMissionEntry(0);
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
        missionEntry = Ov008_GetNextMissionEntry(missionEntry);
    } while (missionEntry != 0);
}
