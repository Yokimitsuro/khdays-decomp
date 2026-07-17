/*
 * Circle-strafe the target: build a perpendicular drift, nudge the facing, and roll for the next
 * attack when the timer expires (x5).
 *
 * Re-acquire the target (020cab14); none -> state 2 and advance. Get a steering vector and its
 * magnitude (020cca34, clamped: over 0x100 becomes 0x180), scale it into the step at state+0x20.
 * Cross it with a fixed axis (data_02042264) to get a PERPENDICULAR drift, normalise, scale by
 * state[0x18]*0x180, and ADD that into the step -- so the node orbits rather than closes. Nudge
 * the facing (state[9] += or -= 0x60) when the target's height (target+0x78) and the owner's
 * (state[2]+4) differ by more than 0x80. Finally count down state[0x17]: when it expires, roll a
 * d100 -- under 0x3c AND a reachability check (020ccacc) picks attack 8, else 5 -- and advance
 * unless the resulting state byte is -1.
 *
 * MATCHED, and a third clean win for the SDK-vein triage rule: real control flow + STACK scratch
 * vectors. The scale/cross/add chain all reads and writes stack locals (v1=sp+0xc, v2=sp+0), so
 * mwcc scheduled it freely.
 *
 * Catalogued cracks, all needed:
 *  - the RNG copy artifact `func_02023eb4(0x65) + (counter - counter)` -- and the variable MUST
 *    be `counter`, not the distance `diff`. Both are live locals, but diff's register is needed
 *    for the height subtraction and reusing it for the artifact kept it alive one instruction too
 *    long; counter is already live across the call. `diff` is scoped INSIDE the height block so it
 *    dies at the clamp. This is the finding: `+ (v - v)` needs a v whose live range already spans
 *    the call, or it perturbs allocation upstream.
 *  - the height subtraction reads target+0x78 (minuend) into the first register: `int a =
 *    target+0x78; int b = state2+4; a - b;` with `a < b` reused for the sign, so both stay live
 *    for the branch (ROM `subs r2,r1,r0 ; ... ; cmp r1,r0`).
 *  - `counter <= 0` not `< 1` (the ROM's `cmp #0 ; bgt`), and `v1` before `v2` so the frame is
 *    v2=sp+0.
 *  - the final state byte is re-read after the store and compared to -1 signed (`ldrsb`).
 */
extern int func_ov107_020cab14(int obj, int out);
extern void func_0203c634(int self, int idx, int cb);
extern int func_ov177_020d431c(int self, void *out);
extern void func_01ffa724(int s, void *v, void *d);
extern void VEC_CrossProduct(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern void VEC_Add(void *a, void *b, void *d);
extern int func_02023eb4();
extern int func_ov177_020d43b4(int self);
extern int data_02042264;

void func_ov177_020d52f0(int *self) {
    int *state = (int *)self[1];
    int v1[3];
    int v2[3];
    int target;
    int mag;
    int counter;
    int roll;
    int st;

    target = func_ov107_020cab14(*state, 0);
    state[3] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    mag = func_ov177_020d431c((int)self, v1);
    if (mag > 0x100) {
        mag = 0x180;
    }
    func_01ffa724(mag, v1, (void *)(state + 8));
    VEC_CrossProduct(&data_02042264, v1, v2);
    func_01ff8d18(v2, v2);
    func_01ffa724(state[0x18] * 0x180, v2, v2);
    VEC_Add((void *)(state + 8), v2, (void *)(state + 8));
    {
        int a = *(int *)(state[3] + 0x78);
        int b = *(int *)(state[2] + 4);
        int diff = a - b;
        if (diff < 0) {
            diff = -diff;
        }
        if (diff > 0x80) {
            if (a < b) {
                state[9] -= 0x60;
            } else {
                state[9] += 0x60;
            }
        }
    }
    counter = state[0x17] - *(int *)(*self + 0x2c);
    state[0x17] = counter;
    if (counter <= 0) {
        roll = func_02023eb4(0x65) + (counter - counter);
        state[0x17] = 0;
        if (roll < 0x3c && func_ov177_020d43b4((int)self) != 0) {
            st = 8;
        } else {
            st = 5;
        }
        *(char *)(*state + 0x1c7) = st;
        if (*(signed char *)(*state + 0x1c7) != -1) {
            func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        }
    }
}
