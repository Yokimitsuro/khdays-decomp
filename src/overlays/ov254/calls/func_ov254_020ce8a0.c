/* Pursuit tick of the ov254 boss. A pending +0x7c grab is dropped (020cd5f4) when the owner's
 * +0x4e0 partner exists. While grabbing, the boss heads (0.25) for 7.7 above the +0x3dc target's
 * +0x190 point and the +0x64 grab meter fills by the flat speed (clamped to +0x68). Otherwise it
 * turns towards the +0x18 goal and moves along the rig's +0x2c step turned by that heading, at a
 * speed easing with the remaining distance (0.75 x 1/8..1 over 10.0), the climb +0x60 (clamped to
 * 2.5 while +0x78 flies) taken off the step, and inside 10.0 it lands (020cd750). On the ground it
 * throws the first idle +0x4ac shard every second 7.7 ahead along the +0x30 heading, keeps climbing
 * by +0x60 (which decays by 6 % per 1/30 s), and a world hit of its +0x408 sphere zeroes the step
 * and keeps its length in +0x60. Once the +4 rig is idle: a flying boss at 60 % stamina, a full
 * grab meter or an expired +0x3c timer ends the move (pose +0x75+2, rig motion +0x76+2 looping,
 * flight extras) into 020cee30; otherwise pose +0x75+1 plays and, with the rig idle, rig motion
 * +0x76+1 follows (the climb resets while flying). */
typedef unsigned char u8;
typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { Vec3 pos; int nRadius; } Sphere;
struct Ov254 {
    char pad000[0x4ac];
    int debris[10];         /* +0x4ac */
};

extern void func_ov254_020cd5f4(int *state, int a, int b);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern int func_020050b4(int x, int z);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int VEC_Mag(Vec3 *v);
extern int FX_Inv(int num, int den);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(Vec3 *v, Mtx33 *m, Vec3 *d);
extern void func_ov254_020cd750(int *state);
extern void VEC_Add(void *a, void *b, Vec3 *d);
extern void func_ov254_020d2ab8(int shard, Vec3 *at);
extern int func_ov107_020ca414(int collision, Sphere *sphere, int *out);
extern void func_ov107_020c9264(int owner, int pose, int loop);
extern void func_ov107_020c9ee8(int rig, int motion, int mode);
extern void func_ov254_020d4d34(int helper);
extern void func_ov254_020d532c(int helper);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov254_020cee30(void);
extern const short data_0203d210[];
extern const Vec3 data_02041dc8;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

