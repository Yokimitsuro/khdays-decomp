/* Flight tick of the ov220 enemy: the +0x24 velocity starts as (speed +0x54 times the sine of
 * the +0x4c phase, 0, 1.0), mirrored on x by +0x58, turned by the +0x48 yaw, normalised and
 * scaled by +0x20 plus 0x140 plus a bob taken from the sine of the phase (0xf00 / 4, folded to
 * fixed point). A wall contact (bit 1 of the actor's +0x17a) reflects the facing of the +0xc
 * yaw about the +0x114 contact normal: the reflected direction gives the new +0x48 yaw and
 * redirects the velocity at its current length, and +0x5c latches. A negative distance to the
 * target or a finished idle countdown ends the state; otherwise the +0xc/+0x10 yaws follow
 * the velocity and the phase advances by the +0x50 rate, handing off to the wander state
 * (and running it) once it reaches 0x8000. */
typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
struct Bits17a { unsigned char bit0 : 1, bit1 : 1; };

extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int VEC_DotProduct(Vec3 *a, Vec3 *b);
extern void VEC_Subtract(Vec3 *a, Vec3 *b, Vec3 *d);
extern int func_020050b4(int x, int z);
extern int func_ov220_020d2448(int *node);
extern int func_ov220_020d2384(int *node, int dist);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov220_020d2b08(int *node);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov220_020d2c0c(int *node)
{
    int *state = (int *)node[1];
    Mtx33 mtx;
    Vec3 n;
    Vec3 back;
    Vec3 refl;
    int bob;
    int dist;
    int len;
    unsigned int idx;

    state[9] = state[0x15] * data_0203d210[(state[0x13] >> 4) * 2] / 0x1000;
    state[10] = 0;
    state[0xb] = 0x1000;
    if (*(unsigned char *)(state + 0x16) != 0) {
        state[9] *= -1;
    }
    idx = ANG2IDX(state[0x12]);
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((Vec3 *)(state + 9), &mtx, (Vec3 *)(state + 9));
    func_01ff8d18((Vec3 *)(state + 9), (Vec3 *)(state + 9));
    bob = data_0203d210[(state[0x13] >> 4) * 2] * 0xf00 / 4;
    if (bob < 0) {
        bob = -bob;
    }
    func_01ffa724(bob / 0x1000 + 0x140 + state[8], (Vec3 *)(state + 9), (Vec3 *)(state + 9));
    if (((struct Bits17a *)(*state + 0x17a))->bit1 != 0) {
        n = *(Vec3 *)(*state + 0x114);
        idx = ANG2IDX(state[3]);
        back.x = -data_0203d210[idx * 2];
        back.y = 0;
        back.z = -data_0203d210[idx * 2 + 1];
        func_01ffa724(VEC_DotProduct(&back, &n) << 1, &n, &refl);
        VEC_Subtract(&refl, &back, &refl);
        func_01ff8d18(&refl, &refl);
        state[0x12] = func_020050b4(refl.x, refl.z);
        len = func_01ff8d18((Vec3 *)(state + 9), (Vec3 *)(state + 9));
        func_01ffa724(len, &refl, (Vec3 *)(state + 9));
        state[0x17] = 1;
    }
    dist = func_ov220_020d2448(node);
    if (dist < 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (func_ov220_020d2384(node, dist) != 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[4] = state[3] = func_020050b4(state[9], state[0xb]);
    state[0x13] += *(int *)(*node + 0x2c) * state[0x14] / 0x1000;
    if (state[0x13] < 0x8000) {
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov220_020d2b08);
    func_ov220_020d2b08(node);
}
