/* NONMATCHING -- 60/60 B. The FIRST loop now matches; the second loop's two counters
 * are still register-swapped (ROM: i=r5 gets the literal, shift=r4 the copy; mwcc the
 * other way round).
 *
 * IMPROVED 2026-07-18: the initialisation is a THREE-WAY CHAIN, `shift = i = acc = 0;`
 * (ROM: `mov ip,#0 ; mov r2,ip ; mov r3,ip`). Three separate `= 0` initialisers each
 * materialise their own zero and mis-colour the first loop.
 *
 * Ruled out for the second loop: `shift = i = 0` and `i = shift = 0` (both orders),
 * swapping the declaration order of i/shift (fixes loop 2, breaks loop 1 -- the two
 * loops want opposite colourings), and giving the second loop its own fresh counters
 * in an inner block, in both declaration orders. */
int func_0200dc70(unsigned int param_1) {
    int acc;
    int i;
    unsigned int shift;

    shift = i = acc = 0;

    do {
        if ((param_1 >> shift & 0xf) >= 10) {
            return 0;
        }
        i = i + 1;
        shift = shift + 4;
    } while (i < 8);

    shift = i = 0;
    {
        int place = 1;
        do {
            acc = place * (param_1 >> shift & 0xf) + acc;
            i = i + 1;
            place = place * 10;
            shift = shift + 4;
        } while (i < 8);
    }
    return acc;
}
