/* func_ov211_020d2b44 -- ov211's move CHOOSER, the plain (non-steering) shape.
 *
 * Byte-identical to func_ov210_020d0d24 modulo this overlay's own symbols; that is the rep
 * and carries the analysis.
 *
 * A dispatcher reads the queued move at ctx[0]+0x1c7 and runs it; a chooser decides what to queue.
 * func_ov107_020cab14 returns the target and writes the SQUARED distance through its out-param,
 * hence the FX_Sqrt; `d` is that one slot reused, squared distance then real gap.
 *
 * Unlike the other choosers, no target means it simply RETURNS -- it queues nothing at all.
 *
 * ctx[0x1b] < 1 selects a passive ruleset:
 *   d > 0x1000   -> move 5 (close the distance)
 *   otherwise    -> a d100: <= 70 move 15, else move 5
 *
 * Otherwise, by range:
 *   d >= 0x8000  -> move 10
 *   d < 0x3000   -> a d100 == 0 -> move 9; else a second d100 >= 20 -> nothing;
 *                   else a third d100 < 50 -> move 13, else move 12
 *   in between   -> one d100 fans out: <40 move 10, <60 move 13, <80 move 12, <99 move 11,
 *                   else move 9
 *
 * `+ (v - v)` on every RNG result is NOT a typo and must not be "simplified": func_02023eb4 returns
 * long long, and that unfoldable zero is what makes mwcc emit the ROM's `add/adds r0, r0, #0`.
 * See deferred-ties.md.
 *
 * The comparison constants are the ROM's own: `<= 0x46` rather than the equivalent `< 0x47`, and
 * `>= 0x14` rather than `> 0x13` -- the other spelling flips the branch.
 */

extern int func_ov107_020cab14(int obj, int *outDistSq);
extern void func_0203c634(int self, int slot, void (*cb)(void));
extern int FX_Sqrt(int x);
extern int func_02023eb4();

void func_ov211_020d2b44(int self) {
    int *ctx;
    int *owner;
    int target;
    int d;
    int roll;

    ctx = *(int **)(self + 4);
    ctx[4] = func_ov107_020cab14(ctx[0], &d);
    target = ctx[4];
    if (target == 0) {
        return;
    }

    owner = (int *)ctx[0];
    d = FX_Sqrt(d) - (owner[0x20] + *(int *)(target + 0x80));

    if (ctx[0x1b] <= 0) {
        if (d <= 0x1000) {
            if (func_02023eb4(0x65) + (d - d) <= 0x46) {
                *(signed char *)(ctx[0] + 0x1c7) = 15;
                func_0203c634(self, *(signed char *)(self + 0x20), 0);
                return;
            }
            *(signed char *)(ctx[0] + 0x1c7) = 5;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
        *(signed char *)(ctx[0] + 0x1c7) = 5;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (d >= 0x8000) {
        *(signed char *)(ctx[0] + 0x1c7) = 10;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (d >= 0x3000) {
        roll = func_02023eb4(0x65) + (d - d);
        if (roll < 0x28) {
            *(signed char *)(ctx[0] + 0x1c7) = 10;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
        if (roll < 0x3c) {
            *(signed char *)(ctx[0] + 0x1c7) = 13;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
        if (roll < 0x50) {
            *(signed char *)(ctx[0] + 0x1c7) = 12;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
        if (roll < 99) {
            *(signed char *)(ctx[0] + 0x1c7) = 11;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
        *(signed char *)(ctx[0] + 0x1c7) = 9;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (func_02023eb4(0x65) + (d - d) == 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 9;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    if (func_02023eb4(0x65) + (d - d) >= 0x14) {
        return;
    }
    if (func_02023eb4(0x65) + (d - d) < 0x32) {
        *(signed char *)(ctx[0] + 0x1c7) = 13;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    *(signed char *)(ctx[0] + 0x1c7) = 12;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
    return;
}
