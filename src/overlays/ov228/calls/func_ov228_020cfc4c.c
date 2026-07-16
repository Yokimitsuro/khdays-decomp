/* func_ov228_020cfc4c -- the approach tick: age the timer, re-acquire the target, and decide
 * which stance to take based on how far away it is.
 *
 * The timer at +0x4c accumulates (*self)[0x2c] every tick. While the flag at ctx[1]+0xad is set
 * AND the slot at +0x60 is still -1, nothing happens until that timer passes 0x1000 -- a warm-up.
 *
 * func_ov107_020cab14(ctx[0], 0) re-acquires the target and caches it at ctx[0]+0x3bc. No target
 * means reset: zero the timer and (only when the flag is clear) fire mode 1.
 *
 * The range r6 is the squared distance to the target minus the two radii
 * (ctx[0]+0x4a0 plus target+0x80). When ctx[0x15] is not positive the range is handed to
 * func_ov228_020cf150, which decides whether to re-enter at all.
 *
 * Otherwise the stance at +0x5c is rolled:
 *   - closer than 0x1000: a 45% chance of stance 1 (the roll falling through on the other 55%);
 *   - closer than 0x3000: keep an existing stance 2 or 3, else pick between them on a coin flip;
 *   - further:            stance 0.
 * Then 4 is parked in ctx[0]+0x1c7 and the object re-enters with no callback.
 *
 * Written with gotos because the ROM has two shared tails (the stance dispatch and the reset) that
 * several branches jump into; expressing them as nested ifs duplicates the code. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern int func_ov107_020cab14(int owner, int a);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int func_01ff8d18(const VecFx32 *a, const VecFx32 *b);
extern int func_ov228_020cf150(int self, int range);
extern void func_0203c634(int self, int action, void *cb);
extern int func_02023eb4(int n);
extern void func_ov107_020c9264(int owner, int mode, int arg);

void func_ov228_020cfc4c(int self) {
    int *ctx;
    VecFx32 d;
    int range;

    ctx = *(int **)(self + 4);
    ctx[0x13] += *(int *)(*(int *)self + 0x2c);

    if (*(unsigned char *)(ctx[1] + 0xad) != 0 && *(signed char *)((char *)ctx + 0x60) == -1
        && ctx[0x13] < 0x1000) {
        return;
    }

    *(int *)(ctx[0] + 0x3bc) = func_ov107_020cab14(ctx[0], 0);
    if (*(int *)(ctx[0] + 0x3bc) == 0) {
        goto reset;
    }

    VEC_Subtract((const VecFx32 *)(*(int *)(ctx[0] + 0x3bc) + 0x190), (const VecFx32 *)ctx[3],
                 &d);
    /* Split from the subtraction below on purpose: as one expression, mwcc evaluates the ctx[0]
     * operand first and hoists that load above the call into a callee-saved register. */
    range = func_01ff8d18(&d, &d);
    range -= *(int *)(ctx[0] + 0x4a0) + *(int *)(*(int *)(ctx[0] + 0x3bc) + 0x80);

    if (ctx[0x15] <= 0) {
        if (func_ov228_020cf150(self, range) == 0) {
            goto reset;
        }
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (range < 0x1000) {
        if ((unsigned int)func_02023eb4(100) < 0x2d) {
            ctx[0x17] = 1;
            goto dispatch;
        }
    }

    if (range < 0x3000) {
        if (ctx[0x17] != 2 && ctx[0x17] != 3) {
            ctx[0x17] = func_02023eb4(2) != 0 ? 2 : 3;
        }
    } else {
        ctx[0x17] = 0;
    }

dispatch:
    *(unsigned char *)(ctx[0] + 0x1c7) = 4;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
    return;

reset:
    ctx[0x13] = 0;
    if (*(unsigned char *)(ctx[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(ctx[0], 1, 0);
}
