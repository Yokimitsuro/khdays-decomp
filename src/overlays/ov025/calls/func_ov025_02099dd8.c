/* func_ov025_02099dd8 -- draw a non-negative number as a right-aligned run of digit sprites.
 * Peels decimal digits off the low end, allocates a sprite entry for each (glyph = digit + 10)
 * and places it at the next slot to the left, starting at slot 9.
 *
 * The slot counter is decremented INSIDE the call argument (`(short)tag--`). The ROM issues the
 * `sub` between the two calls, i.e. after the argument register is set up and before the placement
 * call -- which is exactly what a post-decrement produces and what a separate `tag = tag - 1;`
 * statement does not.
 * Byte-identical twin of func_ov008_020679f8. */
extern int func_ov025_02084a50(void);
extern int func_ov025_020894b0(int ctx, int tag);
extern void func_ov025_02089560(int ctx, int entry, int tag, int flags);

void func_ov025_02099dd8(int n) {
    int ctx;
    int tag;

    tag = 9;
    ctx = func_ov025_02084a50();
    do {
        int digit = n % 10;
        int entry = func_ov025_020894b0(ctx, (unsigned short)(digit + 10));
        func_ov025_02089560(ctx, entry, (short)tag--, 0x14);
        n = n / 10;
    } while (n > 0);
}
