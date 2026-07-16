/* NOT MATCHING -- proven compiler tie, not unfinished work. 568/576 bytes.
 *
 * Everything matches except TWO instructions: the ROM emits a no-op `add r0, r0, #0` immediately
 * after each `bl func_02023eb4` (the RNG), and no C spelling reproduces it. Tried: a plain
 * `extern int` return (how ov114's matched callers declare it), `long long` + `(int)` cast, a
 * `long long` temporary then a cast, `+ 0` on the result, `unsigned long long`, and a
 * `static` helper -- all 568, i.e. all miss exactly those 8 bytes.
 *
 * The evidence that it is the compiler and not this file: across the whole ROM 54 functions have a
 * rand call followed by that `add`, and NOT ONE is implemented in real C anywhere in the project --
 * the ones that "match" are all asm_stubs (ASM blobs verify trivially). Meanwhile the same call
 * WITHOUT the artifact matches from C 564 times. So the artifact tracks the compiler build, not the
 * source: consistent with retail being mwcc 3.0 >=140 (see reference_mwcc_build_hunt). This tie
 * blocks 54 functions, so it is worth revisiting if the exact build is ever found.
 *
 * One further known-good delta, invisible in the byte count: the ROM hoists the `ctx[0]` and
 * `ctx[4]` loads above the `func_01ff8d18` call and keeps them in callee-saved registers (which is
 * why the ROM holds `self` in r7 where this holds it in r6). Scheduling only -- the two `add`s are
 * the real blocker.
 *
 * The C below is believed semantically correct and is kept for the PC port.
 */

/* func_ov206_020cde58 -- ov206's move CHOOSER.
 *
 * The counterpart of a move dispatcher: a dispatcher reads the queued move at ctx[0]+0x1c7 and runs
 * it, while this decides what to queue there. Every exit writes +0x1c7 and then calls
 * func_0203c634 with a NULL handler, i.e. "run whatever is queued now".
 *
 * With no target it queues move 2. Otherwise it takes the vector to the target, normalises it (that
 * call returns the length, so `gap` is the distance minus the two collision radii at +0x80), records
 * the facing angle, builds the unit forward vector, and -- unless the busy byte at *(u8 *)ctx[3] is
 * set -- rolls a d100:
 *
 *   roll < 20        -> move 10
 *   roll < 40        -> move 5
 *   otherwise, close (gap < 0x4000): move 6 only if the target is roughly ahead, else nothing
 *              far  (gap >= 0x4000): roughly ahead -> move 5
 *                                    otherwise     -> a second d100: <50 move 10, else move 9
 *
 * "Roughly ahead" is VEC_DotProduct(toTarget, forward) > 0x200 -- both are unit vectors and Q12's
 * 1.0 is 0x1000, so that is a wide ~82-degree cone, not a narrow aim check.
 *
 * ctx[0xf] takes `*(int *)(*(int *)self + 0x2c) * 30 / 30`. The two 30s cancel at runtime and mwcc
 * does not fold them (the multiply can overflow), so the ROM really does multiply and then divide by
 * a constant -- a unit conversion whose two rates happen to be equal. */

extern int func_ov107_020cab14(int obj, int kind);
extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void VEC_Subtract(const int *a, const int *b, int *dst);
extern int VEC_DotProduct(const int *a, const int *b);
extern int func_01ff8d18(const int *v, int *unit);
extern int func_020050b4(int x, int z);
extern int func_ov107_020c9f48(int a, int *out);
extern void func_0202f384(int *dst, const int *a, const int *b);
extern void func_01ffa724(int scale, const int *src, int *dst);
extern long long func_02023eb4(unsigned int mul);

void func_ov206_020cde58(int self) {
    int *ctx;
    int toTarget[3];
    int forward[3];
    int target;
    int gap;
    int scale;
    int roll;

    ctx = *(int **)(self + 4);
    target = func_ov107_020cab14(ctx[0], 0);
    ctx[4] = target;
    if (target == 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    VEC_Subtract((const int *)(target + 0x190), (const int *)ctx[1], toTarget);
    gap = func_01ff8d18(toTarget, toTarget);
    ctx[0xf] = *(int *)(*(int *)self + 0x2c) * 30 / 30;
    gap -= *(int *)(ctx[0] + 0x80) + *(int *)(ctx[4] + 0x80);
    ctx[0x11] = func_020050b4(toTarget[0], toTarget[2]);

    scale = func_ov107_020c9f48(*(int *)(ctx[0] + 0x3b4), forward);
    func_0202f384(&ctx[5], (const int *)(ctx[0] + 0xa0), forward);
    func_01ffa724(scale, &ctx[5], &ctx[5]);
    func_01ff8d18(&ctx[5], forward);

    if (*(unsigned char *)ctx[3] != 0) {
        return;
    }

    roll = (int)func_02023eb4(0x65);
    if (roll < 0x14) {
        *(signed char *)(ctx[0] + 0x1c7) = 10;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    if (roll < 0x28) {
        *(signed char *)(ctx[0] + 0x1c7) = 5;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (gap < 0x4000) {
        if (VEC_DotProduct(toTarget, forward) > 0x200) {
            *(signed char *)(ctx[0] + 0x1c7) = 6;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
        }
        return;
    }

    if (VEC_DotProduct(toTarget, forward) > 0x200) {
        *(signed char *)(ctx[0] + 0x1c7) = 5;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if ((int)func_02023eb4(0x65) < 0x32) {
        *(signed char *)(ctx[0] + 0x1c7) = 10;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    *(signed char *)(ctx[0] + 0x1c7) = 9;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
