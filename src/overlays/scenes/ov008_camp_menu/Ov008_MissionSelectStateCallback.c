#include "nitro/types.h"

#include "game/ov008_camp_menu.h"
#include "game/engine.h"
/* Pick the per-state callback, stage the active_record for it, and update the two flag bytes at
 * context+0x4ee and +0x4ef. Those two flags sit just below the 0x4f4 context size that
 * Ov006_MissionCreateContext measures, so they are the last fields of the object rather than
 * something past its end. */

typedef void (*MissionCallback)(void);

#define MISSION_CONTEXT (data_ov008_02090f24.pContext)
extern void Ov105_WH_SetSsid(u8 *mode, int value);
extern int Ov105_WH_ChildConnect(int value, MissionRecord *record);
extern void Ov105_WH_SetReceiver(MissionCallback callback);
extern u16 Ov105_WH_GetLastError(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void Ov008_MissionIdleStateNoOp(void);
extern void Ov008_UpdateSlotCache_2(void);
extern void Ov008_MissionUpdateSelectionState(void);
extern void Ov008_MissionSceneIdleCallback(void);

MissionCallback Ov008_MissionSelectStateCallback(void) {
    MissionCallback result = 0;

    switch (Game_PollSceneAlive()) {
    case 1:
        MISSION_CONTEXT->signal = 0;
        Ov105_WH_SetSsid(&MISSION_CONTEXT->mode, 1);
        if (Ov105_WH_ChildConnect(1,
                &MISSION_CONTEXT->active.record) == 0) {
            result = Ov008_MissionIdleStateNoOp;
        }
        break;

    case 3:
    case 8:
        break;

    case 4:
        MISSION_CONTEXT->mode = 0;
        Ov105_WH_SetReceiver(Ov008_UpdateSlotCache_2);
        MISSION_CONTEXT->transitionRequested = 1;
        MISSION_CONTEXT->sendBusy = 0;
        MISSION_CONTEXT->workStates[0] = 0;
        MI_CpuFill8(MISSION_CONTEXT->workBuffers[0].buffer,
                    0, 4);
        result = Ov008_MissionUpdateSelectionState;
        break;

    default:
        if (Ov105_WH_GetLastError() == 12) {
            MISSION_CONTEXT->signal = 1;
            return Ov008_MissionSceneIdleCallback;
        }
        if (Ov105_WH_GetLastError() == 11) {
            MISSION_CONTEXT->signal = 1;
            return Ov008_MissionSceneIdleCallback;
        }
        result = Ov008_MissionIdleStateNoOp;
        break;
    }

    return result;
}
