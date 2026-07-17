/*
 * func_ov212_020cd524 -- UNFINISHED (x3 family: ov212/266/267, worth 3).
 * 180/180 bytes, instruction-for-instruction identical, ONE diff at 0x15.
 *
 * WHAT IT IS (this part is solved; the pool decodes cleanly):
 *   param_3 is a path/polyline blob: a 4-byte header (an angle in DEGREES) followed
 *   by N vec3 points. param_2 is the blob's byte size, so (param_2 - 4) / 12 == N.
 *   Rebuild the owner's point list at +0x5e4 (destroy + re-init), convert the header
 *   angle to Q12 radians and cache it at +0x584, then allocate one 12-byte node per
 *   point (func_01fffca8(list, 12, 100)) and copy the point into it.
 *   Pool: -12868 == -0x3244 == -pi in Q12; 0xb60b60b7 >> 7 == the /180 magic;
 *   0xaaaaaaab >> 3 == the unsigned /12 magic. So +0x584 = deg * -PI_Q12 / 180.
 *
 * THE DIFF: two values are saved into callee-saved registers at +0x014/+0x018, in
 * the same order, by the same two instructions -- only the registers are swapped.
 *      ROM:   mov r6, r1        (param_2, later reused as N)
 *             add r4, r5, #4    (the point array)
 *      mine:  mov r4, r1
 *             add r6, r5, #4
 * Everything from 0x2c to the end is byte-identical, including the walking pointer
 * (`add r4,r4,#0xc`), both division magics and the whole loop.
 *
 * PRE-PARK CHECKLIST -- all four run, none explains it:
 *  1. --thumb: verified. ARM gives an exact 180/180; THUMB gives 104 != 180. It is ARM.
 *  2. Arity of every callee, checked against the ROM's own register setup and the tree:
 *     NNSi_FndDestroyDoubleList(list) sets r0 only; func_01fffc24(list) sets r0 only;
 *     func_01fffca8(list, 12, 100) sets r0/r1/r2 and its result is the copy's dst.
 *     All three agree with their declarations. This is NOT the dropped-arg class.
 *  3. No constant is in the wrong register -- the two swapped values are a parameter
 *     and a derived pointer, not a hoisted literal.
 *  4. Diff read back: it really is only those two registers, and the swap propagates
 *     nowhere else because both are dead by the epilogue.
 *
 * RULED OUT (11 spellings, every one still 180 B; the axis is declaration/first-use
 * order, and the diff offset in brackets is how far in it got):
 *   src-decl-first + `int i = 0`            [0xD]  <- decl-init hoists `mov r5,#0`
 *                                                     above the first bl; the ROM
 *                                                     emits it at +0x5c. Fixing that
 *                                                     alone moved the diff 0xD -> 0x15.
 *   src-decl-first + `for (i = 0; ...)`     [0x15]
 *   n, i, then src                          [0x15]
 *   i, n, then src                          [0x15]
 *   src declared, assigned after the calls   [0xC]
 *   walking pointer (`*src; src++`)          [0xD]
 *   walking pointer + n declared first       [0xD]
 *   src as `(struct vec3 *)(param_3 + 1)`   [0x15]
 *   struct Path {int deg; vec3 pts[1];}, n/i [0x5]  <- worse: changes the param saves
 *   struct Path, i/n                         [0x5]
 *   struct Path + a src local                [0x15]
 *   `int n = (param_2-4)/12` as a decl-init  [176 B] <- lets mwcc compute N before the
 *                                                       calls, so param_2 never needs
 *                                                       saving: 1 instruction short.
 *                                                       The ROM computes N *after*, so
 *                                                       the save is load-bearing.
 *   `unsigned int n` (declared unsigned)     [176 B] <- also 1 short. N is produced by
 *                                                       an unsigned divide but the ROM
 *                                                       compares it SIGNED (`cmp r6,#0`
 *                                                       + `pople`, and `blt` at the
 *                                                       loop foot), so `int n` is
 *                                                       required and the `(unsigned)`
 *                                                       cast belongs on the divide only
 *                                                       -- which is what the kept
 *                                                       version does.
 *
 * NEXT STEP: attack ONLY which callee-saved register the surviving parameter lands in.
 * The two candidates are both live across the same two calls with the same first-use
 * order, so nothing in the source distinguishes them by the usual levers. What is left
 * is something that changes their relative LAST use (the ROM's r4 dies in the loop
 * body, r6 at the loop's compare) -- e.g. a form where the point pointer is consumed
 * after the bound. Every axis I could name is listed above as tried; I do not have a
 * fresh idea, which is why this is parked rather than ground on.
 *
 * Do NOT file this under "regalloc tie" and move on -- that label is what the project
 * has been wrong about ~20 times. It is an unexplained two-register swap on an
 * otherwise perfect 180-byte function, and the analysis above is complete.
 */
struct vec3 { int x, y, z; };

extern void NNSi_FndDestroyDoubleList(void *list);
extern void func_01fffc24(int list);
extern int *func_01fffca8(int list, int a, int b);

void func_ov212_020cd524(int param_1, int param_2, int *param_3) {
    struct vec3 *src = (struct vec3 *)((char *)param_3 + 4);
    int n;
    int i;

    NNSi_FndDestroyDoubleList((void *)(param_1 + 0x5e4));
    func_01fffc24(param_1 + 0x5e4);
    *(int *)(param_1 + 0x584) = param_3[0] * -0x3244 / 180;
    n = (unsigned int)(param_2 - 4) / 12;
    for (i = 0; i < n; i++) {
        *(struct vec3 *)func_01fffca8(param_1 + 0x5e4, 12, 100) = src[i];
    }
}
