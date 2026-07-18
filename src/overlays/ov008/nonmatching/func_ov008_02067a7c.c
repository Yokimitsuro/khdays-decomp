/*
 * func_ov008_02067a7c -- x3 (ov008/...). Render the low two decimal digits of `value` into slots.
 * From the least-significant digit down, look up the glyph entry for digit (tag digit+0x14) with
 * 02055808 and stamp it into slot `tag` via 020558b8(ctx, entry, (short)tag, 0x16). Divide by 10
 * (keeping 16 bits) and step tag down, for two digits.
 *
 * NON-MATCHING: same loop-update instruction-scheduling tie as func_ov008_020679f8 (see its note and
 * deferred-ties.md). Size-exact (144B); the independent `sub tag,#1` (tag--) and `add i,#1` (i++) land
 * at different points. The retail compiler interleaves `tag--` into the second call's argument setup
 * and places `i++` after the value/10 update; mwcc 3.0/139 defers `i++` to just after the call and
 * `tag--` to the loop bottom. Source-order moves and a `(short)tag` temp do not change mwcc's schedule.
 * Identical result.
 */
extern int func_ov008_02050c28(void);
extern int func_ov008_02055808(int ctx, int tag);
extern void func_ov008_020558b8(int ctx, int entry, int tag, int flags);

void func_ov008_02067a7c(int tag, int value) {
    int i;
    int ctx = func_ov008_02050c28();

    for (i = 0; i < 2; i++) {
        int digit = value % 10;
        int entry = func_ov008_02055808(ctx, (unsigned short)(digit + 0x14));
        func_ov008_020558b8(ctx, entry, (short)tag, 0x16);
        value = (value / 10) & 0xffff;
        tag = tag - 1;
    }
}
