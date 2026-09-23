/* Lunge-bite tick: the +0x1c timer accumulates the frame rate; between 2.67 and 3.0 the step of the
 * owner's +0x3cc head point (+0x14) since the last tick (+0x24) sets a 1.5 sphere 1.5 ahead of the
 * head along it, which sweeps the actor list: every entity in it accepts the step as its push
 * (kind 1) and, on acceptance, the 14-byte message data_ov277_020d36ec carries the point of the
 * sphere's surface towards it to the owner's +0x24 hook. The head point is then remembered in +0x24.
 * Once the +0x30 idle byte clears, animation 2 plays once, +0x12, +0x1c and +0x20 clear and the
 * tick hands over to func_ov277_020d00c8. */
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

extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, void *out);
extern void VEC_Add(const void *a, const void *b, void *out);
extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov277_020d36ec;
extern void func_ov277_020d00c8(int *node);

void func_ov277_020cfe28(int *node)
{
    int *state = (int *)node[1];
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int hits[4];
    Sphere sphere;
    Vec3 step;
    Vec3 dir;
    Vec3 point;
    int n;
    int i;

    state[7] += *(int *)(node[0] + 0x2c);
    n = state[7];
    if (n >= 0x2aaa && n < 0x3000) {
        VEC_Subtract((void *)(*(int *)(*state + 0x3cc) + 0x14), state + 9, &step);
        func_01ff8d18(&step, &dir);
        func_01ffa724(0x1800, &dir, &dir);
        VEC_Add((void *)(*(int *)(*state + 0x3cc) + 0x14), &dir, &sphere.center);
        sphere.nRadius = 0x1800;
        n = func_ov107_020c8eb8(*state, &sphere, hits);
        for (i = 0; i < n; i++) {
            Cmd14 msg;

            if (func_ov107_020ca918(hits[i], *state, *state, 1, &step, 0) == 0) {
                continue;
            }
            msg = data_ov277_020d36ec;
            VEC_Subtract((void *)(hits[i] + 0x74), &sphere.center, &point);
            func_01ff8d18(&point, &point);
            func_01ffa724(sphere.nRadius, &point, &point);
            VEC_Add(&sphere.center, &point, &point);
            PACK(msg, scratchX, *(Fx32 *)&point.x, 5);
            PACK(msg, scratchY, *(Fx32 *)&point.y, 8);
            PACK(msg, scratchZ, *(Fx32 *)&point.z, 11);
            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
            }
        }
    }
    *(Vec3 *)(state + 9) = *(Vec3 *)(*(int *)(*state + 0x3cc) + 0x14);
    if (*(u8 *)state[0xc] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 2, 1);
    *(short *)((u8 *)state + 0x12) = 0;
    state[7] = 0;
    state[8] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov277_020d00c8);
}
