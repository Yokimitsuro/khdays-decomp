/* Two passes over items[] (stride 0x58, count elements): first call handler A on
 * each element, then handler B on each. base is preserved across the first pass
 * (kept for the second) so i spills to the stack there. */
extern void func_ov009_02051544(int ctx, int element);
extern void func_ov009_02050d60(int ctx, int element);
void func_ov009_020517cc(int ctx, int base, int count) {
    int i;
    for (i = 0; i < count; i++) {
        func_ov009_02051544(ctx, base + i * 0x58);
    }
    for (i = 0; i < count; i++) {
        func_ov009_02050d60(ctx, base + i * 0x58);
    }
}
