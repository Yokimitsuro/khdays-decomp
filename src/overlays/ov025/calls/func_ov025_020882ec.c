/* Two passes over items[] (stride 0x58, count elements): first call handler A on
 * each element, then handler B on each. base is preserved across the first pass
 * (kept for the second) so i spills to the stack there. */
extern void func_ov025_02088064(int ctx, int element);
extern void func_ov025_02087880(int ctx, int element);
void func_ov025_020882ec(int ctx, int base, int count) {
    int i;
    for (i = 0; i < count; i++) {
        func_ov025_02088064(ctx, base + i * 0x58);
    }
    for (i = 0; i < count; i++) {
        func_ov025_02087880(ctx, base + i * 0x58);
    }
}
