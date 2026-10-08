#include "game/ov008_camp_menu.h"
/* Ov008_GetMissionMenuSelection -- read the confirmed menu selection.
 * While idle (base+0x4e8 == 0) returns the live cursor selection
 * (Ov105_WH_GetLinkLevel); once locked in it returns -1.
 *
 * PROVENANCE: byte-identical twin of Ov006_GetMissionMenuSelection, propagated from it. The "Mission Mode"
 * framing in that rep is ov006's own scene identity -- ov008 loads the same UI/mlt/* resources,
 * so it is plausible here, but it has not been verified for THIS function. Not asserted. */
extern int Ov105_WH_GetLinkLevel(void);
#define MISSION_CONTEXT (data_ov008_02090f24.pContext)

int Ov008_GetMissionMenuSelection(void) {
    int sel;
    if (MISSION_CONTEXT->localMode != 0) {
        sel = -1;
    } else {
        sel = Ov105_WH_GetLinkLevel();
    }
    return (char)sel;
}
