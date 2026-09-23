/* Lunge tick: the +0x5c speed eases a fifth of the way towards 1.0 and the forward unit vector of
 * the +0x38 rotation (data_02042258) scaled by it becomes the +0xc velocity. A 2.0 sphere around the
 * owner's +0x3ec part point (+0x14), moved by that velocity, sweeps the actor list: every entity
 * whose +2 id bit is clear in the +0x69 mask is pushed 1.0 away from the centre, never downwards
 * (kind 1); on acceptance the 14-byte message data_ov273_020d6ac2 carries its +0x74 point to the
 * owner's +0x24 hook, its bit is set and reaction 0x162 mode 7 fires there. The +0x1c distance
 * accumulates the speed; past 16.0 animation 6 plays and the tick hands over to the retreat tick
 * func_ov273_020d3834. */
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

extern const Vec3 data_02042258;
extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, void *out);
extern void VEC_Add(const void *a, const void *b, void *out);
extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov273_020d6ac2;
extern void func_ov273_020d3834(int *node);

void func_ov273_020d3568(int *node)
{
    int *state = (int *)node[1];
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    Vec3 dir;
    Sphere sphere;
    int hits[4];
    Vec3 push;
    int n;
    int i;

    state[0x17] += (0x1000 - state[0x17]) / 5;
    func_0202f384(&dir, state + 0xe, &data_02042258);
    func_01ff8d18(&dir, &dir);
    func_01ffa724(state[0x17], &dir, state + 3);
    VEC_Add((void *)(*(int *)(*state + 0x3ec) + 0x14), state + 3, &sphere.center);
    sphere.nRadius = 0x2000;
    n = func_ov107_020c8eb8(*state, &sphere, hits);
    for (i = 0; i < n; i++) {
        Cmd14 msg;

        if ((*((u8 *)state + 0x69) & (1 << *(u16 *)(hits[i] + 2))) != 0) {
            continue;
        }
        VEC_Subtract((void *)(hits[i] + 0x74), &sphere.center, &push);
        if (push.y < 0) {
            push.y = 0;
        }
        func_01ff8d18(&push, &push);
        func_01ffa724(0x1000, &push, &push);
        if (func_ov107_020ca918(hits[i], *state, *state, 1, &push, 0) == 0) {
            continue;
        }
        msg = data_ov273_020d6ac2;
        PACK(msg, scratchX, *(Fx32 *)(hits[i] + 0x74), 5);
        PACK(msg, scratchY, *(Fx32 *)(hits[i] + 0x78), 8);
        PACK(msg, scratchZ, *(Fx32 *)(hits[i] + 0x7c), 11);
        if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
        }
        *((u8 *)state + 0x69) |= 1 << *(u16 *)(hits[i] + 2);
        func_ov107_020c5af8(*state, 0x162, 7, (void *)(hits[i] + 0x74));
    }
    state[7] += state[0x17];
    if (state[7] <= 0x10000) {
        return;
    }
    func_ov107_020c9264(*state, 6, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov273_020d3834);
}
