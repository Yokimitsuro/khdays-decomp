/*
 * func_ov224_020d4bd8 -- x4 (ov221/222/224/225). AI-state tick: drive a spin/lunge along a matrix.
 * Clear the +0x60 hi-byte bit 0x80 each frame. Decrement timer state[0x14] -= owner_delta. When it
 * lapses (<= 0): reset it, rebuild the orientation matrix state[0xc..] from the direction
 * target(+0x190) - *state(+0xb0), advance it by delta*state[0x15]/4096 (0202f55c), and decay the
 * step state[0x15] *= 0xff8/4096. While the timer is still positive, ease the reach state[0x12]
 * down by (state[0x12]*timer)/1024. Then emit the transformed forward vector {0,0,reach} through
 * the matrix into state[6..8] (0202f384) and re-tick via 020d4950.
 */
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern void func_0202ed60(void *out, void *axis, void *in);
extern void func_0202f55c(void *a, int s, void *b, void *m);
extern void func_0202f384(void *dst, void *src, void *w);
extern void func_ov224_020d4988(int self, int a, int b);
extern int  data_02042258;

void func_ov224_020d4bd8(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int m[4];
    int reach = state[0x12];
    int t;

    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    t = state[0x14] - *(int *)(*self + 0x2c);
    state[0x14] = t;
    if (t <= 0) {
        state[0x14] = 0;
        VEC_Subtract((void *)(state[0x10] + 0x190), (void *)(*state + 0xb0), v);
        func_01ff8d18(v, v);
        func_0202ed60(m, &data_02042258, v);
        func_0202f55c((void *)(state + 0xc), *(int *)(*self + 0x2c) * state[0x15] / 0x1000,
                      (void *)(state + 0xc), m);
        state[0x15] = state[0x15] * 0xff8 / 0x1000;
    } else {
        reach = reach - reach * t / 0x400;
    }
    state[6] = 0;
    state[7] = 0;
    state[8] = reach;
    func_0202f384((void *)(state + 6), (void *)(state + 0xc), (void *)(state + 6));
    func_ov224_020d4988((int)self, 1, 1);
}
