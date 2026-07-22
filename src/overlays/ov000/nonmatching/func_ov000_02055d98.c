/* UNFINISHED -- 120/120 bytes, 14 differing. Head of a SIX-member family
 * (ov000, ov005, ov008, ov009, ov025, ov026), so cracking it pays 6 functions.
 *
 * The whole diff is which registers the two predicated short-circuit chains use:
 *      ROM:   addne r0, r5, r4, lsl #2 ; ldrne r1, [r0,#0x14] ; cmpne r1, r8
 *                                        ldrne r2, [r0,#0x34] ; cmpne r2, r8
 *      ours:  addne r1, r5, r4, lsl #2 ; ldrne r0, [r1,#0x14] ; cmpne r0, r8
 *                                        ldrne r0, [r1,#0x34] ; cmpne r0, r8
 * The ROM gives the two loaded values TWO DISTINCT registers (r1, r2) and puts the
 * pointer in r0; we reuse r0 for both loads and put the pointer in r1. Everything
 * else -- the 0x4000/0xa70 base split held in sb, the -1 kept in r8 via `mvn`, the
 * two un-merged calls, the loop -- already matches.
 *
 * RULED OUT 2026-07-22: naming the two loaded values as locals, which is the obvious
 * reading of "the ROM keeps both live". Three spellings, all 128 B = 8 OVER:
 * two locals reused across both branches, a walking `p = base + i` plus two locals,
 * and four separate locals. Introducing the locals defeats mwcc's if-conversion of
 * the `&&` chain, so the predication collapses and the function grows. Whatever makes
 * the ROM spend a second register does NOT come from the values being named.
 */
extern int func_02032634();

void func_ov000_02055d98(char *a, int *b)
{
    int i = 0;
    int *r5 = *(int **)(a + 0x4a70);

    for (; i < 2; i++) {
        if (r5 != 0) {
            if (r5[i + 5] != -1 && r5[i + 13] != -1)
                func_02032634(a);
        }
        if (b != 0) {
            if (b[i + 5] != -1 && b[i + 15] != -1)
                func_02032634(a);
        }
        *(int **)(a + 0x4a70) = b;
    }
}
