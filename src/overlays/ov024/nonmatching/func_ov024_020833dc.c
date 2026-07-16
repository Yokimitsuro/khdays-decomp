/* func_ov024_020833dc -- MobiClip: has this stream reached its end? (THUMB)
 * Resolves the descriptor to a length, and reports done unless the clock has caught up with it:
 * a zero length means "never done" (an open-ended stream), otherwise the current position from
 * func_ov024_02084e68 must have reached it. If func_ov024_02082eb8 rejects the resolved handle
 * outright the stream counts as done.
 * blx on 02082eb8 / 02084e68 because both are ARM.
 *
 * NONMATCHING: 54/54 bytes, byte-exact through 0x2b; only the final 0/1 return's block layout
 * differs. The ROM ends `cmp r0,r4 ; bge L ; movs r0,#0 ; pop ; L: movs r0,#1 ; pop` -- return 0
 * inline, return 1 out of line. mwcc emits the mirror (`blt L ; movs r0,#1 ; pop ; L: movs r0,#0`)
 * and will not be talked out of it: it canonicalises a 0/1 boolean return and picks the layout
 * itself, ignoring how the source is written.
 * Tried and rejected, all four identical at 0x2d:
 *   if (pos >= len) return 1; return 0;      <- source order matching the ROM's semantics
 *   if (pos <  len) return 0; return 1;      <- inverted sense (the usual block-layout crack)
 *   return pos >= len;                       <- direct boolean
 *   if (pos >= len) goto reached; return 0; reached: return 1;   <- goto, which defeats other
 *                                                                   canonicalisations but not this
 * Note the earlier `return 1` / `return 0` pairs at 0x1a/0x22 DO come out right -- it is only the
 * comparison-fed one that gets normalised. The preset-flag crack does not apply: that one is for
 * ARM predication (moveq/movne), and THUMB has none. */
extern int func_02021980(int owner, void *entry);
extern int func_020219b4(int owner, int handle);
extern int func_ov024_02082eb8(int handle);
extern int func_ov024_02084e68(void);

int func_ov024_020833dc(int owner, void *entry) {
    int len;

    len = func_02021980(owner, entry);
    if (func_ov024_02082eb8(func_020219b4(owner, len)) == 0) {
        return 1;
    }
    if (len == 0) {
        return 0;
    }
    if (func_ov024_02084e68() >= len) {
        return 1;
    }
    return 0;
}
