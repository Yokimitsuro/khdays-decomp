/* func_ov235_020cd994 -- ov235's move CHOOSER (family rep: func_ov208_020d1be0).
 *
 * A dispatcher reads the queued move at ctx[0]+0x1c7 and runs it; this decides what to queue there.
 * Every exit writes +0x1c7 and calls func_0203c634 with a NULL handler, i.e. "run what is queued".
 *
 * This one is richer than ov208's: it has a hard early-out ladder before it ever rolls dice, and
 * two entirely separate decisions depending on the sign of ctx[0x13].
 *
 * The ladder, in order:
 *   no target                  -> nothing queued at all (the only exit that does not dispatch)
 *   ctx[0x22] set, and         -> move 11.  The two shorts at owner+0x218/+0x21a are a pair fed to
 *     f_02020400(a<<12, b)        func_02020400 with the first shifted into Q12; <= 0x4cc queues it.
 *       <= 0x4cc
 *   ctx[0x14] >= 0x1e000       -> move 12
 *
 * Then the split on ctx[0x13]:
 *
 *   ctx[0x13] <= 0 -- the ordinary engagement decision:
 *     |owner[0xb4] - target[0x78]| > 0x1800 -> move 12   (a height/level mismatch: break off)
 *     else if gap > 0x6000 -> d100: <30 move 12, <60 move 4, else move 9
 *     else                 -> if the anchor is near (< 0x8000) and we are facing it
 *                             (dot > 0x400) -> move 9, else d100: <70 move 8, else move 9
 *
 *   ctx[0x13] > 0 -- an anchor-relative decision instead. Both the target and the owner are
 *     measured as unit directions FROM the fixed point data_02041dc8, flattened to the XZ plane,
 *     and dotted together: that is "are we and the target on the same side of the anchor".
 *     far (gap >= 0x8000) or on opposite sides (dot < -0x400) -> move 4
 *     else if gap > 0x2000 -> nothing
 *     else a 1-in-100 roll gates a uniform pick of move 5 / 6 / 7.
 *
 * `gap` is the distance between the two collision radii at +0x80, as in ov208.
 * Every direction vector here is flattened (`[1] = 0`) before normalising, so the whole decision
 * is made in the ground plane -- height only ever enters via the +0xb4/+0x78 comparison above.
 *
 * ctx[0x10] takes `*(int *)(*(int *)self + 0x2c) * 30 / 15`; mwcc cannot fold the two constants
 * (the multiply may overflow), so both stay. See func_ov208_020d1be0.
 *
 * `+ (gap - gap)` is NOT a typo and must not be "cleaned up": func_02023eb4 returns long long, and
 * that addend is what makes mwcc emit the ROM's `add r0, r0, #0` / `adds r0, r0, #0` copy after the
 * call. See deferred-ties.md.
 *
 * Four spellings below are load-bearing -- each was a diff before it was a match, so do not tidy:
 *  - Declaration order `owner, target, ctx` assigns the callee-saved trio r4/r5/r6. Declaring ctx
 *    first (the obvious order) allocates it r4 and permutes every register in the function.
 *  - `owner = (int *)ctx[0];` must sit BEFORE the ctx[0x10] division. Only then does the scheduler
 *    slot its load into the smull latency shadow and home the quotient in r7; with it after, the
 *    quotient lands in a caller-saved reg and 12 instructions permute.
 *  - `ctx[0x17] = f(...); target = ctx[0x17];` (not `target = f(...); ctx[0x17] = target;`) is what
 *    stores the call result itself -- the ROM's `str r0`, not `str r5`. mwcc forwards the store to
 *    the read, so the reload costs nothing.
 *  - `node` is a snapshot of ctx[0] taken BEFORE func_02020400 and reused for the +0x1c7 store
 *    after it, which is why the ROM keeps it in callee-saved r8. Spelling both as a plain `ctx[0]`
 *    expression forces a reload across the call and costs an instruction (this is the one that set
 *    the size to 928). Note this is a SECOND local holding ctx[0] alongside `owner`: `owner` is a
 *    snapshot taken earlier, so the two are not interchangeable to the compiler. */

