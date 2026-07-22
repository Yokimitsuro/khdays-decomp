/* ** SUPERSEDED 2026-07-22: MATCHED, and the whole family with it (six functions
 * across ov000, ov005, ov008, ov009, ov025, ov026). See staging/ov000/.
 *
 * THE ANSWER WAS ARITY. func_02032634 takes THREE arguments, not one:
 *     func_02032634(a, previous[i + 5], previous[i + 13]);
 * The two loaded values sit in r1 and r2 because they ARE the call's arguments. The
 * ROM's `ldrne r1,[r0,#0x14]` / `ldrne r2,[r0,#0x34]` load them straight into the
 * argument registers. Nothing about register allocation was ever involved.
 *
 * ** AND THE NOTE THAT USED TO SIT HERE WAS MEASURING THE WRONG AXIS. It said the diff
 * was "which registers the two predicated chains use", recorded three ruled-out
 * spellings of naming the values as locals, and concluded "whatever makes the ROM spend
 * a second register does NOT come from the values being named". Every word of that is
 * true and all of it is useless, because the question was never why a second register
 * appears -- it was what wants a value in r1 and r2, and the answer to that is always
 * "a call".
 *
 * The project's own checklist says exactly this: when a diff is a value in an unexpected
 * register, check the arity of every call that could want it, BEFORE concluding register
 * allocation. I wrote a ruled-out note without running it. Second time in this session:
 * the same omission produced the false "the struct rewrite makes it worse" note on
 * func_ov294_020d1a24 (retracted in c9113c1f).
 *
 * The pattern worth naming: I run the checklist when I am trying to MATCH a function,
 * and skip it when I am trying to EXPLAIN one. A ruled-out note is a claim about the
 * function and needs the same evidence as a park.
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
