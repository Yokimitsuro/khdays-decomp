/* NONMATCHING -- 128/128 bytes, instruction for instruction identical, ONE register pair
 * transposed: the original colors {result=r4, arg0=r5, base=r6, p=r7}, mwcc gives base r7 and
 * p r6. Everything else, including the whole comparison chain, now matches.
 *
 * IMPROVED 2026-07-22, and the improvement is the reusable part: the zeroed `stack[1]` is
 * written FROM the result variable, not from its own literal. The original's
 *     mov r0, r4 ; str r0, [sp, #4]
 * is `stack[1] = result;` -- with `stack[1] = 0;` mwcc materialises a second zero and the
 * whole tail shifts. Same lens as func_ov000_02054ac8 (`r = offset;`).
 *
 * What is left looks like an allocation-priority difference: base and p are both live across
 * calls, base for the whole function and p only from the middle, and the original hands the
 * lower register to the longer range while mwcc does the opposite. Ruled out: all six
 * declaration orders of {result, base, p}, p declared inside the if versus hoisted, the stack
 * array first versus last, and base typed `int *` with scaled indices instead of `char *`.
 * All are byte-identical to each other.
 *
 * Answers whether the actor should break off: only when func_ov022_020ad114 says it is
 * engaged, the target has pulled at least 0x2000 ahead on the second axis, the separation is
 * within 0x6000, and func_ov022_0209bd04 does not report state 1. */
extern int func_ov022_020ad114(int arg0);
extern int func_ov022_020ad0c0(int arg0);
extern void VEC_Subtract(int *a, int *b, int *out);
extern int VEC_Mag(int *v);
extern int func_ov022_0209bd04(int arg0);

int func_ov022_02095dc8(int arg0) {
    char *base = (char *)(arg0 + 0x8c);
    int result = 0;
    int stack[3];
    if (func_ov022_020ad114(arg0)) {
        int *p = (int *)func_ov022_020ad0c0(arg0);
        VEC_Subtract(p, (int *)(base + 0x400), stack);
        stack[1] = result;
        if (p[1] - *(int *)(base + 0x404) >= 0x2000 &&
            VEC_Mag(stack) <= 0x6000 &&
            func_ov022_0209bd04(arg0) != 1) {
            result = 1;
        }
    }
    return result;
}
