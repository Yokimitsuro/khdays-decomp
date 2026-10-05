/* Swing callback of the ov277 enemy's arm (twin of ce8c4): between frames 4.55 and 5.72 of the event
 * the +0x88 animation's bone matrix at the event frame (02016320) gives the arm tip; the sweep box
 * is centred on the arm's +0x14 root at height 0.5, axis-aligned, with the root-to-tip distance as
 * its extent. Every entity it holds is pushed by 1.0 along the flattened direction away from the
 * centre (kind 0) and, on acceptance, the point that far from the centre towards the entity is
 * packed into the overlay's 14-byte template for the owner's +0x24 message hook and effect 0x53
 * plays there. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
typedef struct { int m[9]; VecFx32 trans; } Mtx43;

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

struct BoxQuery {
    VecFx32 vCenter;
    VecFx32 vAxisX;
    VecFx32 vAxisZ;
    VecFx32 vAxisY;
    int nExtent;
    int bFlag;
};

struct Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Owner *self, PosMsg *msg, int size);
};

struct SwingEvent {
    int pad00;
    struct Owner *pOwner;   /* +0x04 */
    int nFrame;             /* +0x08 */
    int nKey;               /* +0x0c */
};

extern int NNS_G3dGetResultMtx(void *anim, Mtx43 *out, int a, int key);
extern void VEC_Subtract(void *a, void *b, VecFx32 *d);
extern int VEC_Normalize(VecFx32 *a, VecFx32 *d);
extern int Ov107_CollectEntitiesTouchingDisc(struct Owner *owner, struct BoxQuery *query, int *out);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern int Ov107_InvokeHitCallback(int hit, struct Owner *a, struct Owner *b, int kind, VecFx32 *push, int z);
extern void VEC_Add(void *a, void *b, VecFx32 *d);
extern void Slot_Spawn(int id, int kind, VecFx32 *pos, int flag);
extern const VecFx32 data_02042270;
extern const VecFx32 data_02042258;
extern const VecFx32 data_02042264;
extern const PosMsg data_ov277_020d36ae;

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct SwingEvent *ev, PosMsg *msg, const VecFx32 *src)
{
    FxVec vDead;
    vDead.x = *(Fx32 *)&src->x;
    PackFx24(&msg->pos[0], vDead.x.value);
    vDead.y = *(Fx32 *)&src->y;
    PackFx24(&msg->pos[1], vDead.y.value);
    vDead.z = *(Fx32 *)&src->z;
    PackFx24(&msg->pos[2], vDead.z.value);
    if (ev->pOwner->pfnMessage != 0) {
        ev->pOwner->pfnMessage(ev->pOwner, msg, 0xe);
    }
}

void Ov277_ArmSwingSweepB(char *self, struct SwingEvent *ev)
{
    Mtx43 mtx;
    int hits[4];
    VecFx32 tip;
    struct BoxQuery query;
    VecFx32 dir;
    VecFx32 push;
    VecFx32 pos;
    PosMsg msg;
    PosMsg tmpl;
    long i;
    long n;

    if (ev->nFrame < 0x48c8 || ev->nFrame > 0x5b83) {
        return;
    }
    if (NNS_G3dGetResultMtx((void *)(*(int *)(self + 0x88) + 0x20), &mtx, 0, ev->nKey) == 0) {
        return;
    }
    tip = mtx.trans;
    VEC_Subtract(self + 0x14, &tip, &dir);
    query.vCenter = *(VecFx32 *)(self + 0x14);
    query.vCenter.y = 0x800;
    query.vAxisX = data_02042270;
    query.vAxisZ = data_02042258;
    query.vAxisY = data_02042264;
    query.nExtent = VEC_Normalize(&dir, &dir);
    query.bFlag = 0;
    n = Ov107_CollectEntitiesTouchingDisc(ev->pOwner, &query, hits);
    i = 0;
    if (n > 0) {
        tmpl = data_ov277_020d36ae;
        do {
            VEC_Subtract((void *)(hits[i] + 0x74), &query.vCenter, &push);
            push.y = 0;
            VEC_Normalize(&push, &push);
            ScaleVec3Fx12(0x1000, &push, &push);
            if (Ov107_InvokeHitCallback(hits[i], ev->pOwner, ev->pOwner, 0, &push, 0) != 0) {
                msg = tmpl;
                VEC_Subtract((void *)(hits[i] + 0x74), &query.vCenter, &pos);
                VEC_Normalize(&pos, &pos);
                ScaleVec3Fx12(query.nExtent, &pos, &pos);
                VEC_Add(&query.vCenter, &pos, &pos);
                SendPos(ev, &msg, &pos);
                Slot_Spawn(0, 0x53, &pos, 0);
            }
        } while (++i < n);
    }
}
