/* NONMATCHING — pure register-coloring permutation (112/112 bytes, byte-structurally
 * identical: same opcodes, same immediates, same control flow — the second loop's
 * counter and shift registers are swapped, mine r4/r5 vs the original's r5/r4).
 *
 * Parse a packed 8-digit BCD value (little nibble first) into an int. First pass
 * validates every nibble is 0-9 (returns 0 on any invalid nibble); second pass
 * accumulates nibble * 10^position.
 *
 * The first loop matches exactly (counter r2 / shift r3). In the second loop mwcc
 * colors counter->r4 / shift->r5 while the original uses counter->r5 / shift->r4.
 * Both init the counter to 0 then copy it to the shift (`mov X,#0; mov Y,X`), so the
 * mov pattern is identical — only the physical register choice differs, and with no
 * calls it is arbitrary/unsteerable. Tried: reordering the increment stmts, the >=10
 * vs 9< guard form (that half matched -> `cmp #0xa; movhs`). The raw blob keeps the
 * build byte-exact; this documents the equivalent C.
 */
int func_0200dc70(unsigned int param_1) {
    int acc = 0;
    int i = 0;
    unsigned int shift = 0;

    do {
        if ((param_1 >> shift & 0xf) >= 10) {
            return 0;
        }
        i = i + 1;
        shift = shift + 4;
    } while (i < 8);

    i = 0;
    shift = 0;
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
