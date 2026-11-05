/* Latch the pending request once, if the system is idle: only when Session_GetLocalPlayerIndex
 * reports free, the mode halfword at +2 is 1 and the latch at +0 is still clear.
 * Sets the latch, posts event 0x11, notifies ov023, sets game flag 0x2484 and
 * marks the session object's +0xe8.
 *
 * data_0204be08 and data_0204be08_params are the SAME address under two names,
 * and that is required, not cosmetic: the ROM's literal pool holds 0x0204be08 in
 * two separate entries, and mwcc emits two only for two distinct symbols. The
 * duplication is in the original too -- one view reads the block as scalar
 * fields, the other hands it to MsgQueue_Post as a parameter buffer, which is
 * what the _params name records. */

#include "game/engine.h"

extern unsigned short data_0204be08;
extern unsigned short data_0204be08_params;

extern void Ov023_RequestEventSkip(void);

void LatchPendingRequestOnce(void) {
    char *self = *(char **)((char *)&data_0204be08 + 4);

    if (Session_GetLocalPlayerIndex() != 0) {
        return;
    }
    if ((&data_0204be08)[1] != 1) {
        return;
    }
    if (data_0204be08 != 0) {
        return;
    }

    data_0204be08 = 1;
    MsgQueue_Post(0x11, (void *)&data_0204be08_params, 2);
    Ov023_RequestEventSkip();
    GameState_SetField(0x2484, 1, 1);
    *(int *)(self + 0xe8) = 1;
}
