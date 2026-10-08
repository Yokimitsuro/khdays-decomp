#include "game/ov006_mission_mode_select.h"
#include "game/engine.h"
/* Per-frame scene tick: scene state 1 finalises the card transfer (clear owner +0x49c) once
 * Ov105_WH_End is ready; states 0 and 3 idle; any other state advances via
 * Ov105_WH_Finalize. */

extern int Ov105_WH_End(void);
extern void Ov105_WH_Finalize(void);

struct CardXferOwner {
    char _pad[0x49c];
    int nField49c;
};
#define MISSION_CONTEXT (data_ov006_020565e4.pContext)

void Ov006_TickCardTransferScene(void) {
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
