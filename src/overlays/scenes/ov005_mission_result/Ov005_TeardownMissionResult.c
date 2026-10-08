#include "game/engine.h"

extern void Ov005_RegisterAnimTables(void);
extern void VeneerTo_Obj_Destroy(int h);
extern void MI_CpuFill8(void *dst, int value, unsigned size);
extern int **data_ov005_0205b808;
extern int data_0204c32c;

/* Mission-result teardown: drops the three widgets, forces the capture bit in POWCNT, releases
 * the two node handles and clears the shared result block. */
void Ov005_TeardownMissionResult(void) {
    Ov005_RegisterAnimTables();
    ResSlot_Release_2(0x15);
    ResSlot_Release_2(0x1a);
    ResSlot_Release_2(0x19);
    *(volatile unsigned short *)0x04000304 |= 0x8000;
    VeneerTo_Obj_Destroy(**(int **)&data_ov005_0205b808);
    VeneerTo_Obj_Destroy((*(int **)&data_ov005_0205b808)[1]);
    MI_CpuFill8(&data_0204c32c, 0, 0xac);
}
