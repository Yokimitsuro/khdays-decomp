#include "game/ov008_camp_menu.h"
#include "game/engine.h"
/* Per-frame scene tick: scene state 1 finalises the card transfer (clear owner +0x49c) once
 * Ov105_WH_End is ready; states 0 and 3 idle; any other state advances via
 * Ov105_WH_Finalize. */

extern int Ov105_WH_End(void);
extern void Ov105_WH_Finalize(void);

#define MISSION_CONTEXT (data_ov008_02090f24.pContext)

void Ov008_TickCardTransferScene(void) {
    switch (Game_PollSceneAlive()) {
    case 0:
        return;
    case 1:
        if (Ov105_WH_End() != 0) {
            MISSION_CONTEXT->busy = 0;
        }
        return;
    case 3:
        return;
    default:
        Ov105_WH_Finalize();
    }
}
