/* func_ov009_02052be0 -- draw a non-negative number as a right-aligned run of digit sprites.
 * Peels decimal digits off the low end, allocates a sprite entry for each (glyph = digit + 10)
 * and places it at the next slot to the left, starting at slot 9.
 *
 * The slot counter is decremented INSIDE the call argument (`(short)tag--`). The ROM issues the
 * `sub` between the two calls, i.e. after the argument register is set up and before the placement
 * call -- which is exactly what a post-decrement produces and what a separate `tag = tag - 1;`
 * statement does not.
 * Byte-identical twin of func_ov008_020679f8. */
extern int func_ov009_0204e42c(void);
extern int func_ov009_020525cc(int ctx, int tag);
extern void func_ov009_0205267c(int ctx, int entry, int tag, int flags);

void func_ov009_02052be0(int n) {
    int ctx;
    int tag;

    tag = 9;
    ctx = func_ov009_0204e42c();
    do {
        int digit = n % 10;
        int entry = func_ov009_020525cc(ctx, (unsigned short)(digit + 10));
        func_ov009_0205267c(ctx, entry, (short)tag--, 0x14);
        n = n / 10;
    } while (n > 0);
}
