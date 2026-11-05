/* Attack burst of the ov103 enemy (x4: ov048/067/086/103): every third tick of the +0x7b0 timer
 * refreshes the target; the anchor is sampled and two emitter positions placed along the
 * backwards heading (0x800 ahead, 0x1800 behind; range 0x1800, anchored at +0x2bd4); the burst
 * parameters take flags 0x205 (plus 0x420 with the rig's alternate flag), the spin by pattern
 * (0x1b00 / 0x2580 / 0x1fc0) and the fixed 0xa00/0x66/0xa00 extent; a successful submit that is
 * not busy marshals record 5 at the +0x26c8 muzzle with the heading and the alternate flag.
 * (The timer word doubles as the heading variable, as the ROM's registers show.) The +0x26c4
 * result then picks the follow-up: 1 arms the +0x47a/+0x47b pair and asks for step 2
 * when busy or step 1 outside pattern 2, 2 asks for step 1, 4 asks for step 2 unless +0x26c0
 * says 2. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

struct EmitPair {
    VecFx32 vPosB;
    VecFx32 vPosA;
    int nOwner;
    int nRange;
    void *pAnchor;
    int nFlags24;
};

struct Params {
    int nScaledValue;
    int nScaledOther;
    unsigned int uFlags;
    int w0c;
    u8 b10;
    u8 pad11[3];
    VecFx32 vExtent;
    int w20;
    u8 pad24;
    u8 b25;
    u8 pad26[2];
};

struct PoseNode {
    u8 pad00[0x80];
    u16 uHeading;
};

struct AttackRig {
    unsigned int uAlternateFlags;
    u8 pad004[0x35c];
    int nPattern;
};

struct GlobalState {
    u8 pad0000[0x2c2c];
    struct AttackRig attackRig;
};

struct Actor {
    unsigned int uActorFlags;
    u8 pad0004[0x1c];
    struct PoseNode *pPose;
    u8 pad0024[0x42];
    short nOwnerId;
    u8 pad0068[0x412];
    u8 bAttackLatch;
    u8 bAttackLatchAux;
    u8 pad047c[0x334];
    int nAnimationFrame;
    u8 pad07b4[0x1f08];
    unsigned int uAttackFlags;
    int nAttackMode;
    u8 bBurstResult;
    u8 pad26c5[3];
    VecFx32 vBurstOrigin;
    u8 pad26d4[0x500];
    unsigned int uAttackAnchor;
};

extern void Ov022_FillEightHalvesMinus1At0x2bd4(int self);
extern void func_ov022_020ad44c(VecFx32 *out, int self);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Ov022_ScaleMoveDamage(int self, int spin, int *a, int *b);
extern int Ov022_RunReachHandlers(struct Actor *self, struct EmitPair *emit, struct Params *params);
extern void Ov022_MarshalNetworkRecord(int self, int record, VecFx32 *at, int scale, unsigned int angle, int kind);
extern struct GlobalState *data_ov103_020bc120;
extern short data_0203d210[];

static inline int FinalizeParams(struct Params *p)
{
    p->w0c = 0;
    p->vExtent.x = 0xa00;
    p->vExtent.z = 0xa00;
    p->w20 = 0;
    p->b10 = 0;
    p->vExtent.y = 0x66;
    p->b25 &= ~1;
    int value = p->b25;
    value &= ~2;
    p->b25 = value;
    return value;
}

int Ov103_EmitAttackBurst(struct Actor *self)
{
    struct EmitPair emit;
    struct Params prm;
    VecFx32 dir;
    VecFx32 anchor;
    VecFx32 tmp;
    int rem;
    int next;
    u8 *rigBytes;
    int idx;
    int spin;
    int angle;
    angle = self->nAnimationFrame;
    rigBytes = (u8 *)data_ov103_020bc120 + 0x2c2c;
    rem = angle % 3;
    next = 0;
    if (rem == 0) {
        Ov022_FillEightHalvesMinus1At0x2bd4((int)self);
    }
    func_ov022_020ad44c(&anchor, (int)self);
    angle = (u16)(self->pPose->uHeading - 0x8000);
    idx = angle >> 4;
    dir.x = -data_0203d210[idx * 2];
    dir.z = -data_0203d210[idx * 2 + 1];
    dir.y = 0;
    ScaleVec3Fx12(0x800, &dir, &tmp);
    VEC_Add(&tmp, &anchor, &emit.vPosA);
    ScaleVec3Fx12(-0x1800, &dir, &tmp);
    VEC_Add(&tmp, &anchor, &emit.vPosB);
    emit.nRange = 0x1800;
    emit.pAnchor = &self->uAttackAnchor;
    emit.nOwner = self->nOwnerId;
    emit.nFlags24 = 0;
    prm.uFlags = 0x205;
    switch (((struct AttackRig *)rigBytes)->nPattern) {
    case 0:
        spin = 0x1b00;
        break;
    case 1:
        spin = 0x2580;
        break;
    case 2:
        spin = 0x1fc0;
        break;
    }
    if (((struct AttackRig *)rigBytes)->uAlternateFlags != 0) {
        prm.uFlags |= 0x420;
    }
    Ov022_ScaleMoveDamage((int)self, spin, &prm.nScaledValue, &prm.nScaledOther);
    spin = FinalizeParams(&prm);
    if (Ov022_RunReachHandlers(self, &emit, &prm) != 0) {
        spin = 0;
        if ((self->uAttackFlags & 1) == 0) {
            if (((struct AttackRig *)rigBytes)->uAlternateFlags != 0) {
                spin = 1;
            }
            Ov022_MarshalNetworkRecord((int)self, 5, &self->vBurstOrigin, 0x1000, angle, spin);
        }
    }
    switch (self->bBurstResult) {
    case 4:
        if (self->nAttackMode != 2) {
            next = 2;
        }
        break;
    case 2:
        next = 1;
        break;
    case 1:
        if (!(int)(*(unsigned long long *)self & 0x10000)) {
            self->bAttackLatch = 3;
            self->bAttackLatchAux = 0;
        }
        if ((self->uAttackFlags & 1) != 0) {
            next = 2;
        } else if (((struct AttackRig *)rigBytes)->nPattern != 2) {
            next = 1;
        }
        break;
    }
    return next;
}
