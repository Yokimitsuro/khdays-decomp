/* Stomp tick: until the +0x74 flag is set the +0x18 timer accumulates the frame rate; past 0.23
 * the flag is set and, while the actor's +0x3d0 hit points are positive, the actor's +0x24 hook
 * receives note 6 of data_ov236_020d6430, reaction 0x127 mode 0xb fires at the +0x3c0 foot's +4
 * point and a sphere there, of twice the foot's +0x90 radius, sweeps the actor list: every entity
 * in it is pushed 0.375 away horizontally (kind 1, on behalf of the +0x384 rider); on acceptance the
 * 14-byte message data_ov236_020d6454 carries its +0x74 point raised by 0.5 and its +0x1b4 byte to
 * the rider's +0x24 hook, and reaction 0x127 mode 0xd fires at that raised point. Once the +0x20
 * idle byte clears, pose 9 is requested. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { Vec3 center; int nRadius; } Sphere;
typedef struct { u16 lo; u16 hi; } Cmd4;

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, void *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd4 data_ov236_020d6430[];
extern const Cmd14 data_ov236_020d6454;

void func_ov236_020d4d84(int *node)
{
    Cmd4 note;
    int *state = (int *)node[1];
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    Sphere sphere;
    int hits[4];
    Vec3 push;
    Vec3 raw;
    int n;
    int i;

    if (*((u8 *)state + 0x74) == 0) {
        state[6] += *(int *)(node[0] + 0x2c);
        if (state[6] > 0x3bb) {
            *((u8 *)state + 0x74) = 1;
            if (*(short *)(*state + 0x3d0) > 0) {
                {
                    Cmd4 *p = &note;

                    p->hi = data_ov236_020d6430[6].hi;
                    p->lo = data_ov236_020d6430[6].lo;
                    if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
                        (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, p, 4);
                    }
                }
                func_ov107_020c5af8(*state, 0x127, 0xb, (void *)(**(int **)(*state + 0x3c0) + 4));
                sphere.center = *(Vec3 *)(**(int **)(*state + 0x3c0) + 4);
                n = *(int *)(**(int **)(*state + 0x3c0) + 0x90);
                sphere.nRadius = n << 1;
                n = func_ov107_020c8eb8(*state, &sphere, hits);
                for (i = 0; i < n; i++) {
                    Cmd14 msg;

                    VEC_Subtract((void *)(hits[i] + 0x74), &sphere.center, &push);
                    push.y = 0;
                    func_01ff8d18(&push, &push);
                    func_01ffa724(0x600, &push, &push);
                    if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x384), 1, &push, 0) == 0) {
                        continue;
                    }
                    msg = data_ov236_020d6454;
                    raw = *(Vec3 *)(hits[i] + 0x74);
                    raw.y += 0x800;
                    PACK(msg, scratchX, *(Fx32 *)&raw.x, 5);
                    PACK(msg, scratchY, *(Fx32 *)&raw.y, 8);
                    PACK(msg, scratchZ, *(Fx32 *)&raw.z, 11);
                    msg.flag = *(u8 *)(hits[i] + 0x1b4);
                    if (*(void (**)(int, Cmd14 *, int))(*(int *)(*state + 0x384) + 0x24) != 0) {
                        (*(void (**)(int, Cmd14 *, int))(*(int *)(*state + 0x384) + 0x24))(*(int *)(*state + 0x384), &msg, 0xe);
                    }
                    func_ov107_020c5af8(*state, 0x127, 0xd, &raw);
                }
            }
        }
    }
    if (*(u8 *)state[8] != 0) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 9;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
