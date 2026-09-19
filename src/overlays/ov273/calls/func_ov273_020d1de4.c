/* Close-in tick: runs the +0x1c timer, sets the +0x48 rate to 30/2 of the frame step and
 * re-acquires the lock-on target into +0x24 (none: pose request 2, dispatch null). The +0x38
 * orientation looks from the actor at the target (data_02042264 up); the gap between the two
 * body radii (+0x80, floored at 0, data_02042258 when the direction is degenerate) drives a
 * 0x800 step along the direction into +0x50, copied to +0xc. Once the gap closes under 0x1000
 * or the timer passes 0x3000, pose 3 plays and the node moves to 020ce2fc. */
struct v3 { int x, y, z; };
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern void func_0203cd7c(void *out, int a, int b, void *c);
extern void func_0202ea48(void *quat, void *mtx);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_01ff8d18(void *v, void *out);
extern void func_01ffa724(int s, void *v, void *d);
extern void func_ov107_020c9264(int a, int b, int c);
extern int  data_02042264;
extern struct v3 data_02042258;
extern void func_ov273_020d1f3c(void);

void func_ov273_020d1de4(int *self) {
    int *state = (int *)self[1];
    int mtx[9];
    struct v3 v;
    int actor;
    int dist;
    int target;

    state[7] += *(int *)(self[0] + 0x2c);
    state[0x12] = *(int *)(self[0] + 0x2c) * 30 / 2;
    target = state[9] = func_ov107_020cab14(*state, 0);
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    actor = *state;
    func_0203cd7c(mtx, target + 0x74, actor + 0x74, &data_02042264);
    func_0202ea48((void *)(state + 0xe), mtx);
    VEC_Subtract((void *)(target + 0x74), (void *)(actor + 0x74), &v);
    dist = func_01ff8d18(&v, &v);
    if (dist == 0) {
        v = data_02042258;
    }
    dist -= *(int *)(state[9] + 0x80) + *(int *)(*state + 0x80);
    if (dist < 0) dist = 0;
    func_01ffa724(0x800, &v, state + 0x14);
    *(struct v3 *)(state + 3) = *(struct v3 *)(state + 0x14);
    if (dist >= 0x1000) {
        if (state[7] < 0x3000) return;
    }
    func_ov107_020c9264(*state, 3, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov273_020d1f3c);
}
