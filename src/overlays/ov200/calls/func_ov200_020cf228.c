/* func_ov200_020cf228 -- ov200's move CHOOSER, the steering variant (see func_ov208_020d1be0 for
 * the plain one).
 *
 * A dispatcher reads the queued move at ctx[0]+0x1c7 and runs it; a chooser decides what to queue.
 * This one also STEERS every frame before deciding: it aims a matrix at the target, turns the
 * distance into a Q12 approach factor, and writes a velocity into ctx[3..5].
 *
 * Flow:
 *   no target                    -> queue move 2
 *   gap  = |target - self| minus both collision radii (+0x80 each), floored at 0
 *   fac  = FX_Inv(0x4000 - gap, 0x4000) clamped to [-0x1000, 0x1000]   (1.0 = 0x1000, so this is
 *          "how much of full speed", ramping up as the gap closes below 0x4000)
 *   velocity = the aimed forward vector scaled by -fac, then by 0x280
 *   gap > *(ctx[0]+0x2d8)        -> out of leash: queue move 2
 *   ctx[0]+0x13c == 0x7fffffff   -> no attack window: just drift ctx[4] by +/-0x200 toward the
 *                                   target's height and return
 *   ctx[4] = 0x180
 *   ctx[0]+0x13c <= 0x3800       -> return (window too small)
 *   ctx[0x29] = a coin flip: 1 or -1  (the strafe direction)
 *   ctx[0x20] > 0                -> a d201: 0 queues move 5, anything else dispatches
 *                                   func_ov200_020cf508 as the handler instead of queueing
 *   otherwise                    -> burn one d100 roll, then pick a new ctx[0x20] in
 *                                   [+0x224, +0x224 + |+0x228 - +0x224|], then check three slots
 *                                   via func_ov200_020d055c: all three clear -> move 6; else if the
 *                                   last two are clear -> move 7; else nothing.
 *
 * The discarded `func_02023eb4(0x65)` is real -- the ROM calls it and drops the result, advancing
 * the RNG.
 *
 * `+ (v - v)` on the RNG results is NOT a typo and must not be "simplified": func_02023eb4 returns
 * long long, and that unfoldable zero is what makes mwcc emit the ROM's `add/adds r0, r0, #0`.
 * See deferred-ties.md.
 *
 * Three spellings here look gratuitous and are load-bearing -- do not tidy them:
 *   - `ctx[2] = f(); target = ctx[2];` rather than the other way round, so the store reads the
 *     call's own return register.
 *   - the `!= 0 ? -1 : 1` ternary rather than `== 0 ? 1 : -1`, which fixes the mvnne/moveq order.
 *   - the guards on +0x13c and ctx[0x20] are inverted so their bodies land at the END of the
 *     function, matching the ROM's out-of-line block layout.
 * The two extra locals read from ctx[2]/ctx[0] before the func_01ff8d18 call are also deliberate:
 * the ROM keeps those two base pointers in callee-saved registers across it.
 *
 * FX_Inv is the reloc's own name for 01ff8a04, but it takes two arguments and divides -- it is
 * FX_Div in NitroSDK terms. The name is kept because the symbol table says so.
 */

extern int func_ov107_020cab14(int obj, int kind);
extern void func_0203c634(int self, int slot, void (*cb)(void));
typedef struct { int x, y, z; } Vec3;

extern void func_0203cd7c(int *dst, const Vec3 *a, const Vec3 *b, const void *c);
extern void func_0202ea48(int *dst, const int *src);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *dst);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern int FX_Inv(int num, int den);
extern void func_0202f384(Vec3 *dst, const int *a, const void *b);
extern void func_01ffa724(int scale, const Vec3 *src, int *dst);
extern int func_02023eb4();
extern int func_ov200_020d055c(int slot);
extern void func_ov200_020cf508(void);
extern char data_02042264[];
extern char data_02042258[];

void func_ov200_020cf228(int self) {
    int target;
    int *owner;
    int *ctx;
    int tgt;
    int *own2;
    int gap;
    int fac;
    int base;
    int span;
    int mtx[9];
    Vec3 toTarget;
    Vec3 dir;

    ctx = *(int **)(self + 4);
    owner = (int *)ctx[0];
    ctx[2] = func_ov107_020cab14((int)owner, 0);
    target = ctx[2];
    if (target == 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    func_0203cd7c(mtx, (const Vec3 *)(target + 0x74), (const Vec3 *)ctx[0x13], data_02042264);
    func_0202ea48(&ctx[0x25], mtx);
    VEC_Subtract((const Vec3 *)ctx[0x13], (const Vec3 *)(target + 0x74), &toTarget);
    tgt = ctx[2];
    own2 = (int *)ctx[0];
    gap = func_01ff8d18(&toTarget, &toTarget);
    gap = (gap - *(int *)(tgt + 0x80)) - own2[0x20];
    if (gap < 0) {
        gap = 0;
    }
    fac = FX_Inv(0x4000 - gap, 0x4000);
    if (fac < -0x1000) {
        fac = -0x1000;
    }
    if (fac > 0x1000) {
        fac = 0x1000;
    }
    func_0202f384(&dir, &ctx[0x25], data_02042258);
    func_01ffa724(-fac, &dir, &ctx[3]);
    func_01ffa724(0x280, (const Vec3 *)&ctx[3], &ctx[3]);

    if (gap > *(int *)(ctx[0] + 0x2d8)) {
        *(signed char *)(ctx[0] + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (owner[0x4f] != 0x7fffffff) {
        ctx[4] = 0x180;
        if (owner[0x4f] <= 0x3800) {
            return;
        }

        ctx[0x29] = (func_02023eb4(2) + (gap - gap) != 0) ? -1 : 1;

        if (ctx[0x20] <= 0) {
            func_02023eb4(0x65);
            base = *(int *)(ctx[0] + 0x224);
            span = *(int *)(ctx[0] + 0x228) - base;
            if (span < 0) {
                span = -span;
            }
            ctx[0x20] = base + func_02023eb4(span + 1);

            if (func_ov200_020d055c(*(int *)(ctx[0] + 0x390))
                && func_ov200_020d055c(*(int *)(ctx[0] + 0x394))
                && func_ov200_020d055c(*(int *)(ctx[0] + 0x398))) {
                *(signed char *)(ctx[0] + 0x1c7) = 6;
                func_0203c634(self, *(signed char *)(self + 0x20), 0);
                return;
            }
            if (!func_ov200_020d055c(*(int *)(ctx[0] + 0x394))) {
                return;
            }
            if (!func_ov200_020d055c(*(int *)(ctx[0] + 0x398))) {
                return;
            }
            *(signed char *)(ctx[0] + 0x1c7) = 7;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }

        if (func_02023eb4(0xc9) + (gap - gap) == 0) {
            *(signed char *)(ctx[0] + 0x1c7) = 5;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
        func_0203c634(self, *(signed char *)(self + 0x20), func_ov200_020cf508);
        return;
    }

    if (*(int *)(target + 0x78) < *(int *)(ctx[0x13] + 4)) {
        ctx[4] -= 0x200;
    } else {
        ctx[4] += 0x200;
    }
}
