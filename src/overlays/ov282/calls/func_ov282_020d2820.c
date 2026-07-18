/*
 * func_ov282_020d2820 -- x3. AI-state tick: aim at the acquired target, steer, then fire once ready.
 * Acquire (020cab14) -> state[4]; none -> mark *state[0]+0x1c7=2 and bail. Else
 * dir = normalise(flatten_y(target(+0x190) - state[1])); state[0xa] = atan2(dir.x, dir.z).
 * factor = 020c9f48(*(*state+0x3b8), &w); build state[5..7] from *state+0xa0 (0202f384) scaled by factor
 * (01ffa724). While the sub-node byte *(u8)state[3] is set, return. Once idle: fire attack 0xd
 * (020c9264), trigger 020c9ee8(*(*state+0x3b8), 2, 0), and hand off to the 020d2918 state.
 */
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern int  func_020050b4(int x, int z);
extern int  func_ov107_020c9f48(int obj, void *out);
extern void func_0202f384(void *dst, void *src, void *w);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_ov282_020d292c(void);

void func_ov282_020d2820(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int w[3];
    int factor;
    int target = func_ov107_020cab14(*state, 0);

    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[1], v);
    v[1] = 0;
    func_01ff8d18(v, v);
    state[0xa] = func_020050b4(v[0], v[2]);
    factor = func_ov107_020c9f48(*(int *)(*state + 0x3b8), w);
    func_0202f384((void *)(state + 5), (void *)(*state + 0xa0), w);
    func_01ffa724(factor, (void *)(state + 5), (void *)(state + 5));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xd, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3b8), 2, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov282_020d292c);
}
