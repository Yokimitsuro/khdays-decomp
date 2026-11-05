/*
 * Ov008_WorldMap_InitObjectListRetry - build the menu object list, retrying with an
 * incrementing configuration byte until it settles, then do a final plain build. Called
 * from Ov008_WorldMap_StateTick state 0 (alt path, when the context field is set).
 *
 * Copies the 3-word init params to a local, then up to 12 times: sets the second word's
 * high bits from the retry counter (keeping its low byte), builds the object list at
 * obj+0x13fc (ov008_InitObjectWithList), and checks the context via
 * Ov025_GetNextMissionEntry_5(Ov008_GetCtxField967c()) - returning as soon as that is non-zero.
 * Otherwise it tears the list back down (Ov025_DestroyMissionList) and retries with the retry
 * counter shifted up by 0x100. If all 12 attempts fail, it re-copies the original params
 * and builds the list one last time.
 *
 * The 3-word params are copied as a struct (ldm/stm). ov008_InitObjectWithList takes 2
 * args (list, params) - Ghidra's trailing r2/r3 args are leftover-register phantoms.
 */

#include "nitro/types.h"

typedef struct { int f0; int f4; int f8; } ObjListParams;

extern void Ov025_InitObjectWithList(int list, ObjListParams *p);
extern u32  Ov025_GetCtxField967c(void);
extern int  Ov025_GetNextMissionEntry_5(u32 a);
extern void Ov025_DestroyMissionList(int list);

void Ov025_WorldMap_InitObjectListRetry(int obj, ObjListParams *params)
{
    ObjListParams local;
    int tries;
    u32 shift;

    local = *params;
    tries = 0;
    shift = 0;
    do {
        local.f4 = (local.f4 & 0xff) | shift;
        Ov025_InitObjectWithList(obj + 0x13fc, &local);
        if (Ov025_GetNextMissionEntry_5(Ov025_GetCtxField967c()) != 0) return;
        Ov025_DestroyMissionList(obj + 0x13fc);
        tries++;
        shift += 0x100;
    } while (tries < 0xc);
    local = *params;
    Ov025_InitObjectWithList(obj + 0x13fc, &local);
}
