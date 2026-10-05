/* Swing tick of the ov284 enemy: re-acquires the target into +0xc and aims the +0x14 yaw at its
 * +0x190 point from the +4 position; the +0x1c timer accumulates the frame-time, its fraction
 * over 0xa22 (clamped to 1.0) drives the swing, and past 0x888 reaction 0x16c mode 4 fires
 * once (+0x25) at the position. From the half-way point the +0x3a8 item's +0x68 sphere with a
 * doubled radius offers a kind-0 hit pushed away from the position at 0x1000 to every entity
 * whose +0x1b4 kind bit is clear in the +0x24 mask: on acceptance the overlay's 14-byte
 * template with the +0x3a4 item's +0x14 point goes to the actor's +0x24 message hook, the kind
 * bit is set and reaction 0x16c mode 5 fires there. Once the +8 busy byte clears animation 7
 * plays and the tick hands off to cd020. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

typedef struct { VecFx32 pos; int radius; } Sphere;
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

struct Ov284Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov284Owner *self, PosMsg *msg, int size);
};

struct Ov284SwingState {
    struct Ov284Owner *pOwner;  /* +0x00 */
    VecFx32 *pPos;                 /* +0x04 */
    u8 *pBusy;                  /* +0x08 */
    int pTarget;                /* +0x0c */
    char pad010[4];
    int nYaw;                   /* +0x14 */
    char pad018[4];
    int nTimer;                 /* +0x1c */
    char pad020[4];
    u8 bHitMask24;              /* +0x24 */
    u8 bWarned25;               /* +0x25 */
};

extern int Ov107_FindNearestObject(struct Ov284Owner *owner, int mode);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern s64 FX_DivFx64c(int num, int den);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *d);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern int Ov107_CollectSphereOverlaps(struct Ov284Owner *owner, Sphere *sphere, int *out);
extern int Ov107_InvokeHitCallback(int hit, struct Ov284Owner *a, struct Ov284Owner *b, int kind, VecFx32 *push, int z);
extern void Ov107_BuildAndSendUpdate(struct Ov284Owner *owner, int a, int id, void *at);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov284_AiRollTimerQueue2OnAnimEnd(void);
extern const PosMsg data_ov284_020cd5b8;

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov284SwingState *state, PosMsg *msg, const VecFx32 *src)
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

void Ov284_SwingTick(int *node)
{
    struct Ov284SwingState *state = (struct Ov284SwingState *)node[1];
    VecFx32 d;
    int hits[4];
    Sphere sphere;
    VecFx32 push;
    PosMsg msg;
    PosMsg tmpl;
    s64 t;
    long i;
    long n;

    state->pTarget = Ov107_FindNearestObject(state->pOwner, 0);
    if (state->pTarget != 0) {
        VEC_Subtract((void *)(state->pTarget + 0x190), state->pPos, &d);
        state->nYaw = FX_Atan2(d.x, d.z);
    }
    state->nTimer += *(int *)(*node + 0x2c);
    t = FX_DivFx64c(state->nTimer, 0xa22);
    if (t > 0x100000000LL) {
        t = 0x100000000LL;
    }
    if (state->bWarned25 == 0 && state->nTimer >= 0x888) {
        Ov107_BuildAndSendUpdate(state->pOwner, 0x16c, 4, state->pPos);
        state->bWarned25 = 1;
    }
    if (t >= 0x80000000LL) {
        sphere = *(Sphere *)(*(int *)(*(int *)((char *)state->pOwner + 0x3a8)) + 0x68);
        sphere.radius <<= 1;
        n = Ov107_CollectSphereOverlaps(state->pOwner, &sphere, hits);
        i = 0;
        if (n > 0) {
            tmpl = data_ov284_020cd5b8;
            do {
                if (((state->bHitMask24 >> *(u8 *)(hits[i] + 0x1b4)) & 1) == 0) {
                    VEC_Subtract((void *)(hits[i] + 0x190), state->pPos, &push);
                    VEC_Normalize(&push, &push);
                    ScaleVec3Fx12(0x1000, &push, &push);
                    if (Ov107_InvokeHitCallback(hits[i], state->pOwner, state->pOwner, 0, &push, 0) != 0) {
                        msg = tmpl;
                        SendPos(state, &msg, (VecFx32 *)(*(int *)((char *)state->pOwner + 0x3a4) + 0x14));
                        state->bHitMask24 |= 1 << *(u8 *)(hits[i] + 0x1b4);
                        Ov107_BuildAndSendUpdate(state->pOwner, 0x16c, 5, (void *)(*(int *)((char *)state->pOwner + 0x3a4) + 0x14));
                    }
                }
            } while (++i < n);
        }
    }
    if (*state->pBusy != 0) {
        return;
    }
    Ov107_PostTagUpdate((Actor *)state->pOwner, 7, 0);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov284_AiRollTimerQueue2OnAnimEnd);
}
