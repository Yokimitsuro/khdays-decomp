/*
 * func_ov200_020d0c14 -- x3. AI-state tick: advance a timer, drive an interpolation, dispatch.
 * state[0xd] += owner_delta; t = FX_Inv(state[0xd], 0x800) clamped to <= 0x1000. Feed the eased
 * value (0x1000 - t)*6 into 0203ca50(state[1]+4, v, 0x2ffee, v). While state[0xd] < 0x800 return.
 * Once past: clear state[0xe] bits 0xf0, state[0x14] = 0, hand off via 0203c634 (cb=0).
 */
extern int  FX_Inv(int x, int k);
extern void func_0203ca50(int p, int a, int b, int c);
extern void func_0203c634(int self, int idx, int cb);

void func_ov200_020d0c14(int *self) {
    int *state = (int *)self[1];
    int t;

    state[0xd] += *(int *)(*self + 0x2c);
    t = FX_Inv(state[0xd], 0x800);
    if (t > 0x1000) {
        t = 0x1000;
    }
    func_0203ca50(state[1] + 4, (0x1000 - t) * 6, 0x2ffee, (0x1000 - t) * 6);
    if (state[0xd] < 0x800) {
        return;
    }
    state[0xe] &= ~0xf0;
    state[0x14] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
