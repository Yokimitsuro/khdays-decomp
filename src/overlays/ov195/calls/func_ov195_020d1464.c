/* Charge tick of the ov194 enemy (x3: ov194/195/196). Until the +0x53 one-shot fires,
 * the +0x54 timer accumulates and past 0xccc reaction 0x134/4 fires at the +0x398 joint's +0x14
 * (+0x53 set). The +0x30 timer accumulates; once it reaches 0x999 the overlay's 0x14-byte
 * message goes out once (+0x50): the heading from the +0x3c position to that joint in its last
 * word and the +0x3c position packed into bytes 5..13. From 0xaaa on, two spheres are swept: the
 * +0x39c joint's +0x14 at radius 0x1300, then that point offset by the overlay's +0x4a38 vector
 * turned by the +0xc yaw at radius 0x1340. Entities whose +0x1b4 kind is not yet in the +0x51
 * mask that accept a kind-0 hit pushed (0x300, flattened) away from the +0x40 position get the
 * overlay's 14-byte message with their +0x74 position (y raised by 0x800) through the actor's
 * +0x24 hook, their mask bit and reaction 0x134/5 at that position. Once the +4 item's +0xad
 * byte clears, animation 1 plays and the d3754 handler takes over.
 *
 * Codegen: the position packs go through Fx32 wrapper copies (ov122_020d12f4 idiom); the hit
 * position is a stack copy with y raised in place; the point counter is a signed char. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;
typedef struct { int m[9]; } Mtx33;
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
struct Msg14 { u16 h[7]; };
struct Msg20 { int w[5]; };

struct Ov269Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov269Owner *self, void *msg, int size);
};

extern void func_ov107_020c5af8(struct Ov269Owner *owner, int a, int id, void *at);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void VEC_Add(const void *a, const void *b, Vec3 *d);
extern int func_ov107_020c8eb8(struct Ov269Owner *owner, Sphere *sphere, int *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020ca918(int hit, struct Ov269Owner *a, struct Ov269Owner *b, int kind, Vec3 *push, int z);
extern void func_ov107_020c9264(struct Ov269Owner *actor, int anim, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern const struct Msg20 data_ov195_020d2be0;
extern const Vec3 data_02042258;
extern void func_0202f384(Vec3 *dst, void *xfm, Vec3 *src);
extern const struct Msg14 data_ov195_020d2bd0;
extern void func_ov195_020d18bc(void);

#define PACK3(msg, base, v) \
    ((u8 *)(msg))[(base)] = (u8)(((u32)(v) >> 0x10 & 0x7f) | ((u32)(v) >> 0x18 & 0x80)); \
    ((u8 *)(msg))[(base) + 1] = (u8)((u32)(v) >> 8); \
    ((u8 *)(msg))[(base) + 2] = (u8)(v)

void func_ov195_020d1464(int *node)
{
    int *state = (int *)node[1];
    struct Ov269Owner *owner;
    Vec3 d;
    struct Msg20 msg20;
    int hits[4];
    Sphere sphere;
    Vec3 off;
    Vec3 push;
    Vec3 raw;
    struct Msg14 msg;
    struct Msg14 tmpl;
    FxVec vStart;
    FxVec vContact;
    s8 nPoint;
    int nHits;
    int i;
    Vec3 *pPos;

    if (*(u8 *)((char *)state + 0x53) == 0) {
        state[0x15] += *(int *)(*node + 0x2c);
        if (state[0x15] > 0xccc) {
            func_ov107_020c5af8((struct Ov269Owner *)*state, 0x134, 4, (char *)*(int *)(*state + 0x398) + 0x14);
            *(u8 *)((char *)state + 0x53) = 1;
        }
    }
    state[0xc] += *(int *)(*node + 0x2c);
    if (*(u8 *)((char *)state + 0x50) == 0 && state[0xc] >= 0x999) {
        msg20 = data_ov195_020d2be0;
        VEC_Subtract((char *)*(int *)(*state + 0x398) + 0x14, (void *)state[0xf], &d);
        msg20.w[4] = func_020050b4(d.x, d.z);
        pPos = (Vec3 *)state[0xf];
        vStart.x = *(Fx32 *)&pPos->x;
        PACK3(&msg20, 5, vStart.x.value);
        vStart.y = *(Fx32 *)&pPos->y;
        PACK3(&msg20, 8, vStart.y.value);
        vStart.z = *(Fx32 *)&pPos->z;
        PACK3(&msg20, 11, vStart.z.value);
        if (((struct Ov269Owner *)*state)->pfnMessage != 0) {
            ((struct Ov269Owner *)*state)->pfnMessage((struct Ov269Owner *)*state, &msg20, 0x14);
        }
        *(u8 *)((char *)state + 0x50) = 1;
    }
    if (state[0xc] >= 0xaaa) {
        nPoint = 0;
        tmpl = data_ov195_020d2bd0;
        do {
            func_0202f384(&off, (char *)*state + 0xa0, (Vec3 *)&data_02042258);
            func_01ff8d18(&off, &off);
            func_01ffa724(nPoint == 0 ? 0x2800 : 0x5000, &off, &off);
            VEC_Add((void *)state[0x10], &off, &sphere.pos);
            sphere.radius = 0x1400;
            nHits = func_ov107_020c8eb8((struct Ov269Owner *)*state, &sphere, hits);
            i = 0;
            if (nHits > 0) {
                do {
                    if (((*(u8 *)((char *)state + 0x51) >> *(u8 *)(hits[i] + 0x1b4)) & 1) == 0) {
                        VEC_Subtract((void *)(hits[i] + 0x74), (void *)state[0x10], &push);
                        push.y = 0;
                        func_01ff8d18(&push, &push);
                        func_01ffa724(0x300, &push, &push);
                        if (func_ov107_020ca918(hits[i], (struct Ov269Owner *)*state, (struct Ov269Owner *)*state, 0, &push, 0) != 0) {
                            msg = tmpl;
                            raw = *(Vec3 *)(hits[i] + 0x74);
                            raw.y += 0x800;
                            vContact.x = *(Fx32 *)&raw.x;
                            PACK3(&msg, 5, vContact.x.value);
                            vContact.y = *(Fx32 *)&raw.y;
                            PACK3(&msg, 8, vContact.y.value);
                            vContact.z = *(Fx32 *)&raw.z;
                            PACK3(&msg, 11, vContact.z.value);
                            if (((struct Ov269Owner *)*state)->pfnMessage != 0) {
                                ((struct Ov269Owner *)*state)->pfnMessage((struct Ov269Owner *)*state, &msg, 0xe);
                            }
                            *(u8 *)((char *)state + 0x51) |= 1 << *(u8 *)(hits[i] + 0x1b4);
                            func_ov107_020c5af8((struct Ov269Owner *)*state, 0x134, 5, &raw);
                        }
                    }
                } while (++i < nHits);
            }
        } while (++nPoint < 2);
    }
    if (*(u8 *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264((struct Ov269Owner *)*state, 1, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov195_020d18bc);
    }
}
