/* Releases the mission scene instance; in link mode also releases the wireless overlay and resets.
 */

#include "game/engine.h"

extern char *data_ov008_02090fa8;
extern void VeneerTo_Obj_Destroy(int arg0);
extern void OS_ResetSystem(int arg0);

void Ov008_MissionScene_Release(void)
{
    VeneerTo_Obj_Destroy(*(int *)data_ov008_02090fa8);

    if (*(int *)(data_ov008_02090fa8 + 4) == 2) {
        Overlay105_Release();
        OS_ResetSystem(-2);
    }
}
