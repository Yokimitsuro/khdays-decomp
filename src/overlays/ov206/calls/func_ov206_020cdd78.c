/*
 * func_ov206_020cdd78 -- x4 (ov206/207/274/275). AI-state tick: acquire the target, wind up, then
 * fire attack 0xc once the sub-node at state[3] goes idle.
 * Acquire target (020cab14) -> state[4]; none -> mark *state[0]+0x1c7=2 and bail (0203c634 cb=0).
 * Else: dir = normalise(target_pos(+0x190) - state[1]); state[0xf] = delta*30/10;
 * state[0x11] = atan2(dir.x, dir.z). While the sub-node byte *(char*)state[3] is still set, return.
 * Once idle: fire attack 0xc (020c9264, flag 0) and hand off to the 020cde58 continuation.
 */
struct vec { int x, y, z; };
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern int  func_020050b4(int x, int z);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov206_020cde58(void);

void func_ov206_020cdd78(int *self) {
    int *state = (int *)self[1];
    struct vec v;
    int target;

    target = func_ov107_020cab14(*state, 0);
    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[1], &v);
    func_01ff8d18(&v, &v);
    state[0xf] = *(int *)(*self + 0x2c) * 0x1e / 10;
    state[0x11] = func_020050b4(v.x, v.z);
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xc, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov206_020cde58);
}
