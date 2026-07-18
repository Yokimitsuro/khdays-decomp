/*
 * func_ov137_020cd6fc -- x3. AI-state tick: face the acquired target, set the aim rate, dispatch.
 * target = acquire(*state, 0) -> state[2]. If none, mark *state[0]+0x1c7 = 2 and bail. Else set flags
 * (*(u16)(state[0]+0x1b0) |= 0xc, later *(u16)(state[0]+0x1ae) |= 8), face the target:
 * dir = normalise(flatten_y(target(+0x190) - state[0x13])); state[4] = atan2(dir.x, dir.z). Set the
 * turn rate state[5] = owner_delta * 30 / 5, then hand off to the 020cd7e8 state.
 */
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern int  func_020050b4(int x, int z);
extern void func_ov137_020cd7e8(void);

void func_ov137_020cd6fc(int *self) {
    int *state = (int *)self[1];
    int target;
    int v[3];

    target = func_ov107_020cab14(*state, 0);
    state[2] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    *(unsigned short *)(*state + 0x1b0) |= 0xc;
    VEC_Subtract((void *)(state[2] + 0x190), (void *)state[0x13], v);
    v[1] = 0;
    func_01ff8d18(v, v);
    state[4] = func_020050b4(v[0], v[2]);
    *(unsigned short *)(*state + 0x1ae) |= 8;
    state[5] = *(int *)(*self + 0x2c) * 0x1e / 5;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov137_020cd7e8);
}
