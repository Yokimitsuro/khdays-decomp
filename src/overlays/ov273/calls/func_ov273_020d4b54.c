/* Sweep turn tick: re-acquires the lock-on target into +0x60 (none: pose request 0, dispatch
 * null), keeps its +0x74 position at +0x70, runs the +0x18 timer and maps it to a 0..1 blend t.
 * The +0x30 rotation faces the target from the +4 anchor, the +0x20 pose slerps towards it by
 * 30/5 of the frame step, its forward (data_02042258) scaled by the +0x1c speed and by t is
 * blended with (1 - t) of the +0x64 base velocity into +0xc, and the pose is copied to +0x40.
 * Once t reaches 1.0 the timer and +0x7c clear, effect 0x162 (kind 6) spawns at the anchor from
 * the +0x384 model and the node moves to 020d0d8c; otherwise the common 020d1364 step runs. */
typedef struct { int x, y, z; } Vec3;
struct m4 { int w[4]; };

extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern int FX_Inv(int num, int den);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0202ed60(void *rotation, const Vec3 *from, const Vec3 *to);
extern void func_0202f55c(void *a, int s, void *b, void *m);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_ov273_020d4fa4(int *state);
extern const Vec3 data_02042258;
extern void func_ov273_020d49cc(void);

void func_ov273_020d4b54(int *node) {
    int *state = (int *)node[1];
    Vec3 dir;
    Vec3 fwd;
    int t;
    int target;

    target = state[0x18] = func_ov107_020cab14(*state, 0);
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)(node + 8), 0);
        return;
    }
    *(Vec3 *)(state + 0x1c) = *(Vec3 *)(target + 0x74);
    state[6] += *(int *)(node[0] + 0x2c);
    t = FX_Inv(state[6], 0x1000);
    if (t > 0x1000) t = 0x1000;
    VEC_Subtract((Vec3 *)(state + 0x1c), (Vec3 *)state[1], &dir);
    func_01ff8d18(&dir, &dir);
    func_0202ed60((void *)(state + 0xc), &data_02042258, &dir);
    func_0202f55c(state + 8, *(int *)(node[0] + 0x2c) * 30 / 5, state + 8, state + 0xc);
    func_0202f384(&fwd, (void *)(state + 8), &data_02042258);
    func_01ffa724(state[7], &fwd, &fwd);
    func_01ffa724(t, &fwd, &fwd);
    func_01ffa724(0x1000 - t, (Vec3 *)(state + 0x19), (Vec3 *)(state + 3));
    VEC_Add((Vec3 *)(state + 3), &fwd, (Vec3 *)(state + 3));
    *(struct m4 *)(state + 0x10) = *(struct m4 *)(state + 8);
    if (t >= 0x1000) {
        state[6] = 0;
        state[0x1f] = 0;
        func_ov107_020c5af8(*(int *)(state[0] + 0x384), 0x162, 6, (void *)state[1]);
        func_0203c634(node, *(signed char *)(node + 8), func_ov273_020d49cc);
        return;
    }
    func_ov273_020d4fa4(state);
}
