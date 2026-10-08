#include "nitro/types.h"

#include "game/ov008_camp_menu.h"
#include "game/engine.h"
#define SCENE_POLL_IDLE 4

#define MISSION_CONTEXT (data_ov008_02090f24.pContext)
extern unsigned short WH_GetCurrentAid(void);
extern unsigned short WH_GetBitmap(void); /* current session id */

int Ov008_IsMissionGroupStale(void)
{
    MissionContext *pCtx = MISSION_CONTEXT;
    u16 nRecorded;

    if (pCtx == 0 || pCtx->localMode != 0) {
        return 0;
    }
    if (WH_GetCurrentAid() == 0) {
        nRecorded = GetGlobalU16At4();
        if (nRecorded != WH_GetBitmap()) {
            MISSION_CONTEXT->liveEntries.header.bits.dirty = 1;
            return 1;
        }
    } else if (MISSION_CONTEXT->liveEntries.header.bits.dirty != 0) {
        return 1;
    }
    return Game_PollSceneAlive() != SCENE_POLL_IDLE;
}
