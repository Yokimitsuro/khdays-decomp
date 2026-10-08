#include "nitro/types.h"

#include "game/ov008_camp_menu.h"
#include "game/engine.h"
#define MISSION_CONTEXT (data_ov008_02090f24.pContext)
extern u8 data_ov008_0208fc84[];
extern void Ov105_WH_SetGgid(u32 value);
extern void Ov105_WH_StartScan(void (*callback)(const MissionRecord *),
                                void *data, int value);
extern void VBlank_GetCount(void);
extern void Ov008_MissionUpsertRowByKey(const MissionRecord *record);
extern void Ov008_MissionDriveSound(void);

void *Ov008_MissionExpireRows(void) {
    switch (Game_PollSceneAlive()) {
    case 1:
        Ov105_WH_SetGgid(0x800356);
        Ov105_WH_StartScan(Ov008_MissionUpsertRowByKey,
                            data_ov008_0208fc84, 0);
        break;

    case 2: {
        u8 i;

        VBlank_GetCount();
        for (i = 0; i < MISSION_CONTEXT->rowCount; i++) {
            u8 j;

            if (MISSION_CONTEXT->rowStates[i] < 600) {
                MISSION_CONTEXT->rowStates[i]++;
            }

            if (MISSION_CONTEXT->rowStates[i] >= 600) {
                for (j = i;
                     j < MISSION_CONTEXT->rowCount - 1;
                     j++) {
                    MISSION_CONTEXT->rows[j] =
                        MISSION_CONTEXT->rows[j + 1];
                }
                MISSION_CONTEXT->rowCount--;
                i--;
            }
        }
        break;
    }

    case 3:
        break;

    default:
        Ov008_MissionDriveSound();
        break;
    }

    return 0;
}
