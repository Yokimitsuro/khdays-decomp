/* Advance the byte cursor *pidx past one glyph or token of the string at `base`, and
 * report whether an end-of-line was consumed. Lead-byte classes: a control code 1..0x1f
 * advances 1 (code 3 is end-of-line and advances one more, returning 1); printable ASCII
 * 0x20..0x7f advances 1; a UTF-8 lead 110xxxxx advances 2 and 1110xxxx advances 3.
 * A NUL stops the walk and returns 0.
 *
 * The ROM reads the lead byte TWICE per iteration -- once for the loop's NUL test and
 * once at the top of the body to classify it -- and mwcc commons the two identical
 * `*(signed char *)(base + idx)` loads into one, two bytes short. Nothing aliases the
 * string between them, so no ordering or extra local defeats it; spelling the body's
 * read as a SUBSCRIPT (`((signed char *)base)[idx]`) while the condition keeps the
 * dereference form does, and costs nothing. */
int func_ov002_020754bc(int base, int *pidx) {
    int idx = *pidx;

    while (*(signed char *)(base + idx) != 0) {
        int ch = ((signed char *)base)[idx];
        if (ch >= 1 && ch < 0x20) {
            *pidx += 1;
            if (ch == 3) {
                *pidx += 1;
                return 1;
            }
        } else if (ch >= 0x20 && ch < 0x80) {
            *pidx += 1;
        } else {
            if ((ch & 0xe0) == 0xc0) {
                *pidx += 2;
            } else if ((ch & 0xf0) == 0xe0) {
                *pidx += 3;
            }
        }
        idx = *pidx;
    }
    return 0;
}
