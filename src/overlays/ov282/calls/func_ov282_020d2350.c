/* Burst tick of the ov282 enemy (the ov210/ov211 burst tick). The +0x2c timer accumulates the owner's
 * rate; between 0.5 and 0xaaa a sphere at the +4 point, its radius growing to 0x4cc9 with the
 * timer's fraction of 0xaaa, is swept over the actor list: every entity is pushed 0.25 along the
 * unit direction from the centre (kind 2) and on acceptance the overlay's 14-byte message
 * (data_ov282_020d4748, low nibble of byte 4 = 6) carries its +0x74 point to the owner's +0x24
 * hook and reaction 0/0x53 fires there. Once the +0xc idle byte clears, the +0x6c think timer is
 * re-armed between the actor's +0x224 and +0x228, sub-state 2 is requested and the action ends. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
struct Nib { u8 lo : 4, hi : 4; };
typedef struct { u16 id; u8 kind; u8 cmd; struct Nib flag; u8 pos[9]; } Cmd14;
typedef struct { Vec3 pos; int nRadius; } Sphere;

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))


#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int FX_Inv(int num, int den);
extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern int func_02023eb4(int bound);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov282_020d4748;

void func_ov282_020d2350(int *node)
{
    int *state = (int *)node[1];
    Sphere sphere;
    int hits[4];
    Vec3 push;
    Cmd14 msg;
    Cmd14 tmpl;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int n;
    int i;
    int t;
    int lo;
    int d;

    state[0xb] += *(int *)(*node + 0x2c);
    if (state[0xb] >= 0x800 && state[0xb] <= 0xaaa) {
        t = FX_Inv(state[0xb], 0xaaa);
        if (t > 0x1000) {
            t = 0x1000;
        }
        sphere.pos = *(Vec3 *)state[1];
        sphere.nRadius = FX_MUL(t, 0x4cc9);
        n = func_ov107_020c8eb8(*state, &sphere, hits);
        i = 0;
        if (n > 0) {
            tmpl = data_ov282_020d4748;
            do {
                VEC_Subtract((void *)(hits[i] + 0x74), &sphere.pos, &push);
                func_01ff8d18(&push, &push);
                func_01ffa724(0x400, &push, &push);
                if (func_ov107_020ca918(hits[i], *state, *state, 2, &push, 0) != 0) {
                    msg = tmpl;
                    PACK(msg, scratchX, *(Fx32 *)(hits[i] + 0x74), 5);
                    PACK(msg, scratchY, *(Fx32 *)(hits[i] + 0x78), 8);
                    PACK(msg, scratchZ, *(Fx32 *)(hits[i] + 0x7c), 11);
                    msg.flag.lo = 6;
                    msg.flag.hi = 0;
                    if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                        (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
                    }
                    func_ov107_020c5af8(*state, 0, 0x53, (void *)(hits[i] + 0x74));
                }
            } while (++i < n);
        }
    }
    if (*(u8 *)state[3] != 0) {
        return;
    }
    lo = *(int *)(*state + 0x224);
    d = *(int *)(*state + 0x228) - lo;
    if (d < 0) {
        d = -d;
    }
    state[0x1b] = func_02023eb4(d + 1) + lo;
    *(u8 *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
