/* Dive tick: the +0x2c timer accumulates the frame rate and the +0x20 velocity is 0.375 along the
 * forward axis of the +4 orientation (data_02042270). Past 0.5, while the +0x14 lock is clear, the
 * rider's nearest target (func_ov244_020cd300) becomes the actor's +0x390 and the orientation turns
 * towards it by 0.15 of the frame step x 30 (quaternion slerp, renormalised). Grounded or blocked
 * (+0x17a bits 0/1), the dive ends: the message data_ov244_020d36ea carries the +0x1c point
 * lowered by 0.56 to the +0x24 hook, pose 0 is requested and reaction 0x113 mode 0x10 fires there.
 * Otherwise a 0.5 sphere one step ahead of the +0x1c point sweeps the actor list on behalf of the
 * +0x384 rider: the first entity that accepts the velocity as its push (kind 2) gets the message
 * data_ov244_020d36dc, flag 0x10, with the point of its +0x80 radius towards the actor, reaction
 * 0x113 mode 0xf fires and pose 0 is requested. Past 10.0 the dive gives up (pose 0). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { Vec3 center; int nRadius; } Sphere;

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

typedef struct { int w[4]; } Quat;
struct Bits17a { unsigned char b0 : 1, b1 : 1; };

extern const Vec3 data_02042270;
extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, void *out);
extern int func_ov244_020cd300(int rider);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0202f55c(void *out, int t, void *a, Quat *b);
extern void func_0202f4a4(void *out, void *in);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void VEC_Add(const void *a, const void *b, void *out);
extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, void *push, int z);
extern const Cmd14 data_ov244_020d36ea;
extern const Cmd14 data_ov244_020d36dc;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov244_020cdb54(int *node)
{
    int *state = (int *)node[1];
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    Fx32 scratch2Z;
    Fx32 scratch2Y;
    Fx32 scratch2X;
    Vec3 dir;
    Quat turn;
    Vec3 toTarget;
    Vec3 raw;
    Cmd14 landMsg;
    Sphere sphere;
    int hits[4];
    Vec3 point;
    Cmd14 msg;
    int n;
    int i;

    state[0xb] += *(int *)(node[0] + 0x2c);
    func_0202f384(&dir, state + 1, &data_02042270);
    func_01ff8d18(&dir, &dir);
    func_01ffa724(0x600, &dir, state + 8);
    if (state[0xb] > 0x800) {
        if (state[5] == 0) {
            *(int *)(*state + 0x390) = func_ov244_020cd300(*(int *)(*state + 0x384));
            if (*(int *)(*state + 0x390) != 0) {
                VEC_Subtract((void *)(*(int *)(*state + 0x390) + 0x74), (void *)state[7], &toTarget);
                func_01ff8d18(&toTarget, &toTarget);
                func_0202ed60(&turn, &data_02042270, &toTarget);
                func_0202f55c(state + 1, FX_Mul(*(int *)(node[0] + 0x2c) * 30, 0x266), state + 1, &turn);
                func_0202f4a4(state + 1, state + 1);
            }
        }
        if (((struct Bits17a *)(*state + 0x17a))->b0 || ((struct Bits17a *)(*state + 0x17a))->b1) {
            landMsg = data_ov244_020d36ea;
            raw = *(Vec3 *)state[7];
            raw.y -= 0x900;
            PACK(landMsg, scratchX, *(Fx32 *)&raw.x, 5);
            PACK(landMsg, scratchY, *(Fx32 *)&raw.y, 8);
            PACK(landMsg, scratchZ, *(Fx32 *)&raw.z, 11);
            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &landMsg, 0xe);
            }
            *(u8 *)(*state + 0x1c7) = 0;
            func_ov107_020c5af8(*state, 0x113, 0x10, (void *)state[7]);
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    VEC_Add((void *)state[7], state + 8, &sphere.center);
    sphere.nRadius = 0x800;
    n = func_ov107_020c8eb8(*(int *)(*state + 0x384), &sphere, hits);
    for (i = 0; i < n; i++) {
        if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x384), 2, state + 8, 0) == 0) {
            continue;
        }
        msg = data_ov244_020d36dc;
        VEC_Subtract((void *)state[7], (void *)(hits[i] + 0x74), &point);
        func_01ff8d18(&point, &point);
        func_01ffa724(*(int *)(hits[i] + 0x80), &point, &point);
        VEC_Add((void *)(hits[i] + 0x74), &point, &point);
        PACK(msg, scratch2X, *(Fx32 *)&point.x, 5);
        PACK(msg, scratch2Y, *(Fx32 *)&point.y, 8);
        PACK(msg, scratch2Z, *(Fx32 *)&point.z, 11);
        msg.flag = 0x10;
        if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
        }
        func_ov107_020c5af8(*state, 0x113, 0xf, (void *)state[7]);
        *(u8 *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0xb] <= 0xa000) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
