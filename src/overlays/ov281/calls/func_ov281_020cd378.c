/*
 * Aim at the target and pick an attack by range and a die roll (x4).
 *
 * Re-acquire the target (020cab14); none -> state 2 and advance. Aim vector owner->target,
 * normalise for the distance, store the heading (atan2) in state[5]. If the distance is past
 * 0x4000 the target is too far -> state 4. Otherwise run the cooldown at state[7]: while it is
 * still positive, wait. When it expires, roll a d100: under 0x32 -> attack 9; else, inside 0x2000
 * -> attack 6, further -> attack 7.
 *
 * MATCHED at exact size on the FIRST compile -- a clean SDK-vein steer (stack aim vector, real
 * control flow, no divide, no Q12). Two catalogued spellings carried it:
 *  - the RNG copy artifact `func_02023eb4(0x65) + (dist - dist)` -- and `dist` is the right v: it
 *    is already live across the RandNextScaled call (used two branches later for the 0x2000
 *    test), per the refinement in deferred-ties.md. The roll is then COMPARED (not stored), so
 *    the `add r0,r0,#0` is the copy before the cmp.
 *  - every branch pair written with the arm the ROM branches TO written second: `if (roll < 0x32)
 *    state9` first (ROM `bge` sends the >= case out of line), and `dist > 0x4000`/`counter > 0`
 *    likewise.
 * The state byte is `char` (strb), the counter test is `> 0`.
 */
extern int func_ov107_020cab14(int obj, int out);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern int func_020050b4(int x, int z);
extern int func_02023eb4();

void func_ov281_020cd378(int *self) {
    int *state = (int *)self[1];
    int aim[3];
    int target;
    int dist;
    int counter;
    int roll;

    target = func_ov107_020cab14(*state, 0);
    state[2] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)(*state + 0xb0), aim);
    dist = func_01ff8d18(aim, aim);
    state[5] = func_020050b4(aim[0], aim[2]);
    if (dist > 0x4000) {
        *(char *)(*state + 0x1c7) = 4;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    counter = state[7] - *(int *)(*self + 0x2c);
    state[7] = counter;
    if (counter > 0) {
        return;
    }
    state[7] = 0;
    roll = func_02023eb4(0x65) + (dist - dist);
    if (roll < 0x32) {
        *(char *)(*state + 0x1c7) = 9;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    if (dist < 0x2000) {
        *(char *)(*state + 0x1c7) = 6;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    *(char *)(*state + 0x1c7) = 7;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
