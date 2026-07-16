/* func_ov158_020cd174 -- fire the owner's reaction once the target is within half its reach.
 * func_ov107_020cab14 hands back the target and the SQUARED separation, so the gap is the square
 * root of that less both bodies' radii (+0x80 each). With no target the gap is pinned to INT_MAX,
 * which can still fire -- see below.
 * The reaction is skipped only when the gap is at or beyond half the owner's reach (+0x2d8) AND
 * the counter at +0x44 is still positive; once that counter runs out the reaction fires at any
 * range. Firing parks the owner in state 4 (+0x1c7) and dispatches through func_0203c634 with the
 * action id from the caller's +0x20.
 *
 * NONMATCHING: 140/140 bytes, every instruction in the right place. Only r6/r7 are swapped:
 * the ROM gives the target r7 and the owner r6, mwcc gives the first-assigned callee-saved value
 * r6 and the second r7 -- it allocates ascending where the ROM went descending. Carries through
 * to the two radius loads and one `str r0` vs `str r6`.
 *
 * ⚠ This BLOCKS a 4-member family (ov158/159/246/247) -- dedupprop will not propagate from a
 * nonmatching rep -- so it is worth another attempt with fresh eyes.
 * Tried and rejected:
 *   decl order gap/owner/target and gap/target/owner  -> identical, so it is first-use driven,
 *     not decl-order driven (consistent with the deferred-ties note: decl order is inert here).
 *   dropping the `target` local and using ctx[2] directly -> mwcc reloads it, 156 B (+16).
 * The `owner` local IS load-bearing and must stay: without it mwcc reloads ctx[0] after FX_Sqrt
 * instead of caching it across the call, which costs a callee-saved register, and the frame then
 * needs an explicit `sub sp,#4` instead of reusing the pushed r3 slot (144 B). */
extern int func_ov107_020cab14(int owner, int *distSq);
extern int FX_Sqrt(int x);
extern void func_0203c634(int self, int action, int arg);

void func_ov158_020cd174(int self) {
    int *ctx;
    int gap;
    int target;
    int owner;

    ctx = *(int **)(self + 4);
    target = func_ov107_020cab14(ctx[0], &gap);
    ctx[2] = target;
    if (target == 0) {
        gap = 0x7fffffff;
    } else {
        owner = ctx[0];
        gap = FX_Sqrt(gap) - *(int *)(target + 0x80) - *(int *)(owner + 0x80);
    }

    if (gap >= *(int *)(ctx[0] + 0x2d8) / 2 && ctx[0x11] > 0) {
        return;
    }
    *(unsigned char *)(ctx[0] + 0x1c7) = 4;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
