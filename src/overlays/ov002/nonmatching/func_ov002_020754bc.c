/* NON-MATCHING: common-subexpression-elimination tie (twin ov023_020854c0 ties identically).
 *
 * Advance a byte cursor (*pidx into the string at base) past one glyph/token, classifying the
 * lead byte: a control code 1..0x1f advances 1 (code 3 = end-of-line advances 1 more, returns 1);
 * printable ASCII 0x20..0x7f advances 1; a UTF-8 lead 110xxxxx advances 2, 1110xxxx advances 3.
 * Stops at (and returns 0 on) NUL. THUMB.
 *
 * The control flow, the branch order (control-first fall-through), the shared return-0 epilogue
 * and the hoisted 0xe0/0xf0 masks are all byte-exact. The only residue: the ROM reads the byte
 * TWICE per iteration -- once for the null test (loop condition) and once at the body top for
 * classification -- whereas mwcc common-subexpression-eliminates the two identical `str[idx]`
 * loads into one, coming out 1 instruction (2 bytes) shorter. Splitting into distinct `char c`
 * (condition) and `int ch` (body) locals does not defeat the CSE (no store aliases the string
 * between the two reads), and build_sweep gives 104 on every one of the 27 builds. The retail
 * compiler simply did not CSE across the loop back-edge here -- a compiler-version difference.
 */

int func_ov002_020754bc(int base, int *pidx) {
    int idx = *pidx;
    while (*(signed char *)(base + idx) != 0) {
        int ch = *(signed char *)(base + idx);
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
