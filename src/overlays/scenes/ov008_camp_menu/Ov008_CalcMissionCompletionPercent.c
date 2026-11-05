/* Loads the mission-list resource, sums progress for entries whose low status bits are set, and
 * returns the average completion percentage. The caller passes menuState although this body does
 * not consume it. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct {
    const u8 *resourcePath;
    int selector;
    int listKind;
} Ov008MissionResourceDescriptor;

typedef struct {
    u8 data[0x24];
} Ov008MissionListState;

typedef struct Ov008MissionListEntry {
    u8 pad00[2];
    u16 missionId;
    u8 pad04[0x14];
    u32 nKind;
} Ov008MissionListEntry;

extern Ov008MissionResourceDescriptor data_ov008_0208ede0;
extern void Ov008_InitMissionList(Ov008MissionListState *list,
                                Ov008MissionResourceDescriptor *descriptor);
extern Ov008MissionListEntry *Ov008_FindNextMissionEntry(Ov008MissionListState *list,
                                                  Ov008MissionListEntry *entry);
extern void Ov008_DestroyMissionList(Ov008MissionListState *list);
extern int func_02020400(int numerator, int denominator);

u16 Ov008_CalcMissionCompletionPercent(void *menuState)
{
    Ov008MissionResourceDescriptor resourceDescriptor = data_ov008_0208ede0;
    Ov008MissionListState missionList;
    u16 qualifyingCount = 0;
    u16 progressTotal = 0;
    Ov008MissionListEntry *missionEntry;

    Ov008_InitMissionList(&missionList, &resourceDescriptor);
    for (missionEntry = Ov008_FindNextMissionEntry(&missionList, 0);
         missionEntry != 0;
         missionEntry = Ov008_FindNextMissionEntry(&missionList, missionEntry)) {
        if ((missionEntry->nKind & 3) != 0) {
            qualifyingCount++;
            progressTotal += GameState_GetField(missionEntry->missionId * 3 + 0x2a4c, 3);
        }
    }
    Ov008_DestroyMissionList(&missionList);
    if (qualifyingCount != 0) {
        return (u16)func_02020400(progressTotal * 100, qualifyingCount * 3);
    }
    return 0;
}
