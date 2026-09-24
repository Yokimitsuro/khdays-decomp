/* Spin-attack tick of the ov238 enemy: the +0x20 clock runs up at the owner's rate; past 0.46, while a
 * +0x2c charge remains, message 6 goes to the +8 target and the charge is spent. Sound cues 2/5 at
 * tick 5 and 1/4 at tick 15 play (020d0f0c). The overlay's offset is turned by the +0x18 yaw, the
 * push is 1.25 along that yaw, and the sweep sphere (radius 1.4) sits on the +0x3ec bone lifted by
 * the offset's depth; a hit (020d0910) fires reaction 0x51 at the owner. The +0x3e0 bone's point
 * steers the owner (020d07f0). On landing (+0x17a bit 1) message 7 and phase 7 (020d244c) follow.
 * Once the +4 rig is idle, a pending +0x2d hand-over runs 020d2020, otherwise the clock resets,
 * +0x31 becomes 2 and message 7 / phase 7 follow. */
typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { Vec3 pos; int nRadius; } Sphere;
struct b2 { unsigned char b0 : 1, b1 : 1; };

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov238_020d0f0c(int *node, int ticks, int cue, int variant);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(Vec3 *v, Mtx33 *m, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov238_020d0910(int *node, Sphere *sphere, int a, Vec3 *push, int b, int c, int d);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov238_020d07f0(int *node, Vec3 *vec);
extern void func_ov238_020d0f54(int *node, int param_2, int param_3, int param_4, void *cb);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov238_020d2020(void);
extern void func_ov238_020d244c(void);
extern const short data_0203d210[];
extern const Vec3 data_ov238_020d36d8;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov238_020d212c(int *node)
{
    int *state = (int *)node[1];
    Sphere sphere;
    Vec3 push;
    Vec3 offset = data_ov238_020d36d8;
    Mtx33 mtx;
    unsigned int idx;

    state[8] += *(int *)(node[0] + 0x2c);
    if (state[8] >= 0x770 && *((unsigned char *)state + 0x2c) == 1) {
        func_ov107_020c0b90(*state, 6, *(Vec3 *)state[2], 1);
        *((unsigned char *)state + 0x2c) -= 1;
    }
    func_ov238_020d0f0c(node, 5, 2, 5);
    func_ov238_020d0f0c(node, 0xf, 1, 4);
    idx = ANG2IDX(state[6]);
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33(&offset, &mtx, &offset);
    push.x = data_0203d210[ANG2IDX(state[6]) * 2];
    push.y = 0;
    push.z = data_0203d210[ANG2IDX(state[6]) * 2 + 1];
    func_01ffa724(0x1400, &push, &push);
    sphere.nRadius = 0x1680;
    sphere.pos = *(Vec3 *)(*(int *)(*state + 0x3ec) + 0x14);
    sphere.pos.z += offset.z;
    if (func_ov238_020d0910(node, &sphere, 0, &push, 0, 1, 2) != 0) {
        func_ov107_020c5af8(*state, 0, 0x51, (void *)(*state + 0x74));
    }
    func_ov238_020d07f0(node, (Vec3 *)(*(int *)(*state + 0x3e0) + 0x2c));
    if (((struct b2 *)(*state + 0x17a))->b1 != 0) {
        func_ov107_020c0b90(*state, 7, *(Vec3 *)state[2], 0);
        func_ov238_020d0f54(node, 7, 3, 0, func_ov238_020d244c);
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (*((unsigned char *)state + 0x2d) != 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov238_020d2020);
        return;
    }
    state[8] = 0;
    *((unsigned char *)state + 0x31) = 2;
    func_ov107_020c0b90(*state, 7, *(Vec3 *)state[2], 0);
    func_ov238_020d0f54(node, 7, 3, 0, func_ov238_020d244c);
}
