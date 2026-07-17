/*
 * func_ov282_020d2d4c -- x3 (ov210/211/282). AI-state tick: aim a perpendicular strafe at the target.
 * Acquire (020cab14) -> state[4]. With a target: dir = normalise(flatten_y(target(+0x190) - state[1]));
 * state[0xa] = atan2(dir.x, dir.z); state[5..7] = data_02042264 x dir (VEC_CrossProduct), scaled by
 * 0x100 (01ffa724). Then if the sub-node byte *(u8)state[3] is set, keep waiting; else mark
 * *state[0]+0x1c7 = 2 and bail (0203c634 cb=0).
 */
extern int  func_ov107_020cab14(int obj, int flag);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern int  func_020050b4(int x, int z);
extern void VEC_CrossProduct(void *a, void *b, void *c);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_0203c634(int self, int idx, int cb);
extern int  data_02042264;

void func_ov282_020d2d4c(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int target = func_ov107_020cab14(*state, 0);

    state[4] = target;
    if (target != 0) {
        VEC_Subtract((void *)(target + 0x190), (void *)state[1], v);
        v[1] = 0;
        func_01ff8d18(v, v);
        state[0xa] = func_020050b4(v[0], v[2]);
        VEC_CrossProduct(&data_02042264, v, (void *)(state + 5));
        func_01ffa724(0x100, (void *)(state + 5), (void *)(state + 5));
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    *(char *)(*state + 0x1c7) = 2;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
