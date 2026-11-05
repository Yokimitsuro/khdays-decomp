/* Ov008_UpdateMenuInput -- menu per-frame input/state update, ov008. Picks the menu's
 * transition mode into heap[+0x2c] from the input sources (a queued transition
 * Ov008_Link_IsLocal, a pending sub-scene Ov008_IsSessionReady, or the shoulder scroll
 * Session_Exists/Session_IsSceneInterruptible) and mirrors the region flag into heap[+0x2a]. Finally, when
 * both stick axes are centered (Session_Exists/Session_IsActive), commits via Ov008_StoreSeatCampRecord. */

#include "game/engine.h"

extern char *data_ov008_02090f00;
extern int   data_0204c240;
extern int   Ov008_Link_IsLocal(void);
extern int   Ov008_IsSessionReady(void);
extern int   Ov008_GetPlayerMask(void);
extern void  Ov008_StoreSeatCampRecord(int);
void Ov008_UpdateMenuInput(void) {
    if (data_ov008_02090f00 == 0) {
        return;
    }
    if (Ov008_Link_IsLocal() != 0) {
        *(unsigned short *)(data_ov008_02090f00 + 0x2c) = 1;
        *(unsigned short *)(data_ov008_02090f00 + 0x2a) = *(unsigned short *)((char *)&data_0204c240 + 2);
        return;
    }
    if (Ov008_IsSessionReady() != 0) {
        *(unsigned short *)(data_ov008_02090f00 + 0x2c) = Ov008_GetPlayerMask();
        *(unsigned short *)(data_ov008_02090f00 + 0x2a) = *(unsigned short *)((char *)&data_0204c240 + 2);
    } else if (Session_Exists() == 0) {
        *(unsigned short *)(data_ov008_02090f00 + 0x2c) = 0;
    } else if (Session_IsSceneInterruptible() != 0) {
        *(unsigned short *)(data_ov008_02090f00 + 0x2c) = 0;
    }
    if (Session_Exists() == 0) {
        return;
    }
    if (Session_IsActive() == 0) {
        return;
    }
    Ov008_StoreSeatCampRecord(0);
}
