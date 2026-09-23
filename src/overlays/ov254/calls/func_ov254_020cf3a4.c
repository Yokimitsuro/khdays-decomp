/* Approach tick: the +0xc / +0x14 velocity points from the +0x18 point towards the +8 track
 * (speed 0.25, level); a fresh waypoint (020cd128) copies +0x34 to +0x30; the +0x10 climb is the
 * height difference to route point 0xb, clamped to +-0x7fff. Within 10.0 pose 0x1a plays, the
 * +0x44 timer clears, the +0x50 start takes the track's +4 and +0x54 the distance to route point
 * 5; the +0x70 flag clears and the node moves to 020cf4e8. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern int func_ov254_020cd128(int *node);
extern int func_ov254_020cd840(int *state, int a);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov254_020cf4e8(void);

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov254_020cf3a4(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    int dist;

    VEC_Subtract(state + 6, (void *)state[2], &d);
    d.y = 0;
    dist = func_01ff8d18(&d, &d);
    if (func_ov254_020cd128(node) != 0) {
        state[0xc] = state[0xd];
    }
    state[4] = func_ov254_020cd840(state, 0xb) - *(int *)(state[2] + 4);
    state[4] = state[4] > 0x7fff ? 0x7fff : (state[4] < -0x7fff ? -0x7fff : state[4]);
    state[3] = FX_Mul(d.x, 0x400);
    state[5] = FX_Mul(d.z, 0x400);
    if (dist > 0xa000) {
        return;
    }
    func_ov107_020c9264(*state, 0x1a, 0);
    state[0x11] = 0;
    state[0x14] = *(int *)(state[2] + 4);
    state[0x15] = func_ov254_020cd840(state, 5) - state[0x14];
    *((u8 *)state + 0x70) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020cf4e8);
}
