/* Rebind the emitter's five slots to the current source.
 *
 * For each slot: if it still holds a handle, release it (func_02014dc4) and clear the
 * slot; then rebind unconditionally -- the `beq` skips only the release and the clear,
 * not the two calls that follow.
 *
 * PARKED behind three externs declared with EMPTY parentheses, which is the absence of
 * a prototype rather than a declaration of one, so nothing checked the calls:
 *   - func_02014dc4 takes (base, item); the park passed only the base.  The ROM's
 *     `ldr r1,[r0,#0xc]` before the `cmp` is still live at the `bl`.
 *   - func_0202accc and func_01fff774 take the slot index as UNSIGNED SHORT.  That is
 *     the `lsl #0x10 ; lsr #0x10` pair in the ROM and it is worth 8 bytes; passing an
 *     int leaves the function short and looks like a codegen difference.
 * The correct prototypes were already written down in ov038's parked file next door.
 */
extern void func_01fff774(void *p, unsigned short i, int z);
extern void func_02014dc4(void *base, int item);
extern void func_0202accc(void *p, unsigned short i, int a, short m);

void func_ov030_020b4048(int r0, int r1) {
    int i;
    for (i = 0; i < 5; i++) {
        if (((int *)r0)[i + 3] != 0) {
            func_02014dc4((void *)(r0 + 0x20), ((int *)r0)[i + 3]);
            ((int *)r0)[i + 3] = 0;
        }
        func_0202accc((void *)r0, i, r0 + 0x108, (short)r1);
        func_01fff774((void *)r0, i, 0);
    }
}
