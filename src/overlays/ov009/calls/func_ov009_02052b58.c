/*
 * func_ov009_02052b58 -- x3 (ov008/...). Place a UI element at a preset X offset by variant.
 * Pick the X offset from `variant` (1 -> 0x50000, 2 -> 0x74000, 0/else -> 0x2c000). Allocate a
 * 0x10-slot via 02054788, resolve its record with 0205489c, and hand 02054858 a position
 * {*record + 0x8000, X}.
 *
 * The switch lists `case 0: default:` first (sharing the 0x2c000 block) so mwcc lays that block
 * immediately after the compare chain -- both the `beq #0` and the fall-through land on it with no
 * extra branch, matching the ROM.
 */
extern int func_ov009_0204e42c(void);
extern int func_ov009_0204e440(void);
extern int func_ov009_020518fc(int ctx, int size);
extern int *func_ov009_020519f4(int ctx, int slot);
extern void func_ov009_020519b0(int ctx, int slot, int *pos);

void func_ov009_02052b58(int a, int b, int variant) {
    int ctx, slot, *record, x, pos[2];

    func_ov009_0204e42c();
    ctx = func_ov009_0204e440();
    switch (variant) {
    case 0:
    default: x = 0x2c000; break;
    case 1:  x = 0x50000; break;
    case 2:  x = 0x74000; break;
    }
    slot = func_ov009_020518fc(ctx, 0x10);
    record = func_ov009_020519f4(ctx, slot);
    pos[0] = *record + 0x8000;
    pos[1] = x;
    func_ov009_020519b0(ctx, slot, pos);
}
