/* func_ov246_020d0d80 -- fire the owner's reaction once the target is within half its reach.
 * func_ov107_020cab14 hands back the target and the SQUARED separation, so the gap is the square
 * root of that less both bodies' radii (+0x80 each). With no target the gap is pinned to INT_MAX,
 * which can still fire -- see below.
 * The reaction is skipped only when the gap is at or beyond half the owner's reach (+0x2d8) AND
 * the counter at +0x44 is still positive; once that counter runs out the reaction fires at any
 * range. Firing parks the owner in state 4 (+0x1c7) and dispatches through func_0203c634 with the
 * action id from the caller's +0x20.
 *
 *
 * Two things closed it, and the note's "mwcc allocates ascending where the ROM went descending"
 * was a symptom of the first. The ROM stores the acquire result straight out of r0 and keeps the
 * flag-setting copy in r7, which `target = acquire(...); ctx[2] = target;` cannot produce -- write
 * the STORE first and bind the local from the slot (`ctx[2] = acquire(...); target = ctx[2];`).
 * mwcc forwards the value, so there is no reload and no size cost. With that in place the r6/r7
 * pair between `target` and `owner` is pure declaration order, and tools/declperm.py finds it:
 * 12 of the 24 orders match, all of them with `target` declared after `owner`.
 */

extern int func_ov107_020cab14(int owner, int *distSq);
extern int FX_Sqrt(int x);
extern void func_0203c634(int self, int action, int arg);

void func_ov246_020d0d80(int self) {
    int *ctx;
    int gap;
    int owner;
    int target;

    ctx = *(int **)(self + 4);
    ctx[2] = func_ov107_020cab14(ctx[0], &gap);
    target = ctx[2];
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
