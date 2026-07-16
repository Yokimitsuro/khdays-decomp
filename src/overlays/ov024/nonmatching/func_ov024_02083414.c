/* NONMATCHING: THUMB (verify with --thumb). 40/40 bytes, ONE byte: the sense of the final
 * branch. The ROM emits `cmp r0,r4 ; bge ->r0=1 ; (fall through) r0=0`, i.e. it falls through
 * on FALSE. mwcc 3.0/139 canonicalises to `blt ->r0=0 ; (fall through) r0=1` -- falling through
 * on TRUE -- and does so for BOTH source forms (`if (x < n) return 0; return 1;` and
 * `if (x >= n) return 1; return 0;` and the bare `return x >= n;`). Compiler canonicalisation,
 * not steerable.
 *
 * func_ov024_02083414 -- MobiClip player: may the script wait `frames` more?
 * Playback that is not aborting always may. Once an abort is pending a zero wait is refused
 * outright, and any other wait only clears if enough decoded frames are still buffered
 * (func_ov024_02084e68). */
extern int func_ov024_02082eb8(void);
extern int func_ov024_02084e68(void);

int func_ov024_02083414(int unused, int frames) {
    if (func_ov024_02082eb8() == 0) {
        return 1;
    }
    if (frames == 0) {
        return 0;
    }
    if (func_ov024_02084e68() < frames) {
        return 0;
    }
    return 1;
}
