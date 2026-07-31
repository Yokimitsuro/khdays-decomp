/*
 * Ov008_MainMenu_InitObjectListRetry - build the menu object list, retrying with an
 * incrementing configuration byte until it settles, then do a final plain build. Called
 * from Ov008_MainMenu_StateTick state 0 (alt path, when the context field is set).
 *
 * Copies the 3-word init params to a local, then up to 12 times: sets the second word's
 * high bits from the retry counter (keeping its low byte), builds the object list at
 * obj+0x13fc (ov008_InitObjectWithList), and checks the context via
 * func_ov008_0205b6e8(Ov008_GetCtxField967c()) - returning as soon as that is non-zero.
 * Otherwise it tears the list back down (func_ov008_0205658c) and retries with the retry
 * counter shifted up by 0x100. If all 12 attempts fail, it re-copies the original params
 * and builds the list one last time.
 *
 * The 3-word params are copied as a struct (ldm/stm). ov008_InitObjectWithList takes 2
 * args (list, params) - Ghidra's trailing r2/r3 args are leftover-register phantoms.
 */

typedef unsigned int u32;

typedef struct { int f0; int f4; int f8; } ObjListParams;

extern void func_ov008_0205652c(int list, ObjListParams *p);
extern u32  func_ov008_020511e0(void);
extern int  func_ov008_0205b6e8(u32 a);
extern void func_ov008_0205658c(int list);

void func_ov008_0205b19c(int obj, ObjListParams *params)
{
    ObjListParams local;
    int tries;
    u32 shift;

    local = *params;
    tries = 0;
    shift = 0;
    do {
        local.f4 = (local.f4 & 0xff) | shift;
        func_ov008_0205652c(obj + 0x13fc, &local);
        if (func_ov008_0205b6e8(func_ov008_020511e0()) != 0) return;
        func_ov008_0205658c(obj + 0x13fc);
        tries++;
        shift += 0x100;
    } while (tries < 0xc);
    local = *params;
    func_ov008_0205652c(obj + 0x13fc, &local);
}
