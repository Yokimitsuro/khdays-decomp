/* NONMATCHING: instruction-scheduling tie. The original materializes the slot
 * address (base + arg1*0x58) INSIDE the taken branch (guard uses register-offset
 * [r1,r3]); mwcc hoists the `add` above the `tst`/`bne`. One-instruction position
 * difference; everything else (ldm/stm vec3 copy, the zero-fill) matches.
 * Semantics: if slot flag bit2 is clear, copy the vec3 at slot+0x4c into arg2;
 * else zero arg2. Slot = *(arg0+0x2684) + arg1*0x58. */
typedef struct { int a, b, c; } T3_020ad7f0;
void func_ov022_020ad7f0(int arg0, int arg1, T3_020ad7f0 *arg2) {
    int base = *(int *)(arg0 + 0x2684);
    if ((*(unsigned int *)(base + arg1 * 0x58) & 4) == 0) {
        *arg2 = *(T3_020ad7f0 *)(base + arg1 * 0x58 + 0x4c);
        return;
    }
    arg2->c = 0;
    arg2->b = 0;
    arg2->a = 0;
}
