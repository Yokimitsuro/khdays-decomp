/* func_ov011_0205d508 -- Ov011_EmitSlotGfx (348 B, ARM, 8 relocs). Direct dependency of
 * b340 (its ops 6/7). Emits GFX commands for a title pane slot: block-copies a 4x4-int
 * command template (data_ov011_0205dcd0) to the stack, computes the per-pane object
 * piVar1 = pScene + 0x18 + (slot>>1)*0x10940, submits it via func_02024c94(5 args), enqueues
 * GFXi_EnqueueCommand(4 args) from template rows tmpl[slot][k], branches on `entry`
 * (b1bc+b9f4 when set, two more GFXi when clear), then sets bit0 of the dirty flag at
 * pScene+0x23ab8. Cracks (all confirmed): 2D array int[4][4] indexed [slot][k] gives the
 * ROM's `ldr rD,[base,slot,lsl#4]`; `if(entry != 0){...}else{...}` gives the ROM's `beq`;
 * SHARE slot>>1 in a named `half` (ROM keeps it in r5 for both off and the b9f4 arg); and
 * pScene must be RELOADED each use, NOT cached (caching shrinks to 324 B -- the ROM rereads
 * data_e960[1] every time).
 *
 * STATE: DIFIERE, SIZE-EXACT + INSTRUCTION-EXACT (348 == 348), 42 register-field diffs
 * (was 44; a 24-perm declaration-order sweep found `off` BEFORE `half` fixes off->r7 to match
 * the ROM). Declarations are separated from initializers so decl order is a free lever.
 * ⚠ The old "build-version tie / need retail mwcc 3.0>=140" conclusion is RETRACTED -- its
 * sibling b9f4 carried the identical "instruction-exact, only registers differ" residue and
 * was matched BYTE-EXACT with build 139 by clamping its signed param FIRST (which anchored
 * param_1 to fp and cascaded the whole allocation). d508 is the SAME kind of source-shape
 * problem. Residue = an entry-region register permutation: ROM assigns a clean sequence
 * r4=slot, r5=half, r6=base/pScene, r7=off, r8=entry (and uses lr/ip for the template copy),
 * loading pScene EARLY interleaved with the copy; mine permutes (slot->r5, entry->r4) and
 * defers the pScene load past the copy, so the copy takes r6 instead of ip. Remaining residue: mwcc's SCHEDULER loads the &data_e960 pool address late (into ip, just
 * before the first call) whereas the ROM loads it EARLY into a scratch arg reg (r1) interleaved
 * with the template copy -- which frees ip so the copy uses lr/ip (ROM) instead of r6/lr (mine),
 * and this forces entry->r4 instead of r8. All source steering of the load timing is inert
 * (early local, touch, struct-for-base, 24 decl orders): the scheduler decides. NEXT: force the
 * pScene value onto the critical path early, or find the idiom that makes mwcc pick a scratch
 * arg reg for the pool-address load.
 * BUILD SWEEP (2026-07-29, instruction-exact so valid): all 2.0/3.0 builds incl 3.0_patch4
 * (=build 139, the CORRECT compiler that matched b9f4) give "66 off"; 1.2 and dsi give wrong
 * SIZES. So no build reproduces the ROM registers with this source form -> definitively a
 * SOURCE-SHAPE problem, not a build issue (matches the b9f4 lesson: a "no build differs" sweep is
 * a property of the source form). The exhausted axes: 48 decl x init combos, share-half, no-cache
 * pScene, struct-for-base, entry/disp as pointers, global-as-struct, volatile, register, arity
 * (all callees verified), base-before-copy. Floor = 42 (down from 48). The one lever that MOVED
 * it was decl order (off before half -> off->r7). Still open: force mwcc to interleave the pScene
 * pool-load into the template copy (ROM loads &data_e960 into scratch r1 early; mine defers to ip).
 * NOT PARKED; selected function, best form held here.
 */
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct Ov011GfxTemplate { int a[4][4]; } Ov011GfxTemplate;

extern Ov011GfxTemplate data_ov011_0205dcd0;
/* khdays: shared-bss */
int data_ov011_0205e960 = 0;   /* gOv011Cursor */
int data_ov011_0205e964 = 0;   /* gpOv011Scene (kept as an int: the earlier candidate reaches the scene by arithmetic) */

extern void func_02024c94(int *slot, int *disp, int a, int b, int c);
extern int  GFXi_EnqueueCommand(int a, int b, int c, int d);
extern void func_ov011_0205b1bc(int a, int b);
extern void func_ov011_0205b9f4(int a, int b, int c, int d);

void func_ov011_0205d508(int *disp, int slot, int arg, int entry)
{
    int half;
    Ov011GfxTemplate t;
    int *piVar1;
    int off;

    half = slot >> 1;
    off = half * 0x10940;
    t = data_ov011_0205dcd0;
    piVar1 = (int *)(data_ov011_0205e964 + 0x18 + off);

    func_02024c94(piVar1, disp, arg, arg, arg);
    GFXi_EnqueueCommand(t.a[slot][0], t.a[slot][3] << 0xd,
                        *(int *)(piVar1[2] + 0xc), *(int *)(piVar1[2] + 8));
    if (entry != 0) {
        func_ov011_0205b1bc(data_ov011_0205e964 + 0x14 + off, entry);
        {
            int base = data_ov011_0205e964 + off;
            func_ov011_0205b9f4((int)piVar1, half,
                                (int)*(short *)(base + 0x10930) >> 3,
                                ((int)*(short *)(base + 0x10932) >> 3) - 1);
        }
    } else {
        GFXi_EnqueueCommand(t.a[slot][1], 0, *(int *)(piVar1[1] + 0x14),
                            *(int *)(piVar1[1] + 0x10));
        GFXi_EnqueueCommand(t.a[slot][2], 0, *piVar1 + 0xc, *(int *)(*piVar1 + 8));
    }
    *(u32 *)(data_ov011_0205e964 + 0x23ab8) =
        *(u32 *)(data_ov011_0205e964 + 0x23ab8) & 0xfffffffe | 1;
}
