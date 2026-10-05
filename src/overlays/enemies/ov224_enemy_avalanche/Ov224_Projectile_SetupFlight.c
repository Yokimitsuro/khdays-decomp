/* Ov224_Projectile_SetupFlight -- begin a homing move toward a freshly acquired target.
 * The caller passes the mode and two VecFx32 by value, the destination and the facing; the
 * prologue's stmdb {r0,r1,r2,r3} homes them because the facing's address is taken. Nothing happens without a target from Ov107_FindNearestObject.
 * With one: the mode goes to +0x58, the destination VecFx32 to +0x24, the tuning constants at
 * data_02041dc8 to +0x18, the curve at +0x30 is primed by Quat_FromTwoVectors from data_02042258 and
 * the facing, the progress fields (+0x48/+0x54/+0x5c/+0x60) are zeroed,
 * and the owner is put in state 1.
 *
 * The mode is cached out of its argument register (`mov r5,r1`) because no address of it is
 * ever taken: only the facing's is, for Quat_FromTwoVectors (sp+0x24). Taking `&mode` would make
 * mwcc read the mode back from the spilled block (`ldr r5,[sp,#0x14]`). Two named vectors also
 * give two independent frame offsets, the ROM's `add r2,sp,#0x24` materialised from scratch.
 *
 * Still true and worth keeping: the `m = mode` local is what earns r5 and makes the prologue push
 * {r3,r4,r5,lr}; using the parameter directly gives push {r4,lr} and a 4-byte-larger frame.
 */

#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject(int owner, int kind);
extern void Quat_FromTwoVectors(VecFx32 *curve, const VecFx32 *src, char *ap);
extern VecFx32 data_02041dc8;
extern VecFx32 data_02042258;

void Ov224_Projectile_SetupFlight(int *ctx, int mode, VecFx32 dest, VecFx32 facing) {
    int m;

    m = mode;
    ctx[0x10] = Ov107_FindNearestObject(ctx[0], 0);
    if (ctx[0x10] == 0) {
        return;
    }
    ctx[0x16] = m;
    ctx[0x17] = 0;

    *(VecFx32 *)((char *)ctx + 0x24) = dest;
    *(VecFx32 *)((char *)ctx + 0x18) = data_02041dc8;
    ctx[0x18] = 0;
    Quat_FromTwoVectors((VecFx32 *)((char *)ctx + 0x30), &data_02042258, (char *)&facing);

    ctx[0x15] = 0;
    ctx[0x12] = 0;
    *(unsigned char *)(ctx[0] + 0x1c7) = 1;
}
