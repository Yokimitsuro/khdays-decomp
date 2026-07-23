/* func_0200dc70 -- convert a packed 8-digit BCD word to its binary value, or 0 if invalid.
 * First pass rejects the whole word if any nibble is >= 10; second pass accumulates
 * nibble * 10^n from the least significant nibble up.
 *
 * The second pass gets its OWN counters in an inner block: the ROM re-materialises the
 * pair into different registers after the validation loop (i in r5 taking the literal,
 * the shift in r4 taking the copy), which reusing the outer pair cannot express. The
 * declaration order place/shift/index inside that block is what picks that colouring. */
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

    {
        int place = 1;
        unsigned int sh;
        int j;

        sh = j = 0;
        do {
            acc = place * (param_1 >> sh & 0xf) + acc;
            j = j + 1;
            place = place * 10;
            sh = sh + 4;
        } while (j < 8);
    }
    return acc;
}
