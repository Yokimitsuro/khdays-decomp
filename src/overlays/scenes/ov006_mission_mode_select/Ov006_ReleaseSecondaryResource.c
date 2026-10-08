#include "game/ov006_mission_mode_select.h"
/* Ov006_ReleaseSecondaryResource -- release the Mission Mode's secondary resource handle, ov006.
 * Frees the resource object stored in the roster table slot [1] ((int)data_ov006_020565e4.pController) via
 * VeneerTo_Obj_Destroy and clears the slot. No-op if the slot is empty. */
extern void VeneerTo_Obj_Destroy(int p);

void Ov006_ReleaseSecondaryResource(void) {
    if ((int)data_ov006_020565e4.pController == 0) {
        return;
    }
    VeneerTo_Obj_Destroy((int)data_ov006_020565e4.pController);
    data_ov006_020565e4.pController = (void *)(0);
}
