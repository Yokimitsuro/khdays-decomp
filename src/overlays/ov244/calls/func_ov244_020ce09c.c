/* Leap-to-core tick: the +0x2c timer accumulates the frame rate against the +0x30 duration and the
 * actor's +0xa0 position follows the cubic Hermite blend of the +0x4c start, the +0x384 owner's
 * +0x3bc joint (+0x14) and the +0x34 / +0x40 tangents. On arrival an armed owner (+0x60 low byte
 * bit 0) receives hit packet 4 (the owner's +0x29c damage, the actor's +0x258 id, the owner's
 * +0x39c node) from the +0x18 source, the kind-0x30 message with the point 3.0 from the +0x1c
 * anchor towards the player goes out through the actor's +0x24 hook, reaction 0x113/0xf fires at
 * the arrival point, the move request clears and the owner's +0x420 level goes up by one. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
struct Msg14 { u16 h[7]; };
typedef struct { u16 lo : 8; u16 hi : 8; } Hw60;
struct Level { int n : 4; };

struct HitPacket {
    u32 flagsLo : 16;
    u32 flagsHi : 16;
    Vec3 normal;
    int field_10 : 16;
    int field_12 : 16;
    int field_14 : 16;
    int field_16 : 16;
    void *field_18;
    signed char field_1c;
    u8 pad01d[3];
    int field_20;
    u32 flags24Lo : 16;
    u32 flags24Hi : 16;
    int field_28;
};

struct Ov244Actor {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov244Actor *self, void *msg, int size);
};

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int FX_Inv(int num, int den);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const void *a, const void *b, void *out);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_0203ca30(int srt, Vec3 *pos);
extern int func_ov107_020c5cfc(int other, int source, struct HitPacket *packet);
extern int *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern const struct Msg14 data_ov244_020d36f8;

#define PACK3(msg, base, v) \
    ((u8 *)(msg))[(base)] = (u8)(((u32)(v) >> 0x10 & 0x7f) | ((u32)(v) >> 0x18 & 0x80)); \
    ((u8 *)(msg))[(base) + 1] = (u8)((u32)(v) >> 8); \
    ((u8 *)(msg))[(base) + 2] = (u8)(v)

void func_ov244_020ce09c(int *node)
{
    int *state = (int *)node[1];
    Vec3 target;
    Vec3 acc;
    Vec3 tmp;
    int t;
    int t2;
    int t3;
    int t2x3;

    target = *(Vec3 *)(*(int *)(*(int *)(*state + 0x384) + 0x3bc) + 0x14);
    state[0xb] += *(int *)(node[0] + 0x2c);
    t = FX_Inv(state[0xb], state[0xc]);
    t2 = FX_Mul(t, t);
    t3 = FX_Mul(t2, t);
    t2x3 = 3 * t2;
    func_01ffa724(2 * t3 - t2x3 + 0x1000, (Vec3 *)(state + 0x13), &acc);
    func_01ffa724(-(t3 + t3) + t2x3, &target, &tmp);
    VEC_Add(&acc, &tmp, &acc);
    func_01ffa724(t3 - 2 * t2 + t, (Vec3 *)(state + 0xd), &tmp);
    VEC_Add(&acc, &tmp, &acc);
    func_01ffa724(t3 - t2, (Vec3 *)(state + 0x10), &tmp);
    VEC_Add(&acc, &tmp, &acc);
    func_0203ca30(*state + 0xa0, &acc);
    if (state[0xb] < state[0xc]) {
        return;
    }
    if ((((Hw60 *)(*(int *)(*state + 0x384) + 0x60))->lo & 1) != 0) {
        struct HitPacket packet = {0};
        packet.flagsLo = 4;
        packet.normal = data_02041dc8;
        packet.field_10 = *(u16 *)(*(int *)(*state + 0x384) + 0x200 + 0x9c);
        packet.field_14 = *(int *)(*state + 0x258);
        packet.field_18 = *(void **)(*(int *)(*state + 0x384) + 0x39c);
        func_ov107_020c5cfc(*(int *)(*state + 0x384), state[6], &packet);
    }
    {
    Vec3 c;
    Vec3 d;
    struct Msg14 msg;
    FxVec vContact;
    msg = data_ov244_020d36f8;
    VEC_Subtract((void *)(*OS_IsThreadAvailable_0x020c9848() + 0x88), (void *)state[7], &d);
    func_01ff8d18(&d, &d);
    func_01ffa724(0x3000, &d, &d);
    VEC_Add((void *)state[7], &d, &c);
    vContact.x = *(Fx32 *)&c.x;
    PACK3(&msg, 5, vContact.x.value);
    vContact.y = *(Fx32 *)&c.y;
    PACK3(&msg, 8, vContact.y.value);
    vContact.z = *(Fx32 *)&c.z;
    PACK3(&msg, 11, vContact.z.value);
    ((u8 *)&msg)[4] = 0x30;
    if (((struct Ov244Actor *)*state)->pfnMessage != 0) {
        ((struct Ov244Actor *)*state)->pfnMessage((struct Ov244Actor *)*state, &msg, 0xe);
    }
    }
    func_ov107_020c5af8(*state, 0x113, 0xf, &acc);
    *(s8 *)(*state + 0x1c7) = 0;
    ((struct Level *)(*(int *)(*state + 0x384) + 0x420))->n += 1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
