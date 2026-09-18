/* Approach tick of the ov219 enemy (and its byte-identical twin): a wall contact (bit 1 of the
 * actor's +0x17a) requests sub-state 5 and ends the state, as does a negative distance to the
 * target. Otherwise the +0x24 velocity is the forward vector turned by the +0x10 yaw plus 180
 * degrees offset by 77 degrees to the side chosen by +0x48, at speed +0x20 plus 0x200 plus a
 * bob taken from the sine of the +0x4c phase (0xc00 / 3, folded to fixed point); the phase
 * advances by 24 turns per second (wrapped to 16 bits), the +0xc/+0x10 yaws follow the velocity
 * and, after 0x1000 of the +0x14 clock, the tick hands off to the wander state and runs it. */
typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
struct Bits17a { unsigned char bit0 : 1, bit1 : 1; };

extern void func_0203c634(int *node, int slot, void *cb);
extern int func_ov219_020d05f0(int *node);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_020050b4(int x, int z);
extern void func_ov219_020d0c70(int *node);
extern short data_0203d210[];
extern const Vec3 data_02042258;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov219_020d0d24(int *node)
{
    int *state = (int *)node[1];
    Mtx33 mtx;
    int deg;
    int angle;
    int bob;
    unsigned int idx;

    if (((struct Bits17a *)(*state + 0x17a))->bit1 != 0) {
        *(unsigned char *)(*state + 0x1c7) = 5;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (func_ov219_020d05f0(node) < 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    deg = *(unsigned char *)(state + 0x12) != 0 ? -0x4d : 0x4d;
    angle = state[4];
    angle += (deg + 0xb4) * 0x3244 / 180;
    idx = ANG2IDX(angle);
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33(&data_02042258, &mtx, (Vec3 *)(state + 9));
    bob = data_0203d210[(state[0x13] >> 4) * 2] * 0xc00 / 3;
    if (bob < 0) {
        bob = -bob;
    }
    func_01ffa724(bob / 0x1000 + 0x200 + state[8], (Vec3 *)(state + 9), (Vec3 *)(state + 9));
    state[0x13] += *(int *)(*node + 0x2c) * 0x18000 / 0x1000;
    state[0x13] &= 0x7fff;
    state[4] = state[3] = func_020050b4(state[9], state[0xb]);
    state[5] += *(int *)(*node + 0x2c);
    if (state[5] >= 0x1000) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov219_020d0c70);
        func_ov219_020d0c70(node);
    }
}
