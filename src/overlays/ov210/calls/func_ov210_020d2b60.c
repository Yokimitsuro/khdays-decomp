/*
 * func_ov210_020d2b60 -- x3 (ov210/211/282). AI-state tick: keep strafing the same target, fire when
 * the sub-node frees.
 * If the freshly acquired target no longer matches the cached state[4], mark *state[0]+0x1c7=2 and
 * bail (0203c634 cb=0). Else dir = normalise(flatten_y(state[4](+0x190) - state[1]));
 * state[0xa] = atan2(dir.x, dir.z); state[5..7] = data_02042264 x dir (VEC_CrossProduct) scaled 0x100.
 * While the sub-node byte *(u8)state[3] is set keep waiting; else fire attack 0x13 (flag 1) and hand
 * off to the 020d2c44 state.
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
extern void func_ov210_020d2c44(void);

void func_ov210_020d2b60(int *self) {
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
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x13, 1);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov210_020d2c44);
}
