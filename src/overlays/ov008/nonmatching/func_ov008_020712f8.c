/* Show/hide two slot groups from the object's scroll window (+0x20 within +0x28): the left/right
 * group id depends on which context object is active (0x3f vs 0x3d); the left group is visible
 * while position > 0, the 0x3e group while position < span.
 *
 * NON-MATCHING (equivalent), size-exact. Only the callee-saved register assignment differs: the
 * ROM puts id1 in r7, vis1 in r5, vis2 in r6, while mwcc 139 picks r6/r7/r5 for the same three
 * values (propagating through every mov to the call arguments). The matched sibling
 * func_ov008_020746dc has the identical visibility shape but no id-select variable, so it colours
 * cleanly; adding the id1 ternary here perturbs the allocation. Tried declaration reordering and
 * the comma-form; the allocator does not land on the ROM's colouring. */
extern int func_ov008_02051028(void);
extern int func_ov008_02050c64(void);
extern int func_ov008_02054788(int ctx, int id);
extern void func_ov008_02054ba4(int ctx, int entry, int visible);

void func_ov008_020712f8(int param_1) {
    int id1 = func_ov008_02051028() != 0 ? 0x3f : 0x3d;
    unsigned int vis1 = 0;
    int vis2 = 0;
    int ctx, entry;
    if (*(int *)(param_1 + 0x28) > 0 &&
        (vis1 = *(int *)(param_1 + 0x20) > 0, *(int *)(param_1 + 0x20) < *(int *)(param_1 + 0x28))) {
        vis2 = 1;
    }
    ctx = func_ov008_02050c64();
    entry = func_ov008_02054788(ctx, id1);
    func_ov008_02054ba4(ctx, entry, vis1);
    entry = func_ov008_02054788(ctx, 0x3e);
    func_ov008_02054ba4(ctx, entry, vis2);
}
