/* Descent tick of the ov137 enemy: the target is re-acquired into +0x2c (no target ends the
 * state at once); a 50.0 downward probe (func_ov138_020d1bdc) that hits turns the +8
 * sub-object onto the hit normal (ed60 by data_02042264) and lifts its +0x20 height by 0x100.
 * The +0x10 point tracks the +0x398 bone's x/z while its y sinks by 30 x rate x 0.5 per frame
 * and places the +4 sub-object; the +0x28 timer accumulates the rate and past 1.0 resets with
 * the +0x30 hit mask before handing over to func_ov138_020d2008. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int q[4]; } Quat;

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int func_ov107_020cab14(int owner, int flag);
extern void func_0203c640(int *node);
extern int func_ov138_020d1bdc(int *state, Vec3 *dir, Vec3 *out);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0203c9d0(void *transform, const Quat *q);
extern void func_0203ca30(void *transform, const Vec3 *translation);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov138_020d2008(int *node);
extern const Vec3 data_02042264;

void func_ov138_020d1eac(int *node)
{
    int *state = (int *)node[1];
    int step = *(int *)(node[0] + 0x2c) * 30;
    Vec3 hit;
    Vec3 down = {0};
    Quat q;

    state[0xb] = func_ov107_020cab14(*state, 0);
    if (state[0xb] == 0) {
        func_0203c640(node);
        return;
    }
    down.y = -0x32000;
    if (func_ov138_020d1bdc(state, &down, &hit) != 0) {
        func_0202ed60(&q, &data_02042264, &hit);
        func_0203c9d0((void *)(state[2] + 4), &q);
        state[8] += 0x100;
        func_0203ca30((void *)(state[2] + 4), (Vec3 *)(state + 7));
    }
    state[4] = *(int *)(*(int *)(*state + 0x398) + 0x14);
    state[5] += FX_Mul(step, 0x800);
    state[6] = *(int *)(*(int *)(*state + 0x398) + 0x1c);
    func_0203ca30((void *)(state[1] + 4), (Vec3 *)(state + 4));
    state[0xa] += *(int *)(node[0] + 0x2c);
    if (state[0xa] <= 0x1000) {
        return;
    }
    state[0xa] = 0;
    *(unsigned char *)((char *)state + 0x30) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov138_020d2008);
}
