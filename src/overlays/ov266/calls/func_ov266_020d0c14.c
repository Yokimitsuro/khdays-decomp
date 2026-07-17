/* func_ov266_020d0c14 -- the idle/approach tick: run the think timer down, re-acquire the target,
 * and either let the chooser (func_ov266_020cfb00) queue a move or fall back to the idle anim.
 *
 * One of a 3-member shape family; the twins live in ov212/ov267 and are byte-identical modulo
 * relocs (matched here, fanned out with dedupprop).
 *
 * A reactive opening short-circuits everything: if func_ov266_020cf42c(ctx, 1) fires straight away
 * it queues move 4 with a coin-flip stance in ctx[0x18] and dispatches, without even ticking the
 * timer.
 *
 * Otherwise the timer at ctx[0x13] runs down by the frame delta and clamps at 0, the busy byte at
 * *(ctx[1] + 0xad) gates everything else, and then -- only if either opening test still reports
 * true -- the target is re-acquired into ctx[0]+0x5a8. The distance is measured from ctx[0]+0x508
 * (not the usual +0x74 position) to the target's +0x190, minus both collision radii, and handed to
 * the chooser as `dist`. If the chooser queued something, dispatch it.
 *
 * If it did not, move 4 still goes out when the gap is OUTSIDE the 0x3000..0x9800 band -- too close
 * or too far -- or when func_ov266_020cffbc says so. Only a target sitting comfortably in the band
 * with nothing else to say gets the idle anim instead. (The band test reads backwards from the
 * ROM's branches until you resolve them: the `bgt`/`blt` jump INTO the move-4 block, not past it.)
 *
 * Every other path falls into the same tail: kick anim 4 via func_ov107_020c9264 and stay put.
 *
 * `+ (gap - gap)` is NOT a typo and must not be "cleaned up": func_02023eb4 returns long long, and
 * that addend is what makes mwcc emit the ROM's `add r0, r0, #0` copy after the call. `gap` is
 * uninitialised there, which is fine -- the expression is dead by construction and only exists to
 * stop the addend folding away. See deferred-ties.md. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern int func_ov266_020cf42c(int *ctx, int a);
extern int func_ov266_020cf3fc(int *ctx, int a);
extern int func_ov266_020cffbc(int self);
extern int func_ov266_020cfb00(int self, int dist);
extern int func_ov107_020cab14(int obj, int kind);
extern void func_ov107_020c9264(int obj, int anim, int flag);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern int func_01ff8d18(const VecFx32 *v, VecFx32 *unit);
extern int func_02023eb4();
extern void func_0203c634(int self, int slot, void *cb);

void func_ov266_020d0c14(int self) {
    int *ctx;
    VecFx32 v;
    int gap;

    ctx = *(int **)(self + 4);
    if (func_ov266_020cf42c(ctx, 1) != 0) {
        ctx[0x18] = func_02023eb4(2) + (gap - gap);
        *(signed char *)(ctx[0] + 0x1c7) = 4;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    ctx[0x13] -= *(int *)(*(int *)self + 0x2c);
    if (ctx[0x13] <= 0) {
        ctx[0x13] = 0;
    }
    if (*(unsigned char *)(ctx[1] + 0xad) != 0) {
        return;
    }

    if (func_ov266_020cf3fc(ctx, 1) != 0 || func_ov266_020cf42c(ctx, 1) != 0) {
        *(int *)(ctx[0] + 0x5a8) = func_ov107_020cab14(ctx[0], 0);
        if (*(int *)(ctx[0] + 0x5a8) != 0) {
            VEC_Subtract((const VecFx32 *)(*(int *)(ctx[0] + 0x5a8) + 0x190),
                         (const VecFx32 *)(ctx[0] + 0x508), &v);
            /* Two statements, not one: `f() - expr` makes mwcc evaluate the non-call operand
             * FIRST, which hoists the ctx[0] load above the call and parks it in a callee-saved
             * register. The ROM re-reads ctx[0] after the call. See codegen-cracks.md. */
            gap = func_01ff8d18(&v, &v);
            gap = gap - *(int *)(*(int *)(ctx[0] + 0x5a8) + 0x80) - *(int *)(ctx[0] + 0x80);
            if (func_ov266_020cfb00(self, gap) != 0) {
                func_0203c634(self, *(signed char *)(self + 0x20), 0);
                return;
            }
            if (gap > 0x9800 || gap < 0x3000 || func_ov266_020cffbc(self) != 0) {
                *(signed char *)(ctx[0] + 0x1c7) = 4;
                func_0203c634(self, *(signed char *)(self + 0x20), 0);
                return;
            }
        }
    }
    func_ov107_020c9264(ctx[0], 4, 0);
}
