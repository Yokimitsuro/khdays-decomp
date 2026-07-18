/*
 * func_ov209_020d459c -- x3. AI-state tick: during a mid-window, drive two anchors, then transition.
 * state[0xb] += owner_delta. When state[0xb] is in (0x2aa, 0xc44): copy the 4-word transform at
 * *(state[0]+0x3c4)+0x68, scale its 4th component by 0x1800 in Q12 (FX_MUL), and apply it via
 * 020d0f8c(state, 2, &v, 0); do the same for the transform at *(state[0]+0x3c8)+0x68. If the ready byte
 * *(u8)(state[1]+0xad) is set, keep waiting; else mark *state[0]+0x1c7 = 0xa and hand off (0203c634 cb=0).
 */
struct v4 { int w[4]; };
extern void func_ov209_020d2dac(int a, int b, void *c, int d);
extern void func_0203c634(int self, int idx, int cb);

void func_ov209_020d459c(int *self) {
    int *state = (int *)self[1];
    struct v4 v;

    state[0xb] += *(int *)(*self + 0x2c);
    if (state[0xb] > 0x2aa && state[0xb] < 0xc44) {
        v = *(struct v4 *)(*(int *)(*state + 0x3c4) + 0x68);
        v.w[3] = (int)(((long long)v.w[3] * 0x1800 + 0x800) >> 12);
        func_ov209_020d2dac((int)state, 2, &v, 0);
        v = *(struct v4 *)(*(int *)(*state + 0x3c8) + 0x68);
        v.w[3] = (int)(((long long)v.w[3] * 0x1800 + 0x800) >> 12);
        func_ov209_020d2dac((int)state, 2, &v, 0);
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(char *)(*state + 0x1c7) = 0xa;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
