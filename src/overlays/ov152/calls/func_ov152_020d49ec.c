/* Shot launch of the ov151 enemy (and its byte-identical twin): clears the +0x38 hit count, sets
 * bit 0 of the owner's +0x60 high byte and of the +0x388 item's +8 flags, clears bits 0x8e of
 * the +0x60 high byte, and gives the +0xc velocity the forward axis rotated by the +0x18
 * orientation at the +0x28 speed (0x400) with the +0x34 travel reset. If the ray from the
 * +0x38c item's +0x74 point to the +8 position hits the scene collision within 0x200, the
 * overlay's 14-byte message goes to the owner's +0x24 hook with that position, reaction 0x14f
 * mode 6 fires there, sub-state 0 is requested and the state ends; otherwise the shot tick
 * (cd3ac) takes over. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

struct Ov151Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov151Owner *self, PosMsg *msg, int size);
};

struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned int b : 8; };

struct Ov151ShotState {
    struct Ov151Owner *pOwner;  /* +0x00 */
    int pTarget;                /* +0x04 */
    Vec3 *pPos;                 /* +0x08 */
    Vec3 vVelocity;             /* +0x0c */
    char pad018[0x10];
    int nSpeed;                 /* +0x28 */
    char pad02c[8];
    int nTravel;                /* +0x34 */
    int nHits;                  /* +0x38 */
};

extern void func_0202f384(Vec3 *dst, void *quat, const Vec3 *src);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01fff948(void *collision, void *from, Vec3 *dir, int radius);
extern void func_ov107_020c5af8(struct Ov151Owner *owner, int a, int id, Vec3 *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov152_020d4c2c(void);
extern const Vec3 data_02042258;
extern const PosMsg data_ov152_020d648a;

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov151ShotState *state, PosMsg *msg, const Vec3 *src)
{
    FxVec vDead;
    vDead.x = *(Fx32 *)&src->x;
    PackFx24(&msg->pos[0], vDead.x.value);
    vDead.y = *(Fx32 *)&src->y;
    PackFx24(&msg->pos[1], vDead.y.value);
    vDead.z = *(Fx32 *)&src->z;
    PackFx24(&msg->pos[2], vDead.z.value);
    if (state->pOwner->pfnMessage != 0) {
        state->pOwner->pfnMessage(state->pOwner, msg, 0xe);
    }
}

void func_ov152_020d49ec(int *node)
{
    struct Ov151ShotState *state = (struct Ov151ShotState *)node[1];
    char *scene = *(char **)((char *)state->pOwner + 4);
    Vec3 d;
    PosMsg msg;

    state->nHits = 0;
    {
        u16 hw = *(u16 *)((char *)state->pOwner + 0x60);
        *(u16 *)((char *)state->pOwner + 0x60) =
            (u16)((hw & ~0xff00) | (((((unsigned int)hw << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));
    }
    ((struct b8 *)(*(int *)((char *)state->pOwner + 0x388) + 8))->b |= 1;
    ((struct hw60 *)((char *)state->pOwner + 0x60))->hi &= ~0x8e;
    state->nSpeed = 0x400;
    func_0202f384(&state->vVelocity, (char *)state + 0x18, &data_02042258);
    func_01ffa724(state->nSpeed, &state->vVelocity, &state->vVelocity);
    state->nTravel = 0;
    VEC_Subtract(state->pPos, (void *)(*(int *)((char *)state->pOwner + 0x38c) + 0x74), &d);
    if (scene != 0 && func_01fff948(*(void **)(scene + 0x7c), (void *)(*(int *)((char *)state->pOwner + 0x38c) + 0x74), &d, 0x200) != 0) {
        msg = data_ov152_020d648a;
        SendPos(state, &msg, state->pPos);
        func_ov107_020c5af8(state->pOwner, 0x14f, 6, state->pPos);
        *(u8 *)((char *)state->pOwner + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov152_020d4c2c);
}
