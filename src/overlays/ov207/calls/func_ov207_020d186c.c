/*
 * func_ov207_020d186c -- x4 (ov206/207/274/275). AI-state tick: track a target, steer a stored
 * heading toward it, and once a timer lapses fire the transition if past the target.
 * Acquire target (020cab14) -> state[4]; none -> mark *state[0]+0x1c7=2 and bail (0203c634 cb=0).
 * Else: dir = normalise(target_pos(+0x190) - state[1]); state[0xf] = delta*30/30;
 * state[0x11] = atan2(dir.x, dir.z). Rebuild state[5..7]: a scalar factor + base vector from
 * 020c9f48/0202f384, scale it (01ffa724) and normalise into w. Decrement timer state[0xb] -= delta;
 * while >0, return. Then if dir . w > 0, clear *(*state[0]+0x384)+0xa8 and fire the transition
 * (0203c634 with the 020cdd78 continuation).
 */
struct vec { int x, y, z; };
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern int  func_020050b4(int x, int z);
extern int  func_ov107_020c9f48(int obj, void *out);
extern void func_0202f384(void *dst, void *src, void *w);
extern void func_01ffa724(int scale, void *in, void *out);
extern int  VEC_DotProduct(void *a, void *b);
extern void func_ov207_020d19b8(void);

void func_ov207_020d186c(int *self) {
    int *state = (int *)self[1];
    struct vec v;
    struct vec w;
    int target;
    int factor;
    int t;

    target = func_ov107_020cab14(*state, 0);
    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[1], &v);
    func_01ff8d18(&v, &v);
    state[0xf] = *(int *)(*self + 0x2c) * 30 / 30;
    state[0x11] = func_020050b4(v.x, v.z);
    factor = func_ov107_020c9f48(*(int *)(*state + 0x3b4), &w);
    func_0202f384((void *)(state + 5), (void *)(*state + 0xa0), &w);
    func_01ffa724(factor, (void *)(state + 5), (void *)(state + 5));
    func_01ff8d18((void *)(state + 5), &w);
    t = state[0xb] - *(int *)(*self + 0x2c);
    state[0xb] = t;
    if (t > 0) {
        return;
    }
    if (VEC_DotProduct(&v, &w) <= 0) {
        return;
    }
    *(char *)(*(int *)(*state + 0x384) + 0xa8) = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov207_020d19b8);
}
