/* func_ov267_020d3058 -- pick a retreat spot: walk the candidate list and take the Nth one that is
 * far enough from the target, then queue move 2 toward it.
 *
 * One of a 3-member shape family; the twins live in ov212/ov266 and are byte-identical modulo
 * relocs (matched here, fanned out with dedupprop).
 *
 * Re-acquires the target into ctx[0]+0x5a8 and measures the gap from ctx[0]+0x508 to the target's
 * +0x190, minus both collision radii. The search only runs when the target is ALREADY close
 * (gap < 0x10000) and there is at least one candidate (ctx[0]+0x604 > 0) -- i.e. this is the
 * "back off" decision, not a general reposition.
 *
 * `best` starts at our own position (ctx[2]), so if nothing qualifies we simply stay put.
 *
 * The walk is deliberately not "nearest": it rolls n = rand(count) up front and then takes every
 * candidate whose gap from the target is >= 0x10000, stopping once it has seen n of them. So it
 * picks a RANDOM far-enough spot rather than the best one -- `best` keeps being overwritten and the
 * last one written wins. Whatever it lands on gets lifted by our radius and pushed through
 * func_ov107_020c5c54.
 *
 * The list at ctx[0]+0x5e4 is iterated with func_01fffd70 / func_01fffd8c, which take ONLY the list
 * pointer: the cursor lives in the list itself at +0x24 (see src/auto/func_01fffd8c.c -- it reads
 * r0[9], advances to node->next, stores it back, and returns the payload at +0xc, or 0 once it
 * wraps to the sentinel). Do not "fix" these into two-arg iterator calls.
 *
 * Every exit converges on the same tail: ctx[0x1a] = 1, queue move 2, dispatch.
 *
 * `gap = f(...) - radii` is left as ONE statement here, unlike func_ov212_020cee18: the `call() -
 * expr` rule means mwcc evaluates the radii sum FIRST, which is exactly what the ROM does (it
 * computes r7 = target_r + own_r before the two calls and keeps it in a callee-saved register).
 * Same rule, opposite conclusion -- read the ROM, do not apply the crack by reflex. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern int func_ov107_020cab14(int obj, int kind);
extern void func_ov107_020c5c54(int obj, const VecFx32 *dst);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern int func_01ff8d18(const VecFx32 *v, VecFx32 *unit);
extern int func_02023eb4();
extern VecFx32 *func_01fffd70(void *list);
extern VecFx32 *func_01fffd8c(void *list);
extern void func_0203c634(int self, int slot, void *cb);

void func_ov267_020d3058(int self) {
    int *ctx;
    VecFx32 v;
    VecFx32 best;
    int radii;
    int n;
    int i;
    VecFx32 *it;

    ctx = *(int **)(self + 4);
    *(int *)(ctx[0] + 0x5a8) = func_ov107_020cab14(ctx[0], 0);
    if (*(int *)(ctx[0] + 0x5a8) != 0) {
        radii = *(int *)(*(int *)(ctx[0] + 0x5a8) + 0x80) + *(int *)(ctx[0] + 0x80);
        VEC_Subtract((const VecFx32 *)(*(int *)(ctx[0] + 0x5a8) + 0x190),
                     (const VecFx32 *)(ctx[0] + 0x508), &v);
        if (func_01ff8d18(&v, &v) - radii < 0x10000 && *(int *)(ctx[0] + 0x604) > 0) {
            n = func_02023eb4(*(int *)(ctx[0] + 0x604));
            best = *(VecFx32 *)ctx[2];
            it = func_01fffd70((void *)(ctx[0] + 0x5e4));
            i = 0;
            while (it != 0) {
                VEC_Subtract((const VecFx32 *)(*(int *)(ctx[0] + 0x5a8) + 0x190), it, &v);
                if (func_01ff8d18(&v, &v) - radii >= 0x10000) {
                    best = *it;
                    if (i >= n) {
                        break;
                    }
                }
                it = func_01fffd8c((void *)(ctx[0] + 0x5e4));
                i++;
            }
            best.y = best.y + *(int *)(ctx[0] + 0x80);
            func_ov107_020c5c54(ctx[0], &best);
        }
    }

    ctx[0x1a] = 1;
    *(signed char *)(ctx[0] + 0x1c7) = 2;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
