/* Drift tick of an ov227 part: the +0x24 timer accumulates the owner's rate, bit 7 of the owner's
 * +0x60 high byte clears and the +0xc velocity decays to 0.97. When the owner's +0x74 sphere hits
 * something (func_ov227_020d42d8) effect 0 spawns there, the owner's sub-state resets to 0 and
 * the tick ends. Every 2.0 of the timer the velocity is re-aimed at 0.75 towards a point jittered
 * by up to 4.0 around the +8 target's +0x190, the timer and the +0x28 hit mask clear and the tick
 * hands over to func_ov227_020d4770. */
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov227_020d42d8(int *part, void *sphere);
extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_02023eb4(int n);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov227_020d4770(int *node);

static inline int RandRange(int lo, int hi)
{
    int d = hi - lo;

    if (d < 0) {
        d = -d;
    }
    return lo + func_02023eb4(d + 1);
}

void func_ov227_020d4600(int *node)
{
    int *state = (int *)node[1];
    Vec3 goal;

    state[9] += *(int *)(*node + 0x2c);
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    func_01ffa724(0xf85, (Vec3 *)(state + 3), (Vec3 *)(state + 3));
    if (func_ov227_020d42d8(state, (void *)(*state + 0x74)) != 0) {
        func_ov107_020c0b90(*state, 0, *(Vec3 *)(*state + 0x74), 1);
        *(unsigned char *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[9] < 0x2000) {
        return;
    }
    goal = *(Vec3 *)(state[2] + 0x190);
    goal.x += RandRange(-0x4000, 0x4000);
    goal.z += RandRange(-0x4000, 0x4000);
    VEC_Subtract(&goal, (void *)state[1], (Vec3 *)(state + 3));
    func_01ff8d18((Vec3 *)(state + 3), (Vec3 *)(state + 3));
    func_01ffa724(0xc00, (Vec3 *)(state + 3), (Vec3 *)(state + 3));
    state[9] = 0;
    *(unsigned char *)(state + 10) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov227_020d4770);
}
