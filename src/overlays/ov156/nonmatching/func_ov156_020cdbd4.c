/*
 * func_ov156_020cdbd4 -- UNFINISHED. 408/408 bytes, 102/102 instructions.
 * x5 family (worth 5). Semantically complete; the instruction SHAPE is exact.
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
extern void func_ov156_020cc9c4(int *state, int *p);
extern long long func_01ff8a14(int a, int b);
extern void func_ov156_020ccaa8(int *state, int lo, int hi, int *p);
extern void func_ov107_020c9264(int a, int b);
extern void func_0203c634(int self, int idx, int cb);
extern int func_ov107_020cab14(int obj, int out);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_02023eb4(int mul);
extern int func_020050b4(int x, int z);
extern int func_ov156_020cdd6c;

void func_ov156_020cdbd4(int *self) {
    int *state = (int *)self[1];
    int aim[3];
    int t;
    int c;
    int target;

    state[0xc] = *(int *)(*self + 0x2c) * 0x1e / 5;
    state[0xb] += *(int *)(*self + 0x2c);
    if (*(unsigned char *)(state + 0xe) == 0 && state[0xb] >= 0x4cc) {
        func_ov156_020cc9c4(state, state + 8);
        *(unsigned char *)(state + 0xe) = 1;
    }
    t = state[0xb];
    if (t >= 0x4cc && t <= 0xbba) {
        long long fx = func_01ff8a14(t - 0x4cc, 0x6ee);
        func_ov156_020ccaa8(state, (int)fx, (int)((unsigned long long)fx >> 32), state + 8);
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
        func_ov107_020c9264(*state, 6);
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov156_020cdd6c);
        return;
    }
    func_ov107_020c9264(*state, 5);
    target = func_ov107_020cab14(*state, 0);
    state[6] = target;
    if (target == 0) {
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[2], aim);
    {
        int roll = func_02023eb4(0x1923) - 0xc91;
        state[5] = func_020050b4(aim[0], aim[2]) + roll;
    }
}
