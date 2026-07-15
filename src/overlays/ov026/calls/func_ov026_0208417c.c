/* Two passes over items[] (stride 0x58, count elements): first call handler A on
 * each element, then handler B on each. base is preserved across the first pass
 * (kept for the second) so i spills to the stack there. */
extern void func_ov026_02083ef4(int ctx, int element);
extern void func_ov026_02083720(int ctx, int element);
void func_ov026_0208417c(int ctx, int base, int count) {
    int i;
    for (i = 0; i < count; i++) {
        func_ov026_02083ef4(ctx, base + i * 0x58);
    }
    for (i = 0; i < count; i++) {
        func_ov026_02083720(ctx, base + i * 0x58);
    }
}
