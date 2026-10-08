#include "game/ov006_mission_mode_select.h"
/* Ov006_TickInputUpdate -- if the tick source is early (<2), mark the input object busy
 * (ctx+0x4e8 = 1); then kick its update (Obj_SetField14 with callback Ov006_MissionSelectionSendTick),
 * and return the busy flag. */
extern unsigned short WH_GetBitmap(void);
extern void Obj_SetField14(int obj, void *cb);
extern void Ov006_MissionSelectionSendTick(void);
#define MISSION_CONTEXT (data_ov006_020565e4.pContext)

int Ov006_TickInputUpdate(void) {
    if (WH_GetBitmap() <= 1) {
        MISSION_CONTEXT->localMode = 1;
    }
    Obj_SetField14((int)data_ov006_020565e4.pController, Ov006_MissionSelectionSendTick);
    return MISSION_CONTEXT->localMode;
}
