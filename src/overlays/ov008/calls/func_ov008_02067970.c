/*
 * func_ov008_02067970 -- x3 (ov008/...). Place a UI element at a preset X offset by variant.
 * Pick the X offset from `variant` (1 -> 0x50000, 2 -> 0x74000, else 0x2c000). Allocate a 0x10-slot
 * via 02054788, resolve its record with 0205489c, and hand 02054858 a position {*record + 0x8000, X}.
 */
extern int func_ov008_02050c28(void);
extern int func_ov008_02050c54(void);
extern int func_ov008_02054788(int ctx, int size);
extern int *func_ov008_0205489c(int ctx, int slot);
extern void func_ov008_02054858(int ctx, int slot, int *pos);

void func_ov008_02067970(int a, int b, int variant) {
    int ctx;
    int slot;
    int *record;
    int x;
    int pos[2];

    func_ov008_02050c28();
    ctx = func_ov008_02050c54();
    if (variant != 0) {
        if (variant == 1) { x = 0x50000; goto have_x; }
        if (variant == 2) { x = 0x74000; goto have_x; }
    }
    x = 0x2c000;
have_x:
    slot = func_ov008_02054788(ctx, 0x10);
    record = func_ov008_0205489c(ctx, slot);
    pos[0] = *record + 0x8000;
    pos[1] = x;
    func_ov008_02054858(ctx, slot, pos);
}
