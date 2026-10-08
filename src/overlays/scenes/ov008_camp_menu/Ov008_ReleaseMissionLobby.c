#include "game/ov008_camp_menu.h"
/* Ov008_ReleaseMissionLobby -- let go of the mission lobby. Does nothing while there is no lobby
 * task (+4). Otherwise, while other users remain (the count at the lobby's +0x4f2, which
 * Ov008_OpenMissionLobby raises) it counts one down and returns; the last release destroys the
 * task and clears the handle.
 *
 * This was filed as a "PROVEN TIE (register coloring only)" -- an r0/r1 swap with everything else
 * identical. It was two real source bugs, and the second one is the interesting half.
 *
 * 1. A DROPPED ARGUMENT. VeneerTo_Obj_Destroy takes the handle; the old source declared it
 *    `(void)` and called it with none. The ROM's `bl` is reached with r0 still holding the value
 *    loaded by `ldr r0,[r1,#4]` at the top -- that is the argument, not a leftover. Passing it
 *    keeps the handle live in r0 across the whole body, which is precisely what forces the base
 *    pointer into r1 and produced the "swap".
 *
 * 2. THE BASE MUST BE ADVANCED IN PLACE. Written as one expression,
 *    `base = (char *)pContext + 0x400;` mwcc loads the pointer into r1 and lands the sum in
 *    a fresh r2, then puts the counter in r1 -- the last two registers stay swapped. Split into
 *    `base = (char *)pContext;` then `base += 0x400;` and mwcc updates r1 in place
 *    (`ldr r1,[r1]` / `add r1,r1,#0x400`), leaving r2 for the counter exactly as the ROM does.
 *    Same total instructions either way; only the register choice differs.
 */
extern int VeneerTo_Obj_Destroy(int handle);

void Ov008_ReleaseMissionLobby(void) {
    char *base;
    unsigned short c;
    int handle = (int)data_ov008_02090f24.pController;

    if (handle == 0) {
        return;
    }
    base = (char *)data_ov008_02090f24.pContext;
    base += 0x400;

    c = *(unsigned short *)(base + 0xf2);
    if (c != 0) {
        *(unsigned short *)(base + 0xf2) = c - 1;
        return;
    }
    VeneerTo_Obj_Destroy(handle);
    data_ov008_02090f24.pController = 0;
}
