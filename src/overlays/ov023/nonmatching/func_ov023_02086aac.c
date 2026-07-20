/* UNFINISHED. 136/136 bytes.  ONE register differs; every other byte matches.
 *
 * Script VM command: interpolate a value on an actor over a frame countdown.
 * Operands sit at fixed offsets in the command block -- +0x00 actor id, +0x08
 * and +0x10 two fx32 endpoints, +0x18 an int, +0x24 the remaining frames.
 * Each tick it decrements +0x24; on reaching zero it applies the final value and
 * returns 1 (command finished), otherwise it advances the interpolation, applies
 * it, re-arms via func_020219b4 and returns 0 (still running).
 * Reads its operands through ScriptVm_ReadOperandInt / ScriptVm_ReadOperandFx32.
 *
 * WHAT DIFFERS:
 *   ROM   subs r2, r0, #1 ; str r2,[r5,#0x24]
 *   ours  subs r0, r0, #1 ; str r0,[r5,#0x24]
 * The ROM decrements into a FRESH register, leaving the pre-decrement value
 * alive in r0 even though nothing reads it again -- a loose two-colouring.
 *
 * RULED OUT: an explicit temp for the decremented value (plus all 120
 * declaration permutations with that temp), `--*p == 0`, `*p -= 1`, and
 * `(*p)-- == 1` (that one goes +2 bytes).
 *
 * Same class as func_ov010_0204cac0 and func_ov107_020c9a10: the compiler picks
 * the tight colouring, the ROM spent a spare register, and no source form found
 * so far moves it.  Three instances in one day suggests the lever, if it exists,
 * is one idiom rather than three separate ones.
 */
/* Script VM command: interpolate a value on an actor over a countdown.
 * Operands live at fixed offsets in the command: +0 actor id, +0x08 and +0x10
 * two fx32 endpoints, +0x18 an int, +0x24 the remaining frame count. */
extern int func_02021980(void *vm, void *op);   /* ScriptVm_ReadOperandInt */
extern int func_02021994(void *vm, void *op);   /* ScriptVm_ReadOperandFx32 */
extern int *func_0202bfcc(unsigned short actorId);
extern void func_02016d10(int target, int value);
extern int func_0202136c(int a, int b);
extern int func_02021404(int a, int b, int c);
extern void func_020219b4(void *vm, void *op);

int func_ov023_02086aac(void *vm, char *op) {
    int actor;
    int a;
    int b;
    int cur;

    actor = func_02021980(vm, op);
    a = func_02021980(vm, op + 0x18);
    b = func_02021994(vm, op + 8);
    cur = func_02021994(vm, op + 0x10);
    func_0202bfcc((unsigned short)actor);
    *(int *)(op + 0x24) = *(int *)(op + 0x24) - 1;
    if (*(int *)(op + 0x24) == 0) {
        func_02016d10(func_0202bfcc((unsigned short)actor)[0x7c / 4], cur >> 12);
        return 1;
    }
    cur = func_02021404(func_0202136c(2, a), cur, b);
    func_02016d10(func_0202bfcc((unsigned short)actor)[0x7c / 4], cur >> 12);
    func_020219b4(vm, op);
    return 0;
}
