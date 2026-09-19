/* Homing turn tick: snapshots the +8 target's +0x10 position into +0x70, runs the +0x18 timer
 * and maps it to a 0..1 blend t. The +0x30 rotation faces the target from the +4 anchor, the
 * +0x20 pose slerps towards it by 30/5 of the frame step, its forward (data_02042258) scaled by
 * the +0x1c speed and by t is blended with (1 - t) of the +0x64 base velocity into +0xc, and the
 * +0x40 rotation is rebuilt from data_0204227c and the same direction. Once t reaches 1.0 the timer and +0x7c
 * clear, bit 1 of the actor's +0x394 is raised and the node moves to 020d1208. */
typedef struct { int x, y, z; } Vec3;

extern int FX_Inv(int num, int den);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0202ed60(void *rotation, const Vec3 *from, const Vec3 *to);
extern void func_0202f55c(void *a, int s, void *b, void *m);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;
extern const Vec3 data_0204227c;
extern void func_ov213_020d1208(void);

void func_ov213_020d10b0(int *node) {
    int *state = (int *)node[1];
    Vec3 dir;
    Vec3 fwd;
    int t;

    *(Vec3 *)(state + 0x1c) = *(Vec3 *)(state[2] + 0x10);
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
    func_0202ed60((void *)(state + 0x10), &data_0204227c, &dir);
    if (t < 0x1000) return;
    state[6] = 0;
    state[0x1f] = 0;
    *(int *)(*state + 0x394) |= 2;
    func_0203c634(node, *(signed char *)(node + 8), func_ov213_020d1208);
}