static inline void VecSet(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov254_020ce8a0(int *node)
{
    int *state = (int *)node[1];
    Vec3 aim;
    Mtx33 mtx;
    Vec3 d;
    Sphere sph;
    int hits[12];
    Vec3 v;
    int dist;
    int speed;
    int rem;
    long i;
    int world;
    int done;
    unsigned int idx;

    if (state[0x1f] != 0 && *(int *)(*state + 0x4e0) != 0) {
        func_ov254_020cd5f4(state, 0, 0);
        state[0x1f] = 0;
    }
    if (state[0x1f] != 0) {
        int meter;
        int max;

        aim = *(Vec3 *)(*(int *)(*state + 0x3dc) + 0x190);
        aim.y += 0x7b31;
        VEC_Subtract(&aim, (void *)state[2], &aim);
        func_01ff8d18(&aim, &aim);
        state[0xd] = func_020050b4(aim.x, aim.z);
        func_01ffa724(0x400, &aim, (Vec3 *)(state + 3));
        VecSet(&aim, state[3], 0, state[5]);
        state[0x19] += VEC_Mag(&aim);
        meter = state[0x19];
        max = state[0x1a];
        if (meter <= max) {
            if (meter < 0) {
                meter = 0;
            }
            max = meter;
        }
        state[0x19] = max;
    } else {
        int f;

        VEC_Subtract((Vec3 *)(state + 6), (void *)state[2], &d);
        d.y = 0;
        dist = func_01ff8d18(&d, &d);
        state[0xd] = func_020050b4(d.x, d.z);
        f = FX_Inv(dist, 0xa000);
        if (f > 0x1000) {
            f = 0x1000;
        } else if (f < 0x200) {
            f = 0x200;
        }
        speed = FX_MUL(f, 0xc00);
        idx = ANG2IDX(state[0xd]);
        MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
        MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x430) + 0x2c), &mtx, (Vec3 *)(state + 3));
        if (state[0x1e] != 0) {
            int climb;

            state[0x18] -= state[4];
            climb = state[0x18];
            if (climb > 0x2800) {
                climb = 0x2800;
            } else if (climb < -0x2800) {
                climb = -0x2800;
            }
            state[0x18] = climb;
        }
        func_01ffa724(speed, (Vec3 *)(state + 3), (Vec3 *)(state + 3));
        state[4] = 0;
        if (dist <= 0xa000) {
            func_ov254_020cd750(state);
        }
    }
    if (state[0x1e] == 0) {
        world = *(int *)(*state + 4);
        state[0x11] += *(int *)(node[0] + 0x2c);
        if (state[0x11] >= 0x1000) {
            for (i = 0; i < 5; i++) {
                if (*(int *)(((struct Ov254 *)*state)->debris[i] + 0x390) == 0) {
                    idx = ANG2IDX(state[0xc]);
                    v.x = data_0203d210[idx * 2];
                    v.y = 0;
                    v.z = data_0203d210[idx * 2 + 1];
                    func_01ffa724(0x7b31, &v, &v);
                    VEC_Add(&v, (void *)state[2], &v);
                    func_ov254_020d2ab8(((struct Ov254 *)*state)->debris[i], &v);
                    break;
                }
            }
            state[0x11] = 0;
        }
        state[4] += state[0x18];
        for (rem = *(int *)(node[0] + 0x2c); rem > 0; rem -= 0x88) {
            state[0x18] = FX_MUL(state[0x18], 0xf00);
        }
        VEC_Add((void *)(*(int *)(*state + 0x408) + 0x14), (Vec3 *)(state + 3), &sph.pos);
        sph.nRadius = 0x7b31;
        v = data_02041dc8;
        if (func_ov107_020ca414(*(int *)(world + 0x7c), &sph, hits) > 0) {
            state[0x18] = VEC_Mag((Vec3 *)(state + 3));
            state[3] = state[5] = 0;
        }
    }
    if (*(u8 *)(state[1] + 0xad) == 0) {
        done = 0;
        if (state[0x1e] != 0 &&
            *(short *)(*state + 0x21a) <= *(short *)(*state + 0x218) * 0x3c / 100) {
            *(u8 *)(*state + 0x1c7) = 8;
            done = 1;
        } else if ((state[0x1f] != 0 && state[0x19] >= state[0x1a]) ||
                   (state[0x1f] == 0 && state[0xf] <= 0)) {
            done = 1;
        }
        if (done != 0) {
            func_ov107_020c9264(*state, *((u8 *)state + 0x75) + 2, 0);
            func_ov107_020c9ee8(*(int *)(*state + 0x430), *((u8 *)state + 0x76) + 2, 1);
            if (state[0x1e] != 0) {
                func_ov254_020d4d34(*(int *)(*state + 0x460));
                func_ov254_020d532c(*(int *)(*state + 0x464));
                func_ov107_020c0b90(*state, 0xc, data_02041dc8, 0);
            }
            func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020cee30);
            return;
        }
        func_ov107_020c9264(*state, *((u8 *)state + 0x75) + 1, 0);
    }
    {
        int rig = *(int *)(*state + 0x430);

        if (*(u8 *)(*(int *)(rig + 0x3c) + 0xad) != 0) {
            return;
        }
        func_ov107_020c9ee8(rig, *((u8 *)state + 0x76) + 1, 0);
    }
    if (state[0x1e] != 0) {
        state[0x18] = 0;
    }
}
