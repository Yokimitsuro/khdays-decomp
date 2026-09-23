/* Shockwave tick of the ov273 enemy: the +0x1c timer accumulates the frame rate. At 0xaaa (phase
 * 0 of +0x68) the ground note with the actor's position (raised to 0.125 above its +0x13c base)
 * goes out through the +0x24 hook and reaction 0x162/9 fires there. In phase 1, until 0x14cc, a
 * cylinder at the actor's feet (+0.5) grows its +0x60 radius a fifth of the way to 6.5 per tick
 * (swept at three times it) and every entity not yet in the +0x69 mask that accepts a kind-3 hit pushed
 * 1.0 outwards and 0.5 up gets the overlay's 14-byte message with its +0x74 position, its mask
 * bit and reaction 0/0x53 there. Once the +8 flag byte clears the next move is 6. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { Vec3 pos; Vec3 axis[3]; int radius; int flag; } Cyl;
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
struct Msg14 { u16 h[7]; };

struct Ov273Actor {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov273Actor *self, void *msg, int size);
};

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_ov107_020c8fd0(int owner, Cyl *cyl, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void func_0203c634(int *node, int slot, void *cb);
extern const struct Msg14 data_ov273_020d6ad0;
extern const struct Msg14 data_ov273_020d6ade;
extern const Vec3 data_02042270;
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;

#define PACK3(msg, base, v) \
    ((u8 *)(msg))[(base)] = (u8)(((u32)(v) >> 0x10 & 0x7f) | ((u32)(v) >> 0x18 & 0x80)); \
    ((u8 *)(msg))[(base) + 1] = (u8)((u32)(v) >> 8); \
    ((u8 *)(msg))[(base) + 2] = (u8)(v)

void func_ov273_020d2be0(int *node)
{
    int *state = (int *)node[1];
    Vec3 at;
    struct Msg14 note;
    int hits[4];
    Cyl cyl;
    Vec3 push;
    struct Msg14 msg;
    struct Msg14 tmpl;
    FxVec vAt;
    FxVec vHit;
    Vec3 *pPos;
    int nHits;
    int i;

    state[7] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x68) == 0 && state[7] >= 0xaaa) {
        {
            note = data_ov273_020d6ad0;
            at = *(Vec3 *)(*state + 0x74);
            at.y = at.y - *(int *)(*state + 0x13c) + 0x200;
            vAt.x = *(Fx32 *)&at.x;
            PACK3(&note, 5, vAt.x.value);
            vAt.y = *(Fx32 *)&at.y;
            PACK3(&note, 8, vAt.y.value);
            vAt.z = *(Fx32 *)&at.z;
            PACK3(&note, 11, vAt.z.value);
            if (((struct Ov273Actor *)*state)->pfnMessage != 0) {
                ((struct Ov273Actor *)*state)->pfnMessage((struct Ov273Actor *)*state, &note, 0xe);
            }
            func_ov107_020c5af8(*state, 0x162, 9, &at);
            *((u8 *)state + 0x68) = 1;
        }
    } else if (*((u8 *)state + 0x68) == 1 && state[7] <= 0x14cc) {
        cyl.pos = *(Vec3 *)(*state + 0x74);
        cyl.pos.y = cyl.pos.y - *(int *)(*state + 0x13c) + 0x800;
        cyl.axis[0] = data_02042270;
        cyl.axis[1] = data_02042258;
        cyl.axis[2] = data_02042264;
        nHits = state[0x18];
        state[0x18] = nHits + (0x6800 - nHits) / 5;
        cyl.radius = state[0x18] * 3;
        cyl.flag = 1;
        nHits = func_ov107_020c8fd0(*state, &cyl, hits);
        i = 0;
        if (nHits > 0) {
            tmpl = data_ov273_020d6ade;
            do {
                if ((*((u8 *)state + 0x69) & (1 << *(u16 *)(hits[i] + 2))) == 0) {
                    VEC_Subtract((void *)(hits[i] + 0x74), &cyl.pos, &push);
                    push.y = 0;
                    func_01ff8d18(&push, &push);
                    func_01ffa724(0x1000, &push, &push);
                    push.y = 0x800;
                    if (func_ov107_020ca918(hits[i], *state, *state, 3, &push, 0) != 0) {
                        msg = tmpl;
                        pPos = (Vec3 *)(hits[i] + 0x74);
                        vHit.x = *(Fx32 *)&pPos->x;
                        PACK3(&msg, 5, vHit.x.value);
                        vHit.y = *(Fx32 *)&pPos->y;
                        PACK3(&msg, 8, vHit.y.value);
                        vHit.z = *(Fx32 *)&pPos->z;
                        PACK3(&msg, 11, vHit.z.value);
                        if (((struct Ov273Actor *)*state)->pfnMessage != 0) {
                            ((struct Ov273Actor *)*state)->pfnMessage((struct Ov273Actor *)*state, &msg, 0xe);
                        }
                        *((u8 *)state + 0x69) |= 1 << *(u16 *)(hits[i] + 2);
                        func_ov107_020c5af8(*state, 0, 0x53, (void *)(hits[i] + 0x74));
                    }
                }
            } while (++i < nHits);
        }
    }
    if (*(u8 *)state[2] != 0) {
        return;
    }
    *(s8 *)(*state + 0x1c7) = 6;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
