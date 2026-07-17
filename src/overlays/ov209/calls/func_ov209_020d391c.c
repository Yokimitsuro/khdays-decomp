/*
 * func_ov209_020d391c -- x3 (ov208/209/268). AI-state tick: face the target and fire attack 0xa once
 * the owner ready-byte clears.
 * state[0x18] = owner_delta*30/30. Acquire (020d0ea4) -> state[4]; none -> mark *state[0]+0x1c7=2 and
 * bail (0203c634 cb=0). Else dir = normalise(target(+0x190) - state[2]); state[0xd] = atan2(dir.x,
 * dir.z). While the ready byte *(u8)(state[1]+0xad) is set, return; once clear fire attack 0xa and
 * hand off to the 020d1be0 state.
 */
extern int  func_ov209_020d2cc4(int obj, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern int  func_020050b4(int x, int z);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov209_020d3a00(void);

void func_ov209_020d391c(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int target;

    state[0x18] = *(int *)(*self + 0x2c) * 0x1e / 30;
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
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xa, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov209_020d3a00);
}
