#include "nitro/types.h"

#include "game/ov006_mission_mode_select.h"
#include "game/engine.h"

/* Pick the per-state callback, stage the active_record for it, and update the two flag bytes at
 * context+0x4ee and +0x4ef. Those two flags sit just below the 0x4f4 context size that
 * Ov006_MissionCreateContext measures, so they are the last fields of the object rather than
 * something past its end. */

typedef void (*MissionCallback)(void);

extern void Ov105_WH_SetSsid(u8 *mode, int value);
extern int Ov105_WH_ChildConnect(int value, MissionRecord *record);
extern void Ov105_WH_SetReceiver(MissionCallback callback);
extern u16 Ov105_WH_GetLastError(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void Ov006_UpdateAndGetIdleHandler(void);
extern void Ov006_UpdateSlotCache_2(void);
extern void Ov006_MissionUpdateSelectionState(void);
extern void Ov006_MissionSceneIdleCallback(void);

MissionCallback Ov006_MissionSelectStateCallback(void) {
    MissionCallback result = 0;

    switch (Game_PollSceneAlive()) {
    case 1:
        data_ov006_020565e4.pContext->signal = 0;
        Ov105_WH_SetSsid(&data_ov006_020565e4.pContext->mode, 1);
        if (Ov105_WH_ChildConnect(1,
                &data_ov006_020565e4.pContext->active.record) == 0) {
            result = Ov006_UpdateAndGetIdleHandler;
        }
        break;

    case 3:
    case 8:
        break;

    case 4:
        data_ov006_020565e4.pContext->mode = 0;
        Ov105_WH_SetReceiver(Ov006_UpdateSlotCache_2);
        data_ov006_020565e4.pContext->transitionRequested = 1;
        data_ov006_020565e4.pContext->sendBusy = 0;
        data_ov006_020565e4.pContext->workStates[0] = 0;
        MI_CpuFill8(data_ov006_020565e4.pContext->workBuffers[0].buffer,
                    0, 4);
        result = Ov006_MissionUpdateSelectionState;
        break;

    default:
        if (Ov105_WH_GetLastError() == 12) {
            data_ov006_020565e4.pContext->signal = 1;
            return Ov006_MissionSceneIdleCallback;
        }
        if (Ov105_WH_GetLastError() == 11) {
            data_ov006_020565e4.pContext->signal = 1;
            return Ov006_MissionSceneIdleCallback;
        }
        result = Ov006_UpdateAndGetIdleHandler;
        break;
    }

    return result;
}
