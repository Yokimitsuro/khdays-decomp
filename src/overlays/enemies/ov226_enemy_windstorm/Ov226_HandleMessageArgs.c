/* Ov226_HandleMessageArgs -- retune, notify, and (in mode 1) start the homing move.
 * It takes three VecFx32 by value: the first one's address is handed to Ov107_MoveNodeAndRelayout
 * as the start of an argument list, and the second and third are forwarded BY VALUE to
 * Ov226_Projectile_SetupFlight.
 *
 * Bit 1 of +0x40 is a SIGNED bitfield (the ROM extracts it with asr, not lsr) and gates the
 * owner's own notify hook (+0xc), which is loaded only if that bit is set. The rig at +0x384 is
 * reset when there is one, +0x38c is raised, and unless +0x50 is exactly 1 that is where it stops.
 *
 * The two forwarded VecFx32 explain the tail. 020d43a0 takes (ctx, mode, VecFx32, VecFx32): the first VecFx32
 * goes in r2/r3 plus the outgoing slot at sp+0, so the SECOND lands at sp+4..0xc -- which is why
 * the frame is 0x10 and why the second is stored before the first.
 *
 * Taking `&at` is what homes the four argument registers (the stmdb {r0,r1,r2,r3} prologue): it
 * is the block start + 8, the ROM's `add r1,sp,#0x28`. Taking `&mode` instead would mark that
 * parameter address-taken and make mwcc read it back from the block (`ldr r4,[sp,#0x24]`)
 * where the ROM keeps it in r1.
 *
 * Three more knobs are load-bearing and must be kept:
 * 1. The apparent dead local at sp+4 is 020d43a0's SECOND by-value VecFx32. Reading it as a local
 *    costs 28 B and mwcc drops the store as dead.
 * 2. Bit 1 of +0x40 is a SIGNED bitfield -- `int b:1`, giving asrs. As unsigned you get lsrs.
 * 3. The hook must be captured INSIDE the condition (`(notify = *(...)) != 0`): as two separate
 *    expressions mwcc loads +0xc twice, once predicated for the test and again for the call.
 */

#include "nitro/fx_types.h"

extern void Ov107_MoveNodeAndRelayout(int self, char *ap);
extern void RefreshObjectCallbacks(int rig, int a);
extern void Ov226_Projectile_SetupFlight(void *this_, int val, VecFx32 dest, VecFx32 vec);

typedef struct {
    char pad[0x40];
    int b40_0 : 1;
    int b40_1 : 1;
    int b40_rest : 30;
} Ov221_Self;

void Ov226_HandleMessageArgs(int self, int mode, VecFx32 at, VecFx32 facing, VecFx32 dir) {
    int m;
    void (*notify)(int, int);

    m = mode;
    Ov107_MoveNodeAndRelayout(self, (char *)&at);

    /* The hook is captured INSIDE the condition on purpose: as two separate expressions mwcc
     * loads +0xc twice (once predicated for the test, once again for the call). */
    if (((Ov221_Self *)self)->b40_1 && (notify = *(void (**)(int, int))(self + 0xc)) != 0) {
        notify(self, 0);
    }
    RefreshObjectCallbacks(*(int *)(self + 0x384), 0);
    *(int *)(self + 0x38c) = 1;
    if (*(int *)(self + 0x50) != 1) {
        return;
    }

    Ov226_Projectile_SetupFlight(*(void **)(self + 0x214), m, facing, dir);
}