extern int func_ov107_020cab14(int obj, int kind);
extern void VEC_Subtract(const int *a, const int *b, int *dst);
extern int func_020050b4(int x, int z);
extern void func_0202f188(int *dst, const int *a, int angle);
extern int func_01ff8d18(const int *v, int *unit);
extern int func_02020400(int a, int b);
extern void func_0203c634(int self, int slot, void (*cb)(void));
extern int func_02023eb4();
extern void func_0202f384(int *dst, const int *a, const int *b);
extern int VEC_DotProduct(const int *a, const int *b);
extern int data_02041dc8[];
extern int data_02042258[];
extern int data_02042264[];

void func_ov235_020cd994(int self) {
    int *owner;
    int target;
    int *ctx;
    int toTarget[3];
    int targetDir[3];
    int ownerDir[3];
    int anchorDir[3];
    int forward[3];
    int gap;
    int node;
    int roll;
    int dot;

    ctx = *(int **)(self + 4);
    ctx[0x17] = func_ov107_020cab14(ctx[0], 0);
    target = ctx[0x17];
    if (target == 0) {
        return;
    }

    owner = (int *)ctx[0];
    ctx[0x10] = *(int *)(*(int *)self + 0x2c) * 30 / 15;
    VEC_Subtract((const int *)(target + 0x74), (const int *)((int)owner + 0x74), toTarget);
    func_0202f188(&ctx[0xb], data_02042264, func_020050b4(toTarget[0], toTarget[2]));
    gap = func_01ff8d18(toTarget, toTarget) - owner[0x20] - *(int *)(target + 0x80);

    if (ctx[0x22] != 0) {
        node = ctx[0];
        if (func_02020400(*(short *)(node + 0x21a) << 12, *(short *)(node + 0x218)) <= 0x4cc) {
            *(signed char *)(node + 0x1c7) = 11;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
    }

    if (ctx[0x14] >= 0x1e000) {
        *(signed char *)(ctx[0] + 0x1c7) = 12;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (ctx[0x13] <= 0) {
        dot = *(int *)(ctx[0] + 0xb4) - *(int *)(target + 0x78);
        if (dot < 0) {
            dot = -dot;
        }
        if (dot > 0x1800) {
            *(signed char *)(ctx[0] + 0x1c7) = 12;
        } else if (gap > 0x6000) {
            roll = func_02023eb4(0x65) + (gap - gap);
            if (roll < 0x1e) {
                *(signed char *)(ctx[0] + 0x1c7) = 12;
            } else if (roll < 0x3c) {
                *(signed char *)(ctx[0] + 0x1c7) = 4;
            } else {
                *(signed char *)(ctx[0] + 0x1c7) = 9;
            }
        } else {
            VEC_Subtract(data_02041dc8, (const int *)ctx[1], anchorDir);
            anchorDir[1] = 0;
            if (func_01ff8d18(anchorDir, anchorDir) < 0x8000) {
                func_0202f384(forward, &ctx[7], data_02042258);
                if (VEC_DotProduct(forward, anchorDir) > 0x400) {
                    *(signed char *)(ctx[0] + 0x1c7) = 9;
                    func_0203c634(self, *(signed char *)(self + 0x20), 0);
                    return;
                }
            }
            roll = func_02023eb4(0x65) + (gap - gap);
            if (roll < 0x46) {
                *(signed char *)(ctx[0] + 0x1c7) = 8;
            } else {
                *(signed char *)(ctx[0] + 0x1c7) = 9;
            }
        }
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    VEC_Subtract(data_02041dc8, (const int *)(target + 0x74), targetDir);
    targetDir[1] = 0;
    func_01ff8d18(targetDir, targetDir);
    VEC_Subtract(data_02041dc8, (const int *)((int)owner + 0x74), ownerDir);
    ownerDir[1] = 0;
    func_01ff8d18(ownerDir, ownerDir);
    dot = VEC_DotProduct(targetDir, ownerDir);
    if (gap >= 0x8000 || dot < -0x400) {
        *(signed char *)(ctx[0] + 0x1c7) = 4;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    if (gap > 0x2000) {
        return;
    }
    if (func_02023eb4(0x65) + (gap - gap) != 0) {
        return;
    }
    roll = func_02023eb4(3) + (gap - gap);
    if (roll == 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 5;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    if (roll == 1) {
        *(signed char *)(ctx[0] + 0x1c7) = 6;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    if (roll == 2) {
        *(signed char *)(ctx[0] + 0x1c7) = 7;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
    }
}
