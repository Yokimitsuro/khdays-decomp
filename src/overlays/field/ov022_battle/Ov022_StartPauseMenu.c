#include "game/engine.h"

extern void Ov022_UpdateCameraAndViews(int mode);
extern int Ov002_StepPeerObjectLoading(void);
extern int Ov022_GetEntryField66(int);
extern void Ov002_ReadRosterSeat(int a, int b, int *out);
extern void Ov002_RunSeatHooks(void);
extern void Ov002_ClearListA(int id);
extern int Ov002_GetSeatBudget(int id);
extern int Ov002_GetSeatBudgetScaled(int id);
extern void Ov002_SetSessionBusy(int mode);
extern void Ov022_StateEnterGameplay(void);
extern unsigned char data_0204be04;

/* Starts the pause menu unless the lock byte is set: opens the panel, publishes the selected
 * entry and hands back the menu's tick handler. */
void *Ov022_StartPauseMenu(void) {
    int entry;
    unsigned short alpha;
    if (data_0204be04 != 0) {
        /* No value: the ROM leaves r0 as it came, which is this function's own address
         * (Obj_UpdateAll calls each update through r0, `ldr r0,[r1,#0x14]; blx r0`), so the
         * object keeps this update and tries again next frame. */
        return;
    }
    Ov022_UpdateCameraAndViews(0);
    if (Ov002_StepPeerObjectLoading() != 0) {
        Ov002_ReadRosterSeat(Ov022_GetEntryField66(QueryActiveStateOrDelegate()), 0, &entry);
        Ov002_RunSeatHooks();
        Ov002_ClearListA((unsigned short)entry);
        alpha = Session_IsActive() != 0 ? 0x66 : 0x7f;
        Req_SetPendingFields(Ov002_GetSeatBudget(entry), Ov002_GetSeatBudgetScaled(entry), alpha);
        Ov002_SetSessionBusy(0);
        return (void *)&Ov022_StateEnterGameplay;
    }
    return 0;
}
