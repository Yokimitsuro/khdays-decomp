/*
 * func_ov025_02099d50 -- x3 (ov008/...). Place a UI element at a preset X offset by variant.
 * Pick the X offset from `variant` (1 -> 0x50000, 2 -> 0x74000, 0/else -> 0x2c000). Allocate a
 * 0x10-slot via 02054788, resolve its record with 0205489c, and hand 02054858 a position
 * {*record + 0x8000, X}.
 *
 * The switch lists `case 0: default:` first (sharing the 0x2c000 block) so mwcc lays that block
 * immediately after the compare chain -- both the `beq #0` and the fall-through land on it with no
 * extra branch, matching the ROM.
 */
extern int func_ov025_02084a50(void);
extern int func_ov025_02084a7c(void);
extern int func_ov025_0208843c(int ctx, int size);
extern int *func_ov025_02088544(int ctx, int slot);
extern void func_ov025_02088500(int ctx, int slot, int *pos);

void func_ov025_02099d50(int a, int b, int variant) {
    int ctx, slot, *record, x, pos[2];

    func_ov025_02084a50();
    ctx = func_ov025_02084a7c();
    switch (variant) {
    case 0:
    default: x = 0x2c000; break;
    case 1:  x = 0x50000; break;
    case 2:  x = 0x74000; break;
    }
    slot = func_ov025_0208843c(ctx, 0x10);
    record = func_ov025_02088544(ctx, slot);
    pos[0] = *record + 0x8000;
    pos[1] = x;
    func_ov025_02088500(ctx, slot, pos);
}
