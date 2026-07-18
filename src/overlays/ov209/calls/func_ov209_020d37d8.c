/*
 * func_ov209_020d37d8 -- x3. AI-state tick: set the turn rate, aim/steer, transition once the timer
 * expires and the target is in front. state[0x18] = owner_delta * 30 / 10. target = acquire(020d0ea4,
 * *state, 0) -> state[4]; none -> mark *state[0]+0x1c7=2 and bail. Else aim = target(+0x190) - state[2],
 * state[0xd] = atan2(normalise(aim)); steer state[5..7] from *state+0xa0 (020c9f48/0202f384) scaled by
 * factor (01ffa724), then w = normalise(state[5..7]). Advance state[0xf] -= owner_delta; while it stays
 * positive return. Once expired, if dot(aim, w) <= 0 keep waiting; otherwise clear *(state[1])+0xa8 and
 * hand off to the 020d1afc state.
 */
extern int  func_ov209_020d2cc4(int obj, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *in, void *out);
extern int  func_020050b4(int x, int z);
extern int  func_ov107_020c9f48(int obj, void *out);
extern void func_0202f384(void *dst, void *src, void *w);
extern void func_01ffa724(int scale, void *in, void *out);
extern int  VEC_DotProduct(void *a, void *b);
extern void func_ov209_020d391c(void);

void func_ov209_020d37d8(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int w[3];
    int factor;
    int target;

    state[0x18] = *(int *)(*self + 0x2c) * 0x1e / 10;
    target = func_ov209_020d2cc4(*state, 0);
    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[2], v);
    func_01ff8d18(v, v);
    state[0xd] = func_020050b4(v[0], v[2]);
    factor = func_ov107_020c9f48(*(int *)(*state + 0x3ac), w);
    func_0202f384((void *)(state + 5), (void *)(*state + 0xa0), w);
    func_01ffa724(factor, (void *)(state + 5), (void *)(state + 5));
    func_01ff8d18((void *)(state + 5), w);
    state[0xf] -= *(int *)(*self + 0x2c);
    if (state[0xf] > 0) {
        return;
    }
    if (VEC_DotProduct(v, w) <= 0) {
        return;
    }
    *(char *)(state[1] + 0xa8) = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov209_020d391c);
}
