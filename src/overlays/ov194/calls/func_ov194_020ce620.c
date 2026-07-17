/*
 * Tick the timed spin/retreat state: age the shared cooldown, keep facing the target, spin the
 * body, and count down to the next state (x5).
 *
 * First, unconditionally, `state[5] = (owner delta at *self+0x2c) * 30 / 3`. Note the base is
 * *self (self[0], the OWNER), NOT state (self[1]) -- the two are different objects and the ROM
 * loads *self here (`ldr r1,[r5]`) where the rest of the function uses state (`ldr r4,[r5,#4]`).
 * Then re-acquire the target; if present, store its heading (atan2 of the flattened aim) in
 * state[4]. Fetch a per-frame spin factor (020c9f48), transform a scratch vector by the owner's
 * matrix (*state+0xa0) into state+0x18, and scale it by that factor. Finally, unless the sub-node
 * at state[1]+0xad is busy, decrement the counter at state[0x12]: still positive -> stay in state
 * 0xb, expired -> drop to state 2.
 *
 * MATCHED off the SDK-vein template, and it is a clean win for the triage rule: it has real
 * control flow (a conditional aim, a two-way counter branch) and its scratch vectors are STACK
 * locals, so the scheduler had room and it matched at exact size on the first compile. Three
 * catalogued adjustments only:
 *  - the division is `* 0x1e / 3` (magic 0x55555556, no post-shift = divide by 3); NOT the /5 of
 *    ov142, and NOT the algebraic *10 (which would collapse to one mul).
 *  - `tmp` before `aim` in declaration order so the frame is aim=sp+0, tmp=sp+0xc (last-declared
 *    vector gets the lowest slot).
 *  - the counter's `<= 0` (state 2) arm is written FIRST -- the ROM's `bgt` sends the still-
 *    running case out of line.
 * The `*self` vs `state` base for the division was the one real trap: Ghidra prints `*param_1`
 * and it is easy to read as the state pointer, but it is the owner.
 */
extern int func_ov107_020cab14(int obj, int out);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_020050b4(int x, int z);
extern int func_ov107_020c9f48(int a, void *out);
extern void func_0202f384(void *dst, void *mtx, void *src);
extern void func_01ffa724(int s, void *v, void *d);

void func_ov194_020ce620(int *self) {
    int *state = (int *)self[1];
    int tmp[3];
    int aim[3];
    int target;
    int scale;
    int c;

    state[5] = *(int *)(*self + 0x2c) * 0x1e / 3;
    target = func_ov107_020cab14(*state, 0);
    state[2] = target;
    if (target != 0) {
        VEC_Subtract((void *)(target + 0x190), (void *)(*state + 0xb0), aim);
        state[4] = func_020050b4(aim[0], aim[2]);
    }
    scale = func_ov107_020c9f48(*(int *)(*state + 0x3d0), tmp);
    func_0202f384((void *)(state + 6), (void *)(*state + 0xa0), tmp);
    func_01ffa724(scale, (void *)(state + 6), (void *)(state + 6));
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        c = state[0x12];
        state[0x12] = c - 1;
        if (c - 1 <= 0) {
            *(char *)(*state + 0x1c7) = 2;
            func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
            return;
        }
        *(char *)(*state + 0x1c7) = 0xb;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
    }
}
