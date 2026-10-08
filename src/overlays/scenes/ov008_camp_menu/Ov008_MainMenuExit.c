/* Ov008_MainMenuExit -- execute the pending main-menu confirm action, ov008 (one-shot).
 * Guarded by the live menu heap (data_ov008_02090f00 != 0). Reads the confirmed action code
 * (Ov008_GetCtxField9678), tears down the menu UI (e130/da14) and starts the 0x1e-frame fade;
 * if in-game state is active, resets story flags 0xd/0xe. Then:
 *   action 7 -> full soft reset: OS_ResetSystem(-2) (NitroSDK system reset) + scene 1 (ov000/title).
 *   action 8 -> enter game: copy the selected save slot's 4-word config (overwriting word[1]
 *     with Ov008_CountOccupiedSlots), CopyConfig16 it, and switch to scene 2 (ov002/gameplay).
 * Clears the menu-heap guard afterward so it fires only once. */

#include "game/engine.h"

#include "game/scene.h"
struct Cfg4 { int w[4]; };
extern char *data_ov008_02090f00;
extern int  Ov008_GetCtxField9678(void);
extern void Ov008_TeardownMenu2D(void);
extern void Ov008_ReleaseMenuUi(void);
extern void ClearGlobalArrayInt(int flag);
extern void Ov008_ReleaseMissionLobby(void);
extern int  Ov008_CountOccupiedSlots(void);
extern void OS_ResetSystem(int mode);

void Ov008_MainMenuExit(void) {
    int action;
    struct Cfg4 cfg;
    if (data_ov008_02090f00 == 0) {
        return;
    }
    action = Ov008_GetCtxField9678();
    Ov008_TeardownMenu2D();
    Ov008_ReleaseMenuUi();
    RequestQueue_SetOrPushKind3(0x1e);
    if (Session_Exists() != 0) {
        GameSession_SetSyncEnabled(1);
        ClearGlobalArrayInt(0xd);
        ClearGlobalArrayInt(0xe);
    }
    Ov008_ReleaseMissionLobby();
    if (action != 7) {
        if (action == 8) {
            cfg = *(struct Cfg4 *)Session_GetSetup();
            cfg.w[1] = Ov008_CountOccupiedSlots();
            Session_StoreSetup(&cfg);
            Scene_RequestPending(SCENE_FIELD, 0);
        }
    } else {
        if (Session_Exists() != 0) {
            ReleaseServiceInstance();
        }
        PartyState_ResetBuffers();
        OS_ResetSystem(-2);
        Scene_RequestPending(SCENE_TITLE, 0);
    }
    data_ov008_02090f00 = 0;
}
