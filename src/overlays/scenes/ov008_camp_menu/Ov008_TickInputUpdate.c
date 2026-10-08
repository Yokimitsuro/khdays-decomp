#include "game/ov008_camp_menu.h"
/* Ov008_TickInputUpdate -- if the tick source is early (<2), mark the input object busy
 * (ctx+0x4e8 = 1); then kick its update (Obj_SetField14 with callback Ov008_MissionSelectionSendTick),
 * and return the busy flag. */
extern unsigned short WH_GetBitmap(void);
extern void Obj_SetField14(int obj, void *cb);
extern void Ov008_MissionSelectionSendTick(void);
#define MISSION_CONTEXT (data_ov008_02090f24.pContext)

int Ov008_TickInputUpdate(void) {
    if (WH_GetBitmap() <= 1) {
        MISSION_CONTEXT->localMode = 1;
    }
    Obj_SetField14((int)data_ov008_02090f24.pController, Ov008_MissionSelectionSendTick);
    return MISSION_CONTEXT->localMode;
}
