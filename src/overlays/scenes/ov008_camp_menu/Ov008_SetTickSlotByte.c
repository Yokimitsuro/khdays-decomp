#include "game/ov008_camp_menu.h"
/* Stores the mission slot byte (also into the screen flags for the host). */

#define MISSION_CONTEXT (data_ov008_02090f24.pContext)
extern unsigned short WH_GetCurrentAid(void);

void Ov008_SetTickSlotByte(int value)
{
    MISSION_CONTEXT->selectionBlock[0x16] = value;

    if (WH_GetCurrentAid() == 0) {
        MISSION_CONTEXT->message.selection.peerStatus[WH_GetCurrentAid()] = value;
    }
}
