/* Patrol tick: the +0xc / +0x14 velocity points from the +0x18 point towards the +8 track (speed
 * 0.25, level) and the +0x10 climb is the height difference to the next route point (020cd840),
 * clamped to +-0x7fff. Within 10.0 of the track the next move is 8 when aggressive (+0x78) and the
 * +0x21a stock is at most 60 % of +0x218, else 4. */
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern int func_ov254_020cd840(int *state, int a);
extern void func_0203c634(int *node, int slot, void *cb);

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov254_020d1710(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    int dist;

    VEC_Subtract(state + 6, (void *)state[2], &d);
    d.y = 0;
    dist = func_01ff8d18(&d, &d);
    state[4] = func_ov254_020cd840(state, -1) - *(int *)(state[2] + 4);
    state[4] = state[4] > 0x7fff ? 0x7fff : (state[4] < -0x7fff ? -0x7fff : state[4]);
    state[3] = FX_Mul(d.x, 0x400);
    state[5] = FX_Mul(d.z, 0x400);
    if (dist > 0xa000) {
        return;
    }
    if (state[0x1e] != 0 && *(short *)(*state + 0x200 + 0x1a) <= *(short *)(*state + 0x200 + 0x18) * 60 / 100) {
        *(signed char *)(*state + 0x1c7) = 8;
    } else {
        *(signed char *)(*state + 0x1c7) = 4;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
