/* Descent tick of the ov158 enemy: the target is re-acquired into +0x2c (no target ends the
 * state at once); a 50.0 downward probe (func_ov158_020cdfb0) that hits turns the +8 sub-object
 * onto the hit normal (ed60 by data_02042264) and lifts its +0x20 height by 0x100. A second
 * probe of 30 x rate x 0.5 that hits turns the +0xc sub-object onto its normal, moves it (and
 * the +0x10 point) to the +0x1c point, fires reaction 0x150 mode 7 there and hands over to
 * func_ov158_020ce6dc. Otherwise the segment from the +0x10 point along the normalised probe
 * (radius 0x400) is swept over the actor list: with hits, the +0x10 point moves to the nearest
 * one along the segment, the +0xc sub-object goes there, the +0x28 distance clears, reaction
 * 0x150 mode 8 fires and the same hand-over happens; without, the +0x10 point tracks the +0x1c
 * x / +0x24 z while its y sinks by the probe and the +4 sub-object follows. */
typedef int fx32;
typedef long long fx64;
typedef struct { int x, y, z; } Vec3;
typedef struct { int q[4]; } Quat;
typedef struct { Vec3 origin; Vec3 dir; int nLength; int nRadius; } Segment;

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int func_ov107_020cab14(int owner, int flag);
extern void func_0203c640(int *node);
extern int func_ov158_020cdfb0(int *state, Vec3 *dir, Vec3 *out);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0203c9d0(void *transform, const Quat *q);
extern void func_0203ca30(void *transform, const Vec3 *translation);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020c8f44(int owner, Segment *query, int *results);
extern int func_02036304(Vec3 *point, Segment *seg, fx64 *outDist);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov158_020ce6dc(int *node);
extern const Vec3 data_02042264;

void func_ov158_020ce3e0(int *node)
{
    int *state = (int *)node[1];
    Vec3 down = {0};
    int step = *(int *)(node[0] + 0x2c) * 30;
    Vec3 hit;
    Quat q1;
    Quat q2;
    int results[4];
    Segment seg;
    fx64 along;
    int i;
    int n;
    fx64 best;

    state[0xb] = func_ov107_020cab14(*state, 0);
    if (state[0xb] == 0) {
        func_0203c640(node);
        return;
    }
    down.y = -0x32000;
    if (func_ov158_020cdfb0(state, &down, &hit) != 0) {
        func_0202ed60(&q1, &data_02042264, &hit);
        func_0203c9d0((void *)(state[2] + 4), &q1);
        state[8] += 0x100;
        func_0203ca30((void *)(state[2] + 4), (Vec3 *)(state + 7));
    }
    down.y = -FX_Mul(step, 0x800);
    if (func_ov158_020cdfb0(state, &down, &hit) != 0) {
        func_0202ed60(&q2, &data_02042264, &hit);
        func_0203c9d0((void *)(state[3] + 4), &q2);
        *(Vec3 *)(state + 4) = *(Vec3 *)(state + 7);
        func_0203ca30((void *)(state[3] + 4), (Vec3 *)(state + 4));
        func_ov107_020c5af8(*state, 0x150, 7, state + 4);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov158_020ce6dc);
        return;
    }
    seg.origin = *(Vec3 *)(state + 4);
    seg.nLength = func_01ff8d18(&down, &seg.dir);
    seg.nRadius = 0x400;
    n = func_ov107_020c8f44(*state, &seg, results);
    if (n != 0) {
        best = 0x7fffffffffffffffLL;
        for (i = 0; i < n; i++) {
            func_02036304((Vec3 *)(results[i] + 0x74), &seg, &along);
            if (along < best) {
                best = along;
            }
        }
        state[4] = (fx32)((best * seg.dir.x + 0x80000000LL) >> 32);
        state[5] = (fx32)((best * seg.dir.y + 0x80000000LL) >> 32);
        state[6] = (fx32)((best * seg.dir.z + 0x80000000LL) >> 32);
        VEC_Add(&seg.origin, (Vec3 *)(state + 4), (Vec3 *)(state + 4));
        func_0203ca30((void *)(state[3] + 4), (Vec3 *)(state + 4));
        state[0xa] = 0;
        func_ov107_020c5af8(*state, 0x150, 8, state + 4);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov158_020ce6dc);
        return;
    }
    state[4] = state[7];
    state[5] += down.y;
    state[6] = state[9];
    func_0203ca30((void *)(state[1] + 4), (Vec3 *)(state + 4));
}
