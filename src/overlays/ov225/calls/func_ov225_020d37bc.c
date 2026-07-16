/* func_ov225_020d37bc -- enter the approach: pick a lane, a speed and a duration, then dispatch.
 * A negative reading from func_ov225_020d127c aborts straight to the dispatcher.
 *
 * There is a 50/50 coin flip (+0x7c). On heads the target point (+0x54) is jittered off the base
 * (+0x58) by a SYMMETRIC random offset: rand(6435) - 3217, i.e. +/-3217 inclusive (6435 = 2*3217+1).
 * On tails it just copies the plain value (+0x50).
 *
 * The speed at +0x70 is `v / 3072 * 136` -- quantised into steps of 136 -- then clamped to
 * [0xc00, 0x1800]. It is stored BOTH before and after the clamp; that is what the ROM does.
 * The duration at +0x34 is then `(v * 2) / (speed / 136)`, i.e. divided by the step count, and
 * skipped entirely when that count is zero (guarding the division).
 *
 * The divisors are read off the magic shifts: asr #9 with 0x2aaaaaab is /3072, asr #6 with
 * 0x78787879 is /136. Kept unfolded -- the intermediates can overflow. */
extern int func_ov225_020d127c(int self, int kind);
extern void func_0203c634(int self, int action, void (*cb)(void));
extern int func_02023eb4(int n);
extern int func_02020400(int a, int b);
extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_ov225_020d3900(void);

void func_ov225_020d37bc(int self) {
    int *ctx;
    int v;
    int speed;
    int steps;

    ctx = *(int **)(self + 4);
    v = func_ov225_020d127c(self, 0);
    if (v < 0) {
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    ctx[0x1f] = 0;
    ctx[0x15] = ctx[0x14];
    ctx[0x1f] = (unsigned int)func_02023eb4(100) < 0x32;
    if (ctx[0x1f] != 0) {
        ctx[0x15] = ctx[0x16] + (func_02023eb4(6435) - 0xc91);
    }

    speed = v / 3072 * 136;
    ctx[0x1c] = speed;
    if (speed > 0x1800) {
        speed = 0x1800;
    } else if (speed < 0xc00) {
        speed = 0xc00;
    }
    ctx[0x1c] = speed;

    /* Read the step count back through the field, not from `speed`: the dependency is what pins
     * the store ahead of the division, which is where the ROM puts it. */
    steps = ctx[0x1c] / 136;
    if (steps == 0) {
        ctx[0xd] = 0;
    } else {
        ctx[0xd] = func_02020400(v * 2, steps);
    }

    ctx[0xb] = *(int *)(ctx[2] + 4);
    ctx[0xc] = *(int *)(*(int *)(ctx[0] + 0x3e8) + 0x194) - ctx[0xb];
    if (ctx[0xc] > 0) {
        ctx[0xc] = 0;
    }

    func_ov107_020c9264(ctx[0], 0xb, 0);
    ctx[0x17] = 0;
    *(unsigned char *)((char *)ctx + 0x75) = 0;
    *(unsigned char *)((char *)ctx + 0x76) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), func_ov225_020d3900);
}
