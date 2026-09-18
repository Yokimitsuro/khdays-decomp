/*
 * Homing flight tick of the ov153 projectile state (x3: ov153/154/155). The actors inside the
 * owner's +0x74 sphere are pushed away along the flattened direction from the owner at 0x800
 * through the ov107 hit hook (kind 0); the first that takes it gets a kind-5 position message
 * with the +4 position delivered to the owner's +0x24 handler, sub-state 0, reaction 0x13c/5 and
 * the slot released. Then, while the owner's +0x17a bit 0 is set and a target is acquirable, a
 * target ahead of the flight direction (flattened offset . flattened +0x14 direction > 0.5)
 * re-aims the direction: the heading of the summed vectors plus a random +-0x860 turn becomes
 * a sine/cosine pair in +0x14/+0x1c. The +8/+0x10 step is the direction scaled by the +0x20
 * speed; without bit 0 the +0xc height drops by 30 x dt / 16, with it the height decays
 * (x -0xd00 / 4096) and the speed eases towards 16 by a fortieth. Bit 1 of the flags, or the
 * +0x24 distance passing 0x14000 after growing by the step length, ends the flight (message,
 * reaction 0x13c/6, sub-state 0, slot released).
 *
 * Codegen notes: the sender's volatile ints keep the packed position on the stack (three
 * triples after the aggregates); `const` on the sine table lets both table loads precede the
 * direction stores; `angle += r` (not `angle = angle + r`) puts the atan2 result first in the
 * add; the SDK macros are spelled literally (FX_RAD_TO_IDX with `>> 44`, FX_SinIdx/CosIdx as
 * table[(idx >> 4) << 1] and +1).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

struct Flags17a {
    u8 bit0 : 1;
    u8 bit1 : 1;
};

struct Ov153Actor {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov153Actor *self, PosMsg *msg, int size);
    char pad028[0x4c];
    Vec3 vPos74;
    int nRadius80;
    char pad084[0xf6];
    struct Flags17a flags17a;
    char pad17b[0x4c];
    u8 nSubState1c7;
    char pad1c8[0x1c4];
    char *pItem38c;
};

struct Ov153FlightState {
    struct Ov153Actor *pOwner;
    Vec3 *pPos;
    int nStepX;
    int nHeight;
    int nStepZ;
    int nDirX;
    int nDirY;
    int nDirZ;
    int nSpeed;
    int nDist;
};

extern int func_ov107_020c8eb8(char *item, Vec3 *sphere, struct Ov153Actor **out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(struct Ov153Actor *hit, struct Ov153Actor *a, char *item, int kind, const Vec3 *push, int z);
extern void func_ov107_020c5af8(struct Ov153Actor *owner, u16 a, u16 id, Vec3 *pos);
extern void func_0203c634(int node, int slot, void *cb);
extern struct Ov153Actor *func_ov107_020cab14(struct Ov153Actor *owner, int mode);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_02023eb4(int bound);
extern int func_020050b4(int x, int z);
extern int VEC_Mag(const Vec3 *v);
extern const short data_0203d210[];
extern const PosMsg data_ov155_020d58a8;
extern const PosMsg data_ov155_020d58b6;
extern const PosMsg data_ov155_020d58d2;

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov153FlightState *state, PosMsg *msg, const Vec3 *src)
{
    volatile int px;
    volatile int py;
    volatile int pz;
    int x;
    x = src->x;
    PackFx24(&msg->pos[0], x);
    px = x;
    x = src->y;
    PackFx24(&msg->pos[1], x);
    py = x;
    x = src->z;
    PackFx24(&msg->pos[2], x);
    pz = x;
    if (state->pOwner->pfnMessage != 0) {
        state->pOwner->pfnMessage(state->pOwner, msg, 0xe);
    }
}

void func_ov155_020d4578(int node)
{
    struct Ov153Actor *actor;
    struct Ov153FlightState *state = *(struct Ov153FlightState **)(node + 4);
    struct Ov153Actor *hits[4];
    Vec3 push;
    PosMsg msgA;
    Vec3 d;
    Vec3 dir;
    Vec3 sum;
    PosMsg msgB;
    PosMsg msgC;
    struct Ov153Actor *target;
    int angle;
    int r;
    int idx;
    int i;
    int n;

    actor = state->pOwner;
    n = func_ov107_020c8eb8(actor->pItem38c, &actor->vPos74, hits);
    for (i = 0; i < n; i++) {
        VEC_Subtract(&hits[i]->vPos74, &actor->vPos74, &push);
        push.y = 0;
        func_01ff8d18(&push, &push);
        func_01ffa724(0x800, &push, &push);
        if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner->pItem38c, 0, &push, 0) != 0) {
            msgA = data_ov155_020d58b6;
            SendPos(state, &msgA, state->pPos);
            state->pOwner->nSubState1c7 = 0;
            func_ov107_020c5af8(state->pOwner, 0x13c, 5, state->pPos);
            func_0203c634(node, *(signed char *)(node + 0x20), 0);
            return;
        }
    }
    if (state->pOwner->flags17a.bit0) {
        target = func_ov107_020cab14(state->pOwner, 0);
        if (target != 0) {
            VEC_Subtract(&target->vPos74, &actor->vPos74, &d);
            d.y = 0;
            dir = *(Vec3 *)&state->nDirX;
            dir.y = 0;
            func_01ff8d18(&d, &d);
            func_01ff8d18(&dir, &dir);
            if (VEC_DotProduct(&d, &dir) > 0x800) {
                VEC_Add(&d, &dir, &sum);
                r = func_02023eb4(0x10c1) - 0x860;
                angle = func_020050b4(sum.x, sum.z);
                angle += r;
                idx = (unsigned short)((0x28BE60DB9391LL * angle + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
                state->nDirX = data_0203d210[(idx >> 4) << 1];                               /* FX_SinIdx */
                state->nDirZ = data_0203d210[((idx >> 4) << 1) + 1];                         /* FX_CosIdx */
            }
        }
    }
    state->nStepX = (int)(((long long)state->nDirX * state->nSpeed + 0x800) >> 12);
    state->nStepZ = (int)(((long long)state->nDirZ * state->nSpeed + 0x800) >> 12);
    if (!state->pOwner->flags17a.bit0) {
        state->nHeight -= (int)(((long long)(*(int *)(*(int *)node + 0x2c) * 30) * 0x100 + 0x800) >> 12);
    } else {
        state->nHeight = -(int)(((long long)state->nHeight * 0xd00 + 0x800) >> 12);
        state->nSpeed += (0x10 - state->nSpeed) / 40;
    }
    if (state->pOwner->flags17a.bit1) {
        msgB = data_ov155_020d58a8;
        SendPos(state, &msgB, state->pPos);
        func_ov107_020c5af8(state->pOwner, 0x13c, 6, state->pPos);
        state->pOwner->nSubState1c7 = 0;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    state->nDist += VEC_Mag((Vec3 *)&state->nStepX);
    if (state->nDist <= 0x14000) {
        return;
    }
    msgC = data_ov155_020d58d2;
    SendPos(state, &msgC, state->pPos);
    func_ov107_020c5af8(state->pOwner, 0x13c, 6, state->pPos);
    state->pOwner->nSubState1c7 = 0;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
