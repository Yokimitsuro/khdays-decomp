/*
 * func_ov192_020d372c -- MATCHED (408/408 bytes, 102 instrs). x5 family.
 * Rescued 2026-07-17 from a "register-CHOICE tie" write-up: it was TWO ordinary bugs.
 *   (1) ARITY -- func_ov107_020c9264 takes THREE args (a, b, 0); the tree uses the 3-arg form
 *       1448x. The dropped trailing `0` is the ROM's `mov r2,#0`, which is why the reset zero
 *       "landed in r2 (ROM) vs r0 (mine)". With the arg present mwcc is forced to keep it in r2.
 *   (2) ADD OPERAND ORDER -- `atan2 + roll` must be a COMPOUND-ASSIGN accumulate (`a += roll`)
 *       so the atan2 result (r0) is the accumulator base: emits `add r0,r0,r5` not `add r0,r5,r0`.
 *       Neither `a + roll` nor `roll + a` produced it -- mwcc canonicalises both to r5-first.
 *
 * WHAT IT DOES: a charge/telegraph state. state[0xc] = (owner delta) * 30 / 5; advance the timer
 * state[0xb]. Once past 0x4cc, fire the telegraph once (020cc9c4) and set the flag at state+0x38.
 * While the timer is in [0x4cc, 0xbba], ease a value (01ff8a14 returns 64-bit, split lo/hi) into
 * the block via 020ccaa8. When the sub-node at state[1] goes idle: reset the timer and flags,
 * clear bit 1 of state+0x39, decrement the shot counter state[7]; expired -> fire attack 6 and
 * advance with a callback, else fire attack 5, re-acquire the target, and set state[5] to the aim
 * heading plus a random spread (RandNextScaled(0x1923) - 0xc91).
 *
 * ★ THE VALUABLE FINDING, and it confirms the family tie's position rule: the divide-by-5 here is
 * at the FUNCTION HEAD and it MATCHES -- `mul ; lsr(signbit) ; smull ; add ...,asr#1`, the sign
 * bit computed BEFORE the smull, exactly as the ROM has it. The IDENTICAL `* 0x1e / 5` divide TIES
 * in ov142/ov143 because there it sits at the function TAIL, where the register pressure lets mwcc
 * schedule the smull first. So position, not the divisor or the source form, decides: head-divide
 * /5 matches, tail-divide /5 ties. (See deferred-ties.md's divide-by-constant entry.)
 *
 * Also solved: Ghidra's "conditional pointer" `piVar3 = &stack0xfffffff4` when the target is 0 is
 * DEAD CODE -- the very next `if (target != 0)` gates the only use, so the aim buffer is always
 * sp+0. Do not model it. And the RNG roll is combined with -0xc91 BEFORE the atan2 (ROM order:
 * RandNextScaled, then the subtract, then atan2, then the sum), which needs
 * `int roll = 02023eb4(..) - 0xc91;` computed before the atan2 call.
 *
 * THE GAP: two scratch register choices, structure otherwise exact. The zero for the timer/flag
 * reset lands in r2 (ROM) vs r0 (mine) -- both scratch, the zero dies before the counter reuses
 * the register -- and the final `atan2 + roll` add commutes (ROM `add r0,r0,r5`, mine
 * `add r0,r5,r0`). Register-CHOICE class; the char flags are all unsigned (ldrb) and the counter
 * test is `<= 0`.
 */
extern void func_ov192_020d2478(int *state, int *p);
extern long long func_01ff8a14(int a, int b);
extern void func_ov192_020d255c(int *state, int lo, int hi, int *p);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, int cb);
extern int func_ov192_020d39fc(int obj, int out);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_02023eb4(int mul);
extern int func_020050b4(int x, int z);
extern int func_ov192_020d38c4;

void func_ov192_020d372c(int *self) {
    int *state = (int *)self[1];
    int aim[3];
    int t;
    int c;
    int target;

    state[0xc] = *(int *)(*self + 0x2c) * 0x1e / 5;
    state[0xb] += *(int *)(*self + 0x2c);
    if (*(unsigned char *)(state + 0xe) == 0 && state[0xb] >= 0x4cc) {
        func_ov192_020d2478(state, state + 8);
        *(unsigned char *)(state + 0xe) = 1;
    }
    t = state[0xb];
    if (t >= 0x4cc && t <= 0xbba) {
        long long fx = func_01ff8a14(t - 0x4cc, 0x6ee);
        func_ov192_020d255c(state, (int)fx, (int)((unsigned long long)fx >> 32), state + 8);
    }
    if (*(unsigned char *)state[1] != 0) {
        return;
    }
    state[0xb] = 0;
    *(unsigned char *)(state + 0xe) = 0;
    *(unsigned char *)((int)state + 0x39) &= ~2;
    c = state[7];
    state[7] = c - 1;
    if (c - 1 <= 0) {
        func_ov107_020c9264(*state, 6, 0);
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov192_020d38c4);
        return;
    }
    func_ov107_020c9264(*state, 5, 0);
    target = func_ov192_020d39fc(*state, 0);
    state[6] = target;
    if (target == 0) {
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[2], aim);
    {
        int roll = func_02023eb4(0x1923) - 0xc91;
        int a = func_020050b4(aim[0], aim[2]);
        a += roll;
        state[5] = a;
    }
}
