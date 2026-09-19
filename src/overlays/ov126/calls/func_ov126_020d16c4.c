/*
 * func_ov126_020d16c4 -- AI-state entry: seed the +0x3c counter with 6 times the owner's +0x2c
 * rate (30/5), fire attack 2 (020c9264) and, if a target is set (state[0xc]), aim the pose at
 * state[0x1a..] from data_02042264 and atan2(dir.x, dir.z) of target(+0x190) - *state(+0xb0).
 * Always hand off to the 020cdb28 state.
 */
extern void func_ov107_020c9264(int a, int b, int c);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_020050b4(int x, int z);
extern void func_0202f188(void *dst, void *k, int angle);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov126_020d1768(void);
extern int  data_02042264;

void func_ov126_020d16c4(int *self) {
    int *state = (int *)self[1];
    int v[3];

    state[0xf] = *(int *)(self[0] + 0x2c) * 0x1e / 5;
    func_ov107_020c9264(*state, 2, 0);
    if (state[0xc] != 0) {
        VEC_Subtract((void *)(state[0xc] + 0x190), (void *)(*state + 0xb0), v);
        func_0202f188((void *)(state + 0x1a), &data_02042264, func_020050b4(v[0], v[2]));
    }
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov126_020d1768);
}
