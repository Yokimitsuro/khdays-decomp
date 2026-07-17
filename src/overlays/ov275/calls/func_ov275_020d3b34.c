/*
 * func_ov275_020d3b34 -- x4 (ov206/207/274/275). AI-state tick: acquire the target, wind up, then
 * fire attack 2 once the sub-node at state[3] goes idle.
 * Acquire target (020cab14) -> state[4]; none -> mark *state[0]+0x1c7=2 and bail (0203c634 cb=0).
 * Else: dir = normalise(target_pos(+0x190) - state[1]); state[0xf] = delta*30/20;
 * state[0x11] = atan2(dir.x, dir.z); seed state[5..7] from const vec3 data_02041dc8. While the
 * sub-node byte *(char*)state[3] is still set, return. Once idle: fire attack 2 (020c9264, flag 1)
 * and hand off to the 020ce1c8 continuation via 0203c634.
 */
struct vec { int x, y, z; };
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern int  func_020050b4(int x, int z);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov275_020d3c28(void);
extern int  data_02041dc8;

void func_ov275_020d3b34(int *self) {
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
    state[0xf] = *(int *)(*self + 0x2c) * 0x1e / 20;
    state[0x11] = func_020050b4(v.x, v.z);
    *(struct vec *)(state + 5) = *(struct vec *)&data_02041dc8;
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 2, 1);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov275_020d3c28);
}
