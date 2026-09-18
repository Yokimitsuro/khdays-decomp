/* Dash tick of the ov156 enemy (and its byte-identical twin). The actors inside the owner's
 * +0x74 sphere are pushed away along the flattened direction from the owner at 0x800 through the
 * ov107 hit hook (kind 0); the first that takes it gets a kind-5 position message with the +8
 * position delivered to the owner's +0x24 handler, reaction 0x13d/5, sub-state 0 and the slot
 * released. Then a target ahead of the +0x18 direction turns it towards the target by
 * 30 x dt / 15 (d040) as a sine/cosine pair. With bit 0 of the +0x24 flags the actor found at
 * the owner's position (c9094) that is not +0x1ac-4 gets a 0x2004 hit packet (zero normal, the
 * +0x38c item's +0x290/+0x19c ids) through the owner's +0x25c source when its shape's +8 bit 0
 * is set; acceptance sends the message, fires reaction 0/0x53, sub-state 0 and releases the
 * slot. The +0x2c bounce timer counts down; once spent, a wall contact (bit 1 of +0x17a, or a
 * sphere cast of the direction at 0x500 hitting a +8-clear surface whose +4 record gives the
 * normal) reflects the direction about the contact normal, re-arms the timer at 0x100 and fires
 * reaction 0x13d/6. The +0xc/+0x14 step is the direction at 0x500 and the +0x10 height drops
 * 0x40 per tick unless bit 0 of +0x17a is set (then it is 0); the +0x28 distance grows by the
 * step length and past 0x14e00 the dash ends (message, reaction 0x13d/6, sub-state 0, slot
 * released).
 *
 * Codegen notes as in ov153_cccf8: volatile ints in the sender keep the packed position on the
 * stack, `const` on the sine table lets both table loads precede the direction stores, and the
 * hit packet is zeroed as a whole before its fields are filled. */
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

struct w8 { unsigned int lo : 8, rest : 24; };

struct Flags24 {
    u8 bit0 : 1;
};

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

struct CollisionRecord {
    char pad000[0x14];
    short nx;
    short ny;
    short nz;
};

struct CollisionResult {
    int field_00;
    struct CollisionRecord *pRecord;
    int field_08;
};

struct Ov156Item {
    char pad000[0x19c];
    u8 nId19c;
    char pad19d[0x290 - 0x19d];
    u16 nId290;
};

struct Ov156Actor {
    char pad000[4];
    char *pScene;
    char pad008[0x1c];
    void (*pfnMessage)(struct Ov156Actor *self, PosMsg *msg, int size);
    char pad028[0x4c];
    Vec3 vPos74;
    int nRadius80;
    char pad084[0x90];
    Vec3 vNormal114;
    char pad120[0x5a];
    struct Flags17a flags17a;
    u8 nFlags17b;
    char pad17c[0x4b];
    u8 nSubState1c7;
    char pad1c8[0x94];
    int nSource25c;
    char pad260[0x12c];
    struct Ov156Item *pItem38c;
};

struct Ov156DashState {
    struct Ov156Actor *pOwner;
    int pTarget;
    Vec3 *pPos;
    Vec3 vStep;
    int nDirX;
    int nDirY;
    int nDirZ;
    struct Flags24 flags24;
    char pad025[3];
    int nDist;
    int nBounceTimer;
};

extern int func_ov107_020c8eb8(struct Ov156Item *item, Vec3 *sphere, struct Ov156Actor **out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(struct Ov156Actor *hit, struct Ov156Actor *a, struct Ov156Item *item, int kind, const Vec3 *push, int z);
extern void func_ov107_020c5af8(struct Ov156Actor *owner, u16 a, u16 id, Vec3 *pos);
extern void func_0203c634(int node, int slot, void *cb);
extern struct Ov156Actor *func_ov107_020cab14(struct Ov156Actor *owner, int mode);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern int func_020050b4(int x, int z);
extern int func_0203d040(int cur, int want, int step, int *state);
extern char *func_ov107_020c9094(struct Ov156Actor *owner, Vec3 *pos, int *shape);
extern int func_ov107_020c5cfc(char *other, int source, struct HitPacket *packet);
extern struct CollisionResult *func_01fff8e8(void *collision, Vec3 *position, Vec3 *direction, int radius, void *ignore);
extern int VEC_Mag(const Vec3 *v);
extern const short data_0203d210[];
extern const Vec3 data_02041dc8;
extern const PosMsg data_ov157_020d0bcc;
extern const PosMsg data_ov157_020d0bda;
extern const PosMsg data_ov157_020d0be8;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov156DashState *state, PosMsg *msg, const Vec3 *src)
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

