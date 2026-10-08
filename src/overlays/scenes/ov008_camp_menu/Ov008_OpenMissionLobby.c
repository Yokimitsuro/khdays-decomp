#include "game/ov008_camp_menu.h"
/* Open the mission lobby: create its task from the lobby class (data_ov008_02090bb0) when there
 * is none; otherwise count one more user in the lobby's +0x4f2 (Ov008_ReleaseMissionLobby counts
 * it down) and restart the existing task at Ov008_MissionLobbyEnter.
 *
 * Matched byte-exact 2026-07-23, closing an old park. The park held the global in a local, which
 * makes mwcc park it in a callee-saved register across the call; the ROM re-materialises the pool
 * address instead, so the global has to be referenced directly every time. The last piece is a
 * CSE break: the guard and the final argument read the SAME word, and mwcc folds them into one
 * load unless they are spelled differently -- the ROM reloads it, because the first load's
 * register is clobbered by the lobby pointer in between (so the last read of pController
 * goes through the block's address). */
extern int  InstantiateClass(void *desc, int arg);
extern void Obj_SetField14(int inst, void *fn);
extern char data_ov008_02090bb0[];
extern void Ov008_MissionLobbyEnter(void);

void Ov008_OpenMissionLobby(int arg) {
    if (data_ov008_02090f24.pController == 0) {
        data_ov008_02090f24.pController = (void *)InstantiateClass(data_ov008_02090bb0, arg);
        return;
    }
    *(unsigned short *)((char *)data_ov008_02090f24.pContext + 0x4f2) =
        *(unsigned short *)((char *)data_ov008_02090f24.pContext + 0x4f2) + 1;
    Obj_SetField14(*(int *)((char *)&data_ov008_02090f24 + 4), (void *)Ov008_MissionLobbyEnter);
}
