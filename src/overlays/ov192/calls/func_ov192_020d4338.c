/*
 * Flight tick of the ov191 projectile state (x3: ov191/192/193). Each frame it rebuilds the +8
 * step from the +0x14 direction scaled by the +0x20 speed and copies the owner's +0x74 sphere.
 * With the +0x40 mode clear it sweeps the actors in the sphere through the ov107 hit hook
 * (kind 0, no push); the first that takes the hit gets a kind-5 position message with the +4
 * position delivered to the owner's +0x24 handler, reaction 0x133/5 at that position, sub-state
 * 2 and the slot released. With the mode set it asks the ov107 part query for the part under
 * the sphere; a part whose owner is not flagged 4 at +0x1ac and whose node carries bit 0 at +8
 * gets a 0x2004 hit command (zero normal, the +0x38c item's doubled +0x290 rate and the owner's
 * +0x258 strength) through func_ov107_020c5cfc -- success sends the same message, reaction
 * 0/0x53, sub-state 0 and releases the slot. Otherwise the +0x24 distance grows by the speed
 * and the flight ends (message, reaction 0x133/6, sub-state 2, slot released) when the owner's
 * +0x17a flags carry bit 0, 1 or 3 or the distance passes 0x14000.
 *
 * Codegen notes: the three kind-5 templates are 2da8 (hit), 2d9a (part) and 2d8c (end) -- the
 * pool keeps first-use order. Messages are block-scoped so they sit under the else block's
 * 44-byte scratch/command; the packed position is mirrored into three volatile ints owned by the
 * inline sender (allocated after the address-taken queryHit, one triple per call site), with the
 * owner read from the state only after the packing.
 */
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
    u32 flags00;
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
    struct Ov191Actor *pOwner;
    Vec3 *pPos;
    Vec3 vStep;
    Vec3 vDir;
    int nSpeed;
    int nDist;
    char pad028[0x18];
    int bPartMode;
};

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020c8eb8(char *item, Vec4 *sphere, struct Ov191Actor **out);
extern int func_ov107_020ca918(struct Ov191Actor *hit, struct Ov191Actor *a, char *item, int kind, const Vec3 *push, int z);
extern void func_ov107_020c5af8(struct Ov191Actor *owner, u16 a, u16 id, Vec3 *pos);
extern void func_0203c634(int node, int slot, void *cb);
extern struct Ov191Actor *func_ov107_020c9094(struct Ov191Actor *owner, Vec4 *sphere, void *result);
extern int func_ov107_020c5cfc(struct Ov191Actor *target, int value, struct HitCommand *command);
extern const Vec3 data_02041dc8;
extern const PosMsg data_ov192_020d4bac;
extern const PosMsg data_ov192_020d4bba;
extern const PosMsg data_ov192_020d4bc8;

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

void func_ov192_020d4338(int node)
{
    struct Ov191FlightState *state = *(struct Ov191FlightState **)(node + 4);
    Vec4 sphere;
    struct Ov191Actor *hits[4];
    PosMsg msg1;
    int i;
    int n;

    func_01ffa724(state->nSpeed, &state->vDir, &state->vStep);
    sphere = state->pOwner->vSphere74;
    if (state->bPartMode == 0) {
        n = func_ov107_020c8eb8(state->pOwner->pItem38c, &sphere, hits);
        if (n != 0) {
            for (i = 0; i < n; i++) {
                if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner->pItem38c, 0, &data_02041dc8, 0) != 0) {
                    msg1 = data_ov192_020d4bc8;
                    SendPos(state, &msg1, state->pPos);
                    func_ov107_020c5af8(state->pOwner, 0x133, 5, state->pPos);
                    state->pOwner->nSubState1c7 = 2;
                    func_0203c634(node, *(signed char *)(node + 0x20), 0);
                    return;
                }
            }
        }
    } else {
        struct Zero44 scratch = {{0}};
        void *queryHit;
        struct Ov191Actor *target;

        target = func_ov107_020c9094(state->pOwner, &sphere, &queryHit);
        if (target != 0 && (*(u16 *)((char *)target + 0x1ac) & 4) == 0) {
            struct HitCommand command = {0};

            command.flags00 = (command.flags00 & 0xffff0000) | 0x2004;
            command.vector04 = data_02041dc8;
            command.field10 = (command.field10 & 0xffff0000) |
                              (((u32)*(u16 *)(state->pOwner->pItem38c + 0x290) << 17) >> 16);
            command.field14 = (command.field14 & 0xffff0000) |
                              (((u32)state->pOwner->nStrength258 << 16) >> 16);
            command.hit18 = queryHit;
            if ((((struct CollisionHit *)queryHit)->flags08 & 1) != 0 &&
                func_ov107_020c5cfc(target, state->pOwner->nHitOwner25c, &command) != 0) {
                PosMsg msg2;
                msg2 = data_ov192_020d4bba;
                SendPos(state, &msg2, state->pPos);
                func_ov107_020c5af8(state->pOwner, 0, 0x53, state->pPos);
                state->pOwner->nSubState1c7 = 0;
                func_0203c634(node, *(signed char *)(node + 0x20), 0);
                return;
            }
        }
    }

    state->nDist += state->nSpeed;
    if (state->pOwner->flags17a.bit0 || state->pOwner->flags17a.bit1 || state->pOwner->flags17a.bit3 ||
        state->nDist > 0x14000) {
        PosMsg msg3;
        msg3 = data_ov192_020d4bac;
        SendPos(state, &msg3, state->pPos);
        func_ov107_020c5af8(state->pOwner, 0x133, 6, state->pPos);
        state->pOwner->nSubState1c7 = 2;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
    }
}
