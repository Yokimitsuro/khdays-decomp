#include "game/ov006_mission_mode_select.h"
/* Ov006_GetMissionMenuSelection -- read the Mission Mode's confirmed menu selection, ov006.
 * While the Mission Mode is idle (base+0x4e8 == 0) returns the live cursor selection
 * (Ov105_WH_GetLinkLevel); once locked in it returns -1. */
extern int Ov105_WH_GetLinkLevel(void);
#define MISSION_CONTEXT (data_ov006_020565e4.pContext)

int Ov006_GetMissionMenuSelection(void) {
    int sel;
    if (MISSION_CONTEXT->localMode != 0) {
        sel = -1;
    } else {
        sel = Ov105_WH_GetLinkLevel();
    }
    return (char)sel;
}
