/* Shot flight tick: the shot's own sphere (+0x74, radius +0x80) sweeps the actor list on behalf of
 * the +0x38c owner. The first entity that accepts a 0.25 horizontal push away from it (kind 0) ends
 * the shot: effect 0 at the +4 point, the owner's reaction 0x173 mode 5 there and pose 0. Otherwise
 * the step since the last tick (+0x20) is tested against the owner's +4 +0x7c stage grid (01fff920)
 * and a 0.19 sweep (01fff8e8, solid hits only); a wall ends the shot with reaction mode 6. The
 * +0x1c distance accumulates the step length; past 21.0 the shot fizzles (effect 0, pose 0). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 center; int nRadius; } Sphere;

extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov283_020cc92c(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_01fff920(int grid, void *pos, Vec3 *step);
extern int func_01fff8e8(int grid, void *pos, Vec3 *step, int radius, int flags);
extern int VEC_Mag(const Vec3 *v);

void func_ov283_020cf88c(int *node)
{
    int *state = (int *)node[1];
    int owner = *(int *)(*state + 4);
    Sphere sphere;
    Vec3 step;
    int hits[4];
    Vec3 push;
    int hit;
    int i;
    int n;

    sphere = *(Sphere *)(*state + 0x74);
    n = func_ov107_020c8eb8(*state, &sphere, hits);
    for (i = 0; i < n; i++) {
        VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push);
        push.y = 0;
        func_01ff8d18(&push, &push);
        func_01ffa724(0x400, &push, &push);
        if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x38c), 0, &push, 0) == 0) {
            continue;
        }
        func_ov107_020c0b90(*state, 0, *(Vec3 *)state[1], 0);
        func_ov283_020cc92c(*(int *)(state[0] + 0x38c), 0x173, 5, (void *)state[1]);
        *(u8 *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)state[1], state + 8, &step);
    *(Vec3 *)(state + 8) = *(Vec3 *)state[1];
    if (func_01fff920(*(int *)(owner + 0x7c), (void *)state[1], &step) != 0) {
        func_ov107_020c0b90(*state, 0, *(Vec3 *)state[1], 0);
        *(u8 *)(*state + 0x1c7) = 0;
        func_ov283_020cc92c(*(int *)(state[0] + 0x38c), 0x173, 6, (void *)state[1]);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    hit = func_01fff8e8(*(int *)(owner + 0x7c), (void *)state[1], &step, 0x300, 0);
    if (hit != 0 && *(int *)(hit + 8) == 0) {
        func_ov107_020c0b90(*state, 0, *(Vec3 *)state[1], 0);
        *(u8 *)(*state + 0x1c7) = 0;
        func_ov283_020cc92c(*(int *)(state[0] + 0x38c), 0x173, 6, (void *)state[1]);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[7] += VEC_Mag(&step);
    if (state[7] < 0x15000) {
        return;
    }
    func_ov107_020c0b90(*state, 0, *(Vec3 *)state[1], 0);
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
