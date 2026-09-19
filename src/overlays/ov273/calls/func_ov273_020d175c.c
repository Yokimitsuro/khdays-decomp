/* Circle-strafe tick: sets the +0x48 rate to 30/5 of the frame step and re-acquires the lock-on
 * target into +0x24 (none: pose request 2, dispatch null). The +0x5c approach speed is the gap
 * beyond both body radii plus 0.5, floored at 0 and capped at 0x800, applied along the target
 * direction into +0xc; a sideways drift (cross of the +0x18 handedness axis, data_02042264 or
 * data_02042240, with the direction) of 0xc00 is added and the sum halved, and the +0x38
 * orientation faces the drift (data_02042258). Once the +0x1c timer passes 1.0 the velocity is
 * kept at +0x50, pose 3 plays and the node moves to 020cdcb8. */
struct v3 { int x, y, z; };
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_01ff8d18(void *v, void *out);
extern void func_01ffa724(int s, void *v, void *d);
extern void VEC_CrossProduct(const void *a, void *b, void *d);
extern void VEC_Add(void *a, void *b, void *d);
extern void func_0202ed60(void *rotation, const void *from, void *to);
extern void func_ov107_020c9264(int a, int b, int c);
extern struct v3 data_02042264;
extern struct v3 data_02042240;
extern struct v3 data_02042258;
extern void func_ov273_020d18f8(void);

void func_ov273_020d175c(int *self) {
    int *state = (int *)self[1];
    struct v3 dir;
    struct v3 drift;
    struct v3 side;
    int actor;
    int target;
    int d;

    state[0x12] = *(int *)(self[0] + 0x2c) * 30 / 5;
    target = state[9] = func_ov107_020cab14(*state, 0);
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    actor = *state;
    VEC_Subtract((void *)(target + 0x74), (void *)(actor + 0x74), &dir);
    d = func_01ff8d18(&dir, &dir);
    {
        int reach = *(int *)(target + 0x80) + *(int *)(actor + 0x80) + 0x800;
        if (d > reach) d -= reach;
        else d = 0;
    }
    if (d > 0x800) d = 0x800;
    state[0x17] = d;
    func_01ffa724(*(volatile int *)(state + 0x17), &dir, state + 3); /* ROM reloads +0x5c after the store */
    VEC_CrossProduct(state[6] == 1 ? &data_02042264 : &data_02042240, &dir, &side);
    func_01ff8d18(&side, &side);
    func_01ffa724(0xc00, &side, &drift);
    VEC_Add(state + 3, &drift, state + 3);
    func_01ffa724(0x800, state + 3, state + 3);
    func_0202ed60(state + 0xe, &data_02042258, &side);
    state[7] += *(int *)(self[0] + 0x2c);
    if (state[7] <= 0x1000) return;
    *(struct v3 *)(state + 0x14) = *(struct v3 *)(state + 3);
    func_ov107_020c9264(*state, 3, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov273_020d18f8);
}
