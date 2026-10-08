#include "game/ov008_camp_menu.h"
#include "game/engine.h"
/* Ov008_MissionDriveSound -- drive the ov105 sound state from the scene state.
 * State 0 (still booting) arms the "intro jingle started" latch at obj+0x49c once the
 * sound engine reports ready; states 1 and 3 are quiet; 9 and 10 fade out; every other
 * state stops the sound outright.
 *
 * PROVENANCE: byte-identical twin of Ov006_MissionDriveSound -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern void Ov105_WH_Reset(void);
extern int  Ov105_WH_Initialize(void);
extern void Ov105_WH_Finalize(void);
#define MISSION_CONTEXT (data_ov008_02090f24.pContext)

#define OBJ ((int *)data_ov008_02090f24.pContext)

void Ov008_MissionDriveSound(void) {
    switch (Game_PollSceneAlive()) {
    case 9:
    case 10:
        Ov105_WH_Reset();
        return;
    case 0:
        if (OBJ[0x127] != 0) {
            return;
        }
        if (Ov105_WH_Initialize() == 0) {
            return;
        }
        OBJ[0x127] = 1;
        return;
    case 1:
        break;
    case 3:
        break;
    default:
        Ov105_WH_Finalize();
        return;
    }
}
