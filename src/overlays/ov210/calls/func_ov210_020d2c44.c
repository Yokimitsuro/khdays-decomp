/*
 * func_ov210_020d2c44 -- x3 (ov210/211/282). AI-state tick: strafe the same target on a timer, fire.
 * If the freshly acquired target no longer matches cached state[4], mark *state[0]+0x1c7=2 and bail.
 * Else dir = normalise(flatten_y(state[4](+0x190) - state[1])); state[0xa] = atan2(dir.x, dir.z);
 * state[5..7] = data_02042264 x dir scaled 0x100. Advance timer state[0xb] += owner_delta; while it
 * stays under state[0xc], return. Once past: fire attack 0x14 (020c9264) and hand off to the 020d2d38
 * state.
 */
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern int  func_020050b4(int x, int z);
extern void VEC_CrossProduct(void *a, void *b, void *c);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_ov107_020c9264(int a, int b, int c);
extern int  data_02042264;
extern void func_ov210_020d2d38(void);

void func_ov210_020d2c44(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int target = func_ov107_020cab14(*state, 0);

    if (state[4] != target) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[1], v);
    v[1] = 0;
    func_01ff8d18(v, v);
    state[0xa] = func_020050b4(v[0], v[2]);
    VEC_CrossProduct(&data_02042264, v, (void *)(state + 5));
    func_01ffa724(0x100, (void *)(state + 5), (void *)(state + 5));
    state[0xb] += *(int *)(*self + 0x2c);
    if (state[0xb] < state[0xc]) {
        return;
    }
    func_ov107_020c9264(*state, 0x14, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov210_020d2d38);
}
