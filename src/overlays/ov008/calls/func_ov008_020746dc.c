/* Show/hide two slot groups based on the scroll extent (0x60 - field 0x164) and the drag delta
 * param_2: group 0x40 visible while scrolling right (delta > 0), group 0x41 visible while there is
 * still room to scroll (delta < extent). */
extern int func_ov008_02050c64(void);
extern int func_ov008_02054788(int ctx, int id);
extern void func_ov008_02054ba4(int ctx, int entry, int visible);

void func_ov008_020746dc(int param_1, int param_2) {
    int ctx = func_ov008_02050c64();
    int extent = 0x60 - *(int *)(param_1 + 0x164);
    int vis1 = 0;
    int vis2 = 0;
    int entry;
    if (extent > 0 && param_2 > 0) {
        vis1 = 1;
    }
    if (extent > 0 && param_2 < extent) {
        vis2 = 1;
    }
    entry = func_ov008_02054788(ctx, 0x40);
    func_ov008_02054ba4(ctx, entry, vis1);
    entry = func_ov008_02054788(ctx, 0x41);
    func_ov008_02054ba4(ctx, entry, vis2);
}
