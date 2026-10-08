#include "nitro/types.h"

#include "game/ov006_mission_mode_select.h"
#include "game/engine.h"

/* Age every row, compact rows[4] once a row reaches 600 ticks, and take the ov105 scene branch when
 * the compaction empties the list. 600 is the expiry threshold in ticks; the row stride is the
 * MissionRecord 0xc0 established by the first hand-off. */

extern u8 data_ov006_020561c8[];
extern void Ov105_WH_SetGgid(u32 value);
extern void Ov105_WH_StartScan(void (*callback)(const MissionRecord *),
                                void *data, int value);
extern void VBlank_GetCount(void);
extern void Ov006_MissionUpsertRowByKey(const MissionRecord *record);
extern void Ov006_MissionDriveSound(void);

void *Ov006_MissionExpireRows(void) {
    switch (Game_PollSceneAlive()) {
    case 1:
        Ov105_WH_SetGgid(0x800356);
        Ov105_WH_StartScan(Ov006_MissionUpsertRowByKey,
                            data_ov006_020561c8, 0);
        break;

    case 2: {
        u8 i;

        VBlank_GetCount();
        for (i = 0; i < data_ov006_020565e4.pContext->rowCount; i++) {
            u8 j;

            if (data_ov006_020565e4.pContext->rowStates[i] < 600) {
                data_ov006_020565e4.pContext->rowStates[i]++;
            }

            if (data_ov006_020565e4.pContext->rowStates[i] >= 600) {
                for (j = i;
                     j < data_ov006_020565e4.pContext->rowCount - 1;
                     j++) {
                    data_ov006_020565e4.pContext->rows[j] =
                        data_ov006_020565e4.pContext->rows[j + 1];
                }
                data_ov006_020565e4.pContext->rowCount--;
                i--;
            }
        }
        break;
    }

    case 3:
        break;

    default:
        Ov006_MissionDriveSound();
        break;
    }

    return 0;
}
