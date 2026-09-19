/* Back-off tick: runs the +0x1c timer, sets the +0x48 rate to 30/10 of the frame step and
 * re-acquires the lock-on target into +0x24 (none: pose request 2, dispatch null). The +0x38
 * orientation looks from the actor at the target (data_02042264 up); the direction away from
 * the target (data_02042258 when degenerate, its rise capped at 0x100 and renormalised) scaled
 * by 0x800 becomes the +0x50 step, copied to +0xc; the gap between the two body radii (+0x80,
 * floored at 0) is measured. Once the gap exceeds 0x4000 or the timer passes 0x3000, pose 0x14
 * plays and the node moves to 020ce5d0. */
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
extern void func_ov273_020d2210(void);

void func_ov273_020d2094(int *self) {
    int actor;
    int target;
    int *state = (int *)self[1];
    int mtx[9];
    struct v3 v;
    int dist;

    state[7] += *(int *)(self[0] + 0x2c);
    state[0x12] = *(int *)(self[0] + 0x2c) * 30 / 10;
    target = state[9] = func_ov107_020cab14(*state, 0);
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    actor = *state;
    func_0203cd7c(mtx, target + 0x74, actor + 0x74, &data_02042264);
    func_0202ea48((void *)(state + 0xe), mtx);
    VEC_Subtract((void *)(actor + 0x74), (void *)(target + 0x74), &v);
    dist = func_01ff8d18(&v, &v);
    if (dist == 0) {
        v = data_02042258;
    }
    if (v.y > 0x100) {
        v.y = 0x100;
        func_01ff8d18(&v, &v);
    }
    dist -= *(int *)(target + 0x80) + *(int *)(actor + 0x80);
    if (dist < 0) dist = 0;
    func_01ffa724(0x800, &v, state + 0x14);
    *(struct v3 *)(state + 3) = *(struct v3 *)(state + 0x14);
    if (dist <= 0x4000) {
        if (state[7] < 0x3000) return;
    }
    func_ov107_020c9264(*state, 0x14, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov273_020d2210);
}