void func_ov157_020d03f4(int node)
{
    struct Ov156Actor *actor;
    struct Ov156DashState *state = *(struct Ov156DashState **)(node + 4);
    struct Ov156Actor *hits[4];
    Vec3 push;
    PosMsg msgA;
    Vec3 d;
    int shape;
    struct Ov156Actor *target;
    struct CollisionResult *result;
    char *other;
    int cur;
    int want;
    int angle;
    unsigned int idx;
    int hit;
    int i;
    int nHits;

    actor = state->pOwner;
    nHits = func_ov107_020c8eb8(actor->pItem38c, &actor->vPos74, hits);
    for (i = 0; i < nHits; i++) {
        VEC_Subtract(&hits[i]->vPos74, &actor->vPos74, &push);
        push.y = 0;
        func_01ff8d18(&push, &push);
        func_01ffa724(0x800, &push, &push);
        if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner->pItem38c, 0, &push, 0) != 0) {
            msgA = data_ov157_020d0bda;
            SendPos(state, &msgA, state->pPos);
            func_ov107_020c5af8(state->pOwner, 0x13d, 5, state->pPos);
            state->pOwner->nSubState1c7 = 0;
            func_0203c634(node, *(signed char *)(node + 0x20), 0);
            return;
        }
    }
    target = func_ov107_020cab14(state->pOwner, 0);
    if (target != 0) {
        VEC_Subtract(&target->vPos74, &actor->vPos74, &d);
        if (VEC_DotProduct(&d, (Vec3 *)&state->nDirX) > 0) {
            cur = func_020050b4(state->nDirX, state->nDirZ);
            want = func_020050b4(d.x, d.z);
            angle = func_0203d040(cur, want, *(int *)(*(int *)node + 0x2c) * 30 / 15, 0);
            idx = ANG2IDX(angle);
            state->nDirX = data_0203d210[idx * 2];                                       /* FX_SinIdx */
            state->nDirZ = data_0203d210[idx * 2 + 1];                                   /* FX_CosIdx */
        }
    }
    if (state->flags24.bit0) {
        other = func_ov107_020c9094(state->pOwner, &actor->vPos74, &shape);
        if (other != 0 && (*(u16 *)(other + 0x1ac) & 4) == 0) {
            struct HitPacket packet = {0};
            PosMsg msgB;
            packet.flagsLo = 0x2004;
            packet.normal = data_02041dc8;
            packet.field_10 = state->pOwner->pItem38c->nId290;
            packet.field_16 = state->pOwner->pItem38c->nId19c;
            packet.field_18 = (void *)shape;
            if ((((struct w8 *)(shape + 8))->lo & 1) != 0 &&
                func_ov107_020c5cfc(other, state->pOwner->nSource25c, &packet) != 0) {
                msgB = data_ov157_020d0bcc;
                SendPos(state, &msgB, state->pPos);
                func_ov107_020c5af8(state->pOwner, 0, 0x53, state->pPos);
                state->pOwner->nSubState1c7 = 0;
                func_0203c634(node, *(signed char *)(node + 0x20), 0);
                return;
            }
        }
    }
    if (state->nBounceTimer > 0) {
        state->nBounceTimer -= *(int *)(*(int *)node + 0x2c);
    }
    if (state->nBounceTimer <= 0) {
        Vec3 n;
        Vec3 back;
        Vec3 refl;
        n = state->pOwner->vNormal114;
        hit = state->pOwner->flags17a.bit1;
        if (hit == 0 && state->pOwner->nFlags17b == 0) {
            char *scene = state->pOwner->pScene;
            func_01ffa724(0x500, (Vec3 *)&state->nDirX, &back);
            result = func_01fff8e8(*(void **)(scene + 0x7c), &state->pOwner->vPos74, &back, state->pOwner->nRadius80, 0);
            if (result != 0 && result->field_08 == 0) {
                hit = 1;
                n.x = result->pRecord->nx;
                n.y = result->pRecord->ny;
                n.z = result->pRecord->nz;
            }
        }
        if (hit != 0) {
            func_01ffa724(-0x1000, (Vec3 *)&state->nDirX, &back);
            func_01ffa724(VEC_DotProduct(&back, &n) << 1, &n, &refl);
            VEC_Subtract(&refl, &back, &refl);
            func_01ff8d18(&refl, (Vec3 *)&state->nDirX);
            state->nBounceTimer = 0x100;
            func_ov107_020c5af8(state->pOwner, 0x13d, 6, state->pPos);
        }
    }
    state->vStep.x = (int)(((long long)state->nDirX * 0x500 + 0x800) >> 12);
    if (state->pOwner->flags17a.bit0) {
        state->vStep.y = 0;
    } else {
        state->vStep.y -= 0x40;
    }
    state->vStep.z = (int)(((long long)state->nDirZ * 0x500 + 0x800) >> 12);
    state->nDist += VEC_Mag(&state->vStep);
    if (state->nDist <= 0x14e00) {
        return;
    }
    {
        PosMsg msgC;
        msgC = data_ov157_020d0be8;
        SendPos(state, &msgC, state->pPos);
        func_ov107_020c5af8(state->pOwner, 0x13d, 6, state->pPos);
        state->pOwner->nSubState1c7 = 0;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
    }
}
