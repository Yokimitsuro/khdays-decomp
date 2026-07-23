/* func_ov009_02052c64 -- draw a two-digit value as a right-aligned pair of digit sprites.
 * Peels the two low decimal digits off `value` (glyph = digit + 0x14) and places each at the
 * next slot to the left, starting at `tag`.
 *
 * The slot counter is decremented INSIDE the call argument (`(short)tag--`): the ROM issues the
 * `sub` between the two calls, after the argument register is set up and before the placement
 * call. A separate `tag = tag - 1;` statement schedules it after both. Same shape as func_ov008_020679f8; byte-identical twin of func_ov008_02067a7c. */
extern int func_ov009_0204e42c(void);
extern int func_ov009_020525cc(int ctx, int tag);
extern void func_ov009_0205267c(int ctx, int entry, int tag, int flags);

void func_ov009_02052c64(int tag, int value) {
    int i;
    int ctx = func_ov009_0204e42c();

    for (i = 0; i < 2; i++) {
        int digit = value % 10;
        int entry = func_ov009_020525cc(ctx, (unsigned short)(digit + 0x14));
        func_ov009_0205267c(ctx, entry, (short)tag--, 0x16);
        value = (value / 10) & 0xffff;
    }
}
