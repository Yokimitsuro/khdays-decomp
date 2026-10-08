#include "game/ov006_mission_mode_select.h"
/* Ov006_GetMissionScreenFlag -- read the current-screen flag byte, ov006. Indexes the ov006
 * context (*MISSION_CONTEXT) by the RTC-available bit and reads byte @+0x48e. */
extern unsigned short WH_GetCurrentAid(void);
#define MISSION_CONTEXT (data_ov006_020565e4.pContext)
int Ov006_GetMissionScreenFlag(void) {
    return MISSION_CONTEXT->message.selection.peerStatus[WH_GetCurrentAid()];
}
