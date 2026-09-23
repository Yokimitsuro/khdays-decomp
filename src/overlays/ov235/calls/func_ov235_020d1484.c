/* Hover tick of an ov235 state. While the +0xc idle byte is set the +0x40 rate is the frame rate
 * x 3.75 and, with a nearest target (020cab14, kept in +0x5c), the +0x2c orientation looks at it
 * (0203cd7c about data_02042264) and +0x68 takes the unit direction to it (zeroed without one).
 * Once it clears the +0x40 rate becomes x 0.6 and the +0x44 timer accumulates the frame rate; an
 * armed +0x74 request with fewer than 8 +0x78 uses plays animation 0x26 (looping), clears the
 * timer and hands over to func_ov235_020d161c, otherwise animation 0x1c plays, the +0x3a8 part
 * plays motion 0x15, the owner's +0x64 velocity becomes 1.5 up and the tick hands over to
 * func_ov235_020d1738. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
typedef struct { int m[9]; } Mtx33;

extern int func_ov107_020cab14(int obj, int kind);
extern void func_0203cd7c(Mtx33 *out, const Vec3 *at, const Vec3 *from, const Vec3 *up);
extern void func_0202ea48(Quat *out, const Mtx33 *m);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020d161c(int *node);
extern void func_ov235_020d1738(int *node);
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;

static inline void VEC_Set(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov235_020d1484(int *node)
{
    int *state = (int *)node[1];
    Mtx33 m;
    int owner;
    int target;

    if (*(unsigned char *)state[3] == 0) {
        state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 50;
        state[0x11] += *(int *)(node[0] + 0x2c);
        if (state[0x1d] != 0 && state[0x1e] < 8) {
            func_ov107_020c9264(*state, 0x26, 1);
            state[0x11] = 0;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020d161c);
            return;
        }
        func_ov107_020c9264(*state, 0x1c, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x3a8), 0x15, 0);
        VEC_Set((Vec3 *)(*state + 0x64), 0, 0x1800, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020d1738);
        return;
    }
    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 8;
    target = state[0x17] = func_ov107_020cab14(*state, 0);
    if (target != 0) {
        owner = *state;
        func_0203cd7c(&m, (Vec3 *)(target + 0x74), (Vec3 *)(owner + 0x74), &data_02042264);
        func_0202ea48((Quat *)(state + 0xb), &m);
        VEC_Subtract((void *)(target + 0x74), (void *)(owner + 0x74), (Vec3 *)(state + 0x1a));
        func_01ff8d18((Vec3 *)(state + 0x1a), (Vec3 *)(state + 0x1a));
    } else {
        *(Vec3 *)(state + 0x1a) = data_02041dc8;
    }
}
