/* Homing-shot tick of the ov260 enemy: the +0x34 clock runs up at the owner's rate; the +0x28 step is
 * the +8 orientation's forward times the +0x38 speed, which decays by 5.5 % per 1/30 s slice and is
 * clamped to 0.375-0.625. Every entity around the owner (+0x74 sphere) is pushed by 0.5 along the
 * flattened direction away from it (kind 5); any acceptance breaks the shot: message 0 and sound 0x10
 * at the +0x18 position, sub-state 0. After 0.5 the shot turns towards the target (020cab14) while it
 * lies ahead (dot product above -0.875), slerping the orientation at 0.2 per frame. A world hit of the
 * step, or a swept sphere (half the owner's radius) from the +0x1c previous position, breaks it with
 * message 1 / 0 and sound 0x11; after 5.0 it expires with message 0. Otherwise +0x1c keeps the
 * position. */
typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;

extern void func_0202f384(Vec3 *out, void *pose, const Vec3 *k);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int FX_Inv(int num, int den);
extern int func_ov107_020c8eb8(int owner, void *query, int *out);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov260_020cd148(int owner, int mode, int arg);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_ov107_020cab14(int actor, int mode);
extern void func_0202ed60(Quat *out, const Vec3 *forward, const Vec3 *direction);
extern int VEC_DotProduct(Vec3 *a, Vec3 *b);
extern void func_0202f55c(Quat *out, int t, Quat *a, Quat *b);
extern void func_0202f4a4(Quat *out, Quat *in);
extern int func_01fff920(int collision, Vec3 *start, Vec3 *ray);
extern int func_01fff8e8(int collision, Vec3 *origin, Vec3 *dir, int radius, void *ignore);
extern const Vec3 data_02042258;

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov260_020d1fa0(int *node)
{
    int owner;
    int *state = (int *)node[1];
    Vec3 fwd;
    Vec3 to;
    int hits[4];
    Vec3 push;
    Quat q;
    int world;
    int speed;
    int hit;
    int rem;
    long i;
    long n;
    int target;

    owner = *state;
    world = *(int *)(owner + 4);
    state[0xd] += *(int *)(node[0] + 0x2c);
    hit = 0;
    func_0202f384(&fwd, state + 2, &data_02042258);
    func_01ff8d18(&fwd, &fwd);
    func_01ffa724(state[0xe], &fwd, (Vec3 *)(state + 10));
    for (rem = *(int *)(node[0] + 0x2c); rem > 0; rem -= 0x88) {
        state[0xe] = FX_MUL(state[0xe], 0x1000 - FX_MUL(FX_Inv(rem <= 0x88 ? rem : 0x88, 0x88), 0xe0));
    }
    speed = state[0xe];
    if (speed > 0xa00) {
        speed = 0xa00;
    } else if (speed < 0x600) {
        speed = 0x600;
    }
    state[0xe] = speed;
    n = func_ov107_020c8eb8(*(int *)(*state + 0x38c), (void *)(owner + 0x74), hits);
    for (i = 0; i < n; i++) {
        VEC_Subtract((void *)(hits[i] + 0x74), (void *)(owner + 0x74), &push);
        push.y = 0;
        func_01ff8d18(&push, &push);
        func_01ffa724(0x800, &push, &push);
        if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x38c), 5, &push, 0) != 0) {
            hit = 1;
        }
    }
    if (hit != 0) {
        func_ov107_020c0b90(*state, 0, *(Vec3 *)state[6], 0);
        func_ov260_020cd148(*(int *)(*state + 0x38c), 0x10, state[6]);
        *(unsigned char *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0xd] > 0x800) {
        target = func_ov107_020cab14(*state, 0);
        if (target != 0) {
            VEC_Subtract((void *)(target + 0x74), (void *)state[6], &to);
            func_01ff8d18(&to, &to);
            func_0202ed60(&q, &data_02042258, &to);
            if (VEC_DotProduct(&fwd, &to) >= -0xe00) {
                func_0202f55c((Quat *)(state + 2), FX_MUL(*(int *)(node[0] + 0x2c) * 0x14, 0x320),
                              (Quat *)(state + 2), &q);
                func_0202f4a4((Quat *)(state + 2), (Quat *)(state + 2));
            }
        }
    }
    if (func_01fff920(*(int *)(world + 0x7c), (Vec3 *)state[6], (Vec3 *)(state + 10)) != 0) {
        func_ov107_020c0b90(*state, 1, *(Vec3 *)state[6], 0);
        func_ov260_020cd148(*(int *)(*state + 0x38c), 0x11, state[6]);
        *(unsigned char *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)state[6], (void *)(state + 7), &to);
    if (func_01fff8e8(*(int *)(world + 0x7c), (Vec3 *)(state + 7), &to, *(int *)(owner + 0x80) / 2, 0) != 0) {
        func_ov107_020c0b90(*state, 0, *(Vec3 *)state[6], 0);
        func_ov260_020cd148(*(int *)(*state + 0x38c), 0x11, state[6]);
        *(unsigned char *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0xd] >= 0x5000) {
        func_ov107_020c0b90(*state, 0, *(Vec3 *)state[6], 0);
        *(unsigned char *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    *(Vec3 *)(state + 7) = *(Vec3 *)state[6];
}
