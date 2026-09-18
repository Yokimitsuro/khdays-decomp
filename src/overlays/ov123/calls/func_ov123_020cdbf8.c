/* Shot flight tick of the ov123 enemy (and its byte-identical twin). Without a +0x24 target the
 * actors inside the owner's +0x74 sphere are pushed away along the flattened direction from the
 * owner at 0x800 through the ov107 hit hook (kind 0); the first that takes it gets the overlay's
 * hit message with the +8 position, sub-state 0, reaction 0x115 mode 5 and the slot released.
 * With a target, the actor found at the sphere (c9094) that is not +0x1ac-4 gets a 0x2004 hit
 * packet (0x1000 added for +0x19c kind 5; zero vector, the +0x38c item's +0x290 id doubled, the
 * owner's +0x258 strength, the query hit) through the owner's +0x25c source when the query
 * hit's +8 bit 0 is set; acceptance sends the message, fires reaction 0/0x53, sub-state 0 and
 * releases the slot. The step from the +0x2c previous position (then refreshed) grows the
 * +0x28 distance: a wall or floor contact (bits 0/1 of +0x17a) ends the flight with reaction
 * 0x115 mode 6, and past 0x14000 the end message goes out (sub-state 0, slot released). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct Vec4 { int x, y, z, w; } Vec4;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

struct Zero44 {
    int words[11];
};

struct HitCommand {
    u32 flagsLo : 16;
    u32 flagsHi : 16;
    Vec3 vector04;
    u32 field10;
    u32 field14;
    void *hit18;
    int pad1c[4];
};

struct CollisionHit {
    int pad00[2];
    u32 flags08 : 8;
};

struct Flags17a {
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
};

struct Ov191Actor {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov191Actor *self, PosMsg *msg, int size);
    char pad028[0x4c];
    Vec4 vSphere74;
    char pad084[0xf6];
    struct Flags17a flags17a;
    char pad17b[0x4c];
    u8 nSubState1c7;
    char pad1c8[0x90];
    int nStrength258;
    int nHitOwner25c;
    char pad260[0x12c];
    char *pItem38c;
};

struct Ov191FlightState {
    struct Ov191Actor *pOwner;  /* +0x00 */
    int pad004;
    Vec3 *pPos;                 /* +0x08 */
    char pad00c[0x18];
    int pTarget;                /* +0x24 */
    int nDist;                  /* +0x28 */
    Vec3 vPrev;                 /* +0x2c */
};

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern int VEC_Mag(const Vec3 *v);
extern int func_ov107_020c8eb8(char *item, Vec4 *sphere, struct Ov191Actor **out);
extern int func_ov107_020ca918(struct Ov191Actor *hit, struct Ov191Actor *a, char *item, int kind, const Vec3 *push, int z);
extern void func_ov107_020c5af8(struct Ov191Actor *owner, u16 a, u16 id, Vec3 *pos);
extern void func_0203c634(int node, int slot, void *cb);
extern struct Ov191Actor *func_ov107_020c9094(struct Ov191Actor *owner, Vec4 *sphere, void *result);
extern int func_ov107_020c5cfc(struct Ov191Actor *target, int value, struct HitCommand *command);
extern const Vec3 data_02041dc8;
extern const PosMsg data_ov123_020ce2b8;
extern const PosMsg data_ov123_020ce2c6;
extern const PosMsg data_ov123_020ce2d4;
extern const PosMsg data_ov123_020ce2e2;

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov191FlightState *state, PosMsg *msg, const Vec3 *src)
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

void func_ov123_020cdbf8(int node)
{
    struct Ov191FlightState *state = *(struct Ov191FlightState **)(node + 4);
    Vec4 sphere;
    Vec3 step;
    struct Ov191Actor *hits[4];
    Vec3 push;
    PosMsg msg1;
    int i;
    int n;

    sphere = state->pOwner->vSphere74;
    if (state->pTarget == 0) {
        n = func_ov107_020c8eb8(state->pOwner->pItem38c, &sphere, hits);
        for (i = 0; i < n; i++) {
            VEC_Subtract(&hits[i]->vSphere74, &state->pOwner->vSphere74, &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            func_01ffa724(0x800, &push, &push);
            if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner->pItem38c, 0, &push, 0) != 0) {
                msg1 = data_ov123_020ce2d4;
                SendPos(state, &msg1, state->pPos);
                state->pOwner->nSubState1c7 = 0;
                func_ov107_020c5af8(state->pOwner, 0x115, 5, state->pPos);
                func_0203c634(node, *(signed char *)(node + 0x20), 0);
                return;
            }
        }
    } else {
        void *queryHit;
        struct Ov191Actor *target;

        target = func_ov107_020c9094(state->pOwner, &sphere, &queryHit);
        if (target != 0 && (*(u16 *)((char *)target + 0x1ac) & 4) == 0) {
            struct HitCommand command = {0};

            if (*(u8 *)((char *)target + 0x19c) == 5) {
                command.flagsLo |= 0x1000;
            }
            command.flagsLo |= 0x2004;
            command.vector04 = data_02041dc8;
            command.field10 = (command.field10 & 0xffff0000) |
                              (((u32)*(u16 *)(state->pOwner->pItem38c + 0x290) << 17) >> 16);
            command.field14 = (command.field14 & 0xffff0000) |
                              (((u32)state->pOwner->nStrength258 << 16) >> 16);
            command.hit18 = queryHit;
            if ((((struct CollisionHit *)queryHit)->flags08 & 1) != 0 &&
                func_ov107_020c5cfc(target, state->pOwner->nHitOwner25c, &command) != 0) {
                PosMsg msg2;
                msg2 = data_ov123_020ce2c6;
                SendPos(state, &msg2, state->pPos);
                func_ov107_020c5af8(state->pOwner, 0, 0x53, state->pPos);
                state->pOwner->nSubState1c7 = 0;
                func_0203c634(node, *(signed char *)(node + 0x20), 0);
                return;
            }
        }
    }

    VEC_Subtract(state->pPos, &state->vPrev, &step);
    state->vPrev = *state->pPos;
    if (state->pOwner->flags17a.bit0 || state->pOwner->flags17a.bit1) {
        PosMsg msg3;
        msg3 = data_ov123_020ce2b8;
        SendPos(state, &msg3, state->pPos);
        func_ov107_020c5af8(state->pOwner, 0x115, 6, state->pPos);
        state->pOwner->nSubState1c7 = 0;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    state->nDist += VEC_Mag(&step);
    if (state->nDist <= 0x14000) {
        return;
    }
    {
        PosMsg msg4;
        msg4 = data_ov123_020ce2e2;
        SendPos(state, &msg4, state->pPos);
        state->pOwner->nSubState1c7 = 0;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
    }
}
