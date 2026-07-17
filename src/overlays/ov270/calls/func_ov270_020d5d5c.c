/*
 * Tick the timed spin/retreat state, retreat variant (x5). Twin of TickSpinRetreat
 * (func_ov195_020d2260) -- same shape, the only difference is the timeout state (10 here, 0xb
 * there).
 *
 * state[5] = (owner delta at *self+0x2c) * 30 / 3 -- base is *self (the OWNER, self[0]), not
 * state. Re-acquire the target; if present store its heading (atan2 of the flattened aim) in
 * state[4]. Fetch a per-frame spin factor (020c9f48), transform a scratch vector by the owner
 * matrix (*state+0xa0) into state+0x18, scale by that factor. Finally, unless the sub-node at
 * state[1]+0xad is busy, decrement state[0x12]: still positive -> stay in state 10, expired ->
 * drop to state 2.
 *
 * MATCHED at exact size on the FIRST compile, straight off the ov195 template -- the division at
 * the function HEAD matches (divisor 3, magic 0x55555556, no post-shift; unlike the tail-position
 * /5 of ov142 which ties). `tmp` before `aim` for the frame; the counter's <= 0 arm first.
 */
extern int func_ov107_020cab14(int obj, int out);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_020050b4(int x, int z);
extern int func_ov107_020c9f48(int a, void *out);
extern void func_0202f384(void *dst, void *mtx, void *src);
extern void func_01ffa724(int s, void *v, void *d);

void func_ov270_020d5d5c(int *self) {
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
        *(char *)(*state + 0x1c7) = 10;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
    }
}
