/* func_ov012_0205b9e0 -- MobiClip player: may the script wait `frames` more?
 * Playback that is not aborting always may. Once an abort is pending a zero wait is refused
 * outright, and any other wait only clears if enough decoded frames are still buffered
 * (func_ov024_02084e68).
 *
 * The redundant `pos >= frames` test is load-bearing, not a typo. mwcc recognises the pattern
 * `if (c) return 0; return 1;` as the boolean `!c` and then materialises it with a FIXED block
 * order -- `blt L ; movs r0,#1 ; pop ; L: movs r0,#0 ; pop` -- ignoring how the source is
 * written. The ROM has the mirror image (`bge L ; movs r0,#0 ; pop ; L: movs r0,#1 ; pop`),
 * which is the ordinary "then-arm inline" layout mwcc uses for every constant pair that is NOT
 * (0, 1): with `return 0` / `return 2` the ROM's order comes out at the first compile. A second
 * `if` whose condition mwcc can prove redundant costs no instruction and takes the return pair
 * out of that special case, so the natural layout is restored. Measured across all 27 mwccarm
 * builds, 13 optimisation levels and 25 flag combinations: the fold is universal, so the source
 * has to dodge it rather than the compiler be talked out of it. */
extern int func_ov012_0205b258(void);
extern int func_ov024_02084e68(void);

int func_ov012_0205b9e0(int unused, int frames) {
    int buffered;

    if (func_ov012_0205b258() == 0) {
        return 1;
    }
    if (frames == 0) {
        return 0;
    }

    buffered = func_ov024_02084e68();
    if (buffered < frames) {
        return 0;
    }
    if (buffered >= frames) {
        return 1;
    }
    return 1;
}
