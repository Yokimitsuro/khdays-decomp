#include "game/engine.h"

extern void VeneerTo_Obj_Destroy(int *ctx);
extern int *data_ov002_0207fa20;
/* Reset the subsystem: run teardown on the global context and clear global array entry 4; return 1. */
int Ov002_ResetSubsystem(void) {
    VeneerTo_Obj_Destroy(data_ov002_0207fa20);
    StoreGlobalArrayEntry(4, 0);
    return 1;
}
