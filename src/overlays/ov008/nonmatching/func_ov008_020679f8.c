/*
 * func_ov008_020679f8 -- x3 (ov008/...). Render a non-negative integer as decimal digits into slots.
 * Working from the least-significant digit at slot tag 9 downward, look up the glyph entry for digit
 * (via tag digit+10) with 02055808, and stamp it into the slot for tag `tag` via 020558b8(ctx, entry,
 * (short)tag, 0x14). Divide by 10 and repeat until the value is exhausted.
 *
 * NON-MATCHING: size-exact (132B) and byte-exact EXCEPT the position of the single `sub r8,r8,#1`
 * (tag--) instruction. The retail compiler schedules it up into the second call's argument setup
 * (between the (short)tag materialisation and the call); mwcc 3.0/139 defers the independent decrement
 * to the loop bottom just before the branch. Tried: declaring tag before/after ctx, split decl/init,
 * moving `tag = tag - 1` above `n = n / 10`, and materialising `(short)tag` into a temp before the
 * decrement -- mwcc's instruction scheduler re-orders the independent decrement regardless of source
 * order. One-instruction scheduling tie; identical result.
 */
extern int func_ov008_02050c28(void);
extern int func_ov008_02055808(int ctx, int tag);
extern void func_ov008_020558b8(int ctx, int entry, int tag, int flags);

void func_ov008_020679f8(int n) {
    int ctx;
    int tag;

    tag = 9;
    ctx = func_ov008_02050c28();
    do {
        int digit = n % 10;
        int entry = func_ov008_02055808(ctx, (unsigned short)(digit + 10));
        func_ov008_020558b8(ctx, entry, (short)tag, 0x14);
        n = n / 10;
        tag = tag - 1;
    } while (n > 0);
}
