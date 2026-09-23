/* Update of the ov256 actor (+0x30): the +0x40 heading turns towards +0x44 at three times the
 * frame rate, is mirrored to +0x458 and orients the +0xa0 pose; the +0x10 velocity goes to +0xf0
 * and then halves. Outside move 3 the leash is checked: beyond 19.0 (21.0 when +0x6b is 2) from
 * the arena anchor (-0.25, 3.25, -1.5) +0x6b becomes 4, below height 12.0 of the +0xc track 0,
 * above 19.0 it becomes 1, each setting the +0x74 request. Past x 12.0 +0x78 / +0x7c are set.
 * The +0x48 timer advances and, in moves 2-4, the +0x50 countdown runs down to 0. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;

extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0203c9d0(int a, void *b);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern const Vec3 data_02042264;
extern const Vec3 data_ov256_020d2594;

void func_ov256_020cd740(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    Vec3 vel = *(Vec3 *)(state + 4);
    Vec3 anchor = data_ov256_020d2594;
    Vec3 d;
    int dist;
    int limit = 0x13000;

    state[0x10] = func_0203d040(state[0x10], state[0x11], *(int *)(node[0] + 0x2c) * 3, 0);
    *(int *)(*state + 0x458) = state[0x10];
    func_0202f188(&q, &data_02042264, state[0x10]);
    func_0203c9d0(*state + 0xa0, &q);
    VEC_Subtract(&anchor, (Vec3 *)(*state + 0xb0), &d);
    dist = func_01ff8d18(&d, &d);
    if (*((u8 *)state + 0x6b) == 2) {
        limit += 0x2000;
    }
    *(Vec3 *)(*state + 0xf0) = vel;
    func_01ffa724(0x800, (Vec3 *)(state + 4), (Vec3 *)(state + 4));
    if (*(signed char *)(*state + 0x100 + 0xc6) != 3) {
        if (dist > limit) {
            *((u8 *)state + 0x6b) = 4;
            state[0x1d] = 1;
        }
        if (((Vec3 *)state[3])->y < 0xc000) {
            *((u8 *)state + 0x6b) = 0;
            state[0x1d] = 1;
        }
        if (((Vec3 *)state[3])->y > 0x13000) {
            *((u8 *)state + 0x6b) = 1;
            state[0x1d] = 1;
        }
    }
    if (((Vec3 *)state[3])->x > 0xc000) {
        state[0x1e] = 1;
        state[0x1f] = 1;
    }
    state[0x12] += *(int *)(node[0] + 0x2c);
    if (!(*(signed char *)(*state + 0x100 + 0xc6) != 2 && *(signed char *)(*state + 0x100 + 0xc6) != 3 &&
          *(signed char *)(*state + 0x100 + 0xc6) != 4)) {
        state[0x14] -= *(int *)(node[0] + 0x2c);
        if (state[0x14] < 0) {
            state[0x14] = 0;
        }
    }
}
