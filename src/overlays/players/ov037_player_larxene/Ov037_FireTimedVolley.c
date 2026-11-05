#pragma opt_propagation off
/*
 * Fire the timed volley: on every third tick of the +0x7b0 timer that lands on one of the
 * trigger frames (0x6000, 0x9000, 0xf000, 0x1b000, 0x1e000, 0x21000, 0x27000, 0x2a000, 0x2d000
 * fire one shot; 0x12000, 0x15000 and 0x24000 fire two), fills the emitter block from the anchor
 * sampler, points it backwards along the actor's heading through the shared sin/cos table
 * (kind 0x2800, range 0x800, no anchor), builds the burst parameters with spin 0x800, flags
 * 0x205 and the fixed 0xa00/0x66/0xa00 extent, then per shot: submits them and, if the submit
 * takes and neither busy bit of +0x26bc is set, spawns an effect record (variant from
 * 020307f4(3), position = +0x26c8 jittered by +-0x99a/+-0x4cd/+-0x99a, scale 0x1000, the heading,
 * owner +0x7a6, tag 4) on the +0x2648 pool and, unless bit 16 of the flags is set, queues
 * action 3.
 *
 * Three spellings carry the match (all catalogued): `ok` is initialised at its declaration but
 * `count` only after the tick test -- the ROM materialises the 1 in the predicated return's
 * shadow (`addne sp ; mov r0,#1 ; popne`) and lets `count` borrow it afterwards; with `count = 1`
 * at the declaration the borrow drags `ok` above the `subs` and it lands in r1. The kind 0x2800
 * is a `register const` created BEFORE the heading chain (propagation off keeps its node there)
 * and stored after nDirY, which is what holds it in r1 across the table lookups. And the flag
 * test is the 64-bit spelling from the ov044 twin: the low word of a u64 AND loads into r1.
 */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

struct Emit {
    char pad00[0xc];
    int nKind;
    int nOwner;
    int nDirX;
    int nDirY;
    int nDirZ;
    int nRange;
    void *pAnchor;
    int nFlags28;
};

struct Params {
    void *pA;
    void *pB;
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

struct EffectRec {
    u8 bSlot;
    u8 pad01[3];
    VecFx32 vPos;
    u16 uScale;
    short nAngle;
    u8 bVariant;
    u8 b15;
    short nOwner;
    u16 uTag;
};

extern void func_ov022_020ad44c(struct Emit *emit, char *self);
extern void Ov022_ScaleMoveDamage(char *self, int spin, void *a, void *b);
extern int Ov022_RunCommandHandlers(char *self, struct Emit *emit, void *params);
extern void Ov022_SendAimMessage(void *pool, int n, struct EffectRec *rec);
extern short data_0203d210[];

void Ov037_FireTimedVolley(char *self)
{
    struct Emit emit;
    struct Params prm;
    VecFx32 at;
    struct EffectRec rec;
    int angle;
    int idx;
    int variant;
    int i;
    int r;
    int timer = *(int *)(self + 0x7b0);
    int ok = 1;
    int count;

    if (timer % 3 != 0) {
        return;
    }
    count = 1;
    switch (timer) {
    case 0x6000:
    case 0x9000:
    case 0xf000:
    case 0x1b000:
    case 0x1e000:
    case 0x21000:
    case 0x27000:
    case 0x2a000:
    case 0x2d000:
        break;
    case 0x12000:
    case 0x15000:
    case 0x24000:
        count = 2;
        break;
    default:
        ok = 0;
        break;
    }
    if (ok == 0) {
        return;
    }
    func_ov022_020ad44c(&emit, self);
    register const int kind = 0x2800;
    angle = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000);
    idx = angle >> 4;
    emit.nDirX = -data_0203d210[idx * 2];
    emit.nDirZ = -data_0203d210[idx * 2 + 1];
    emit.nDirY = 0;
    emit.nKind = kind;
    emit.nOwner = *(short *)(self + 0x66);
    emit.nRange = 0x800;
    emit.pAnchor = 0;
    emit.nFlags28 = 0;
    prm.uFlags = 0x205;
    Ov022_ScaleMoveDamage(self, 0x800, &prm.pA, &prm.pB);
    prm.w0c = 0;
    prm.vExtent.x = 0xa00;
    prm.vExtent.y = 0x66;
    prm.vExtent.z = 0xa00;
    prm.w20 = 0;
    prm.b25 &= ~1;
    prm.b25 &= ~2;
    prm.b10 = 0;
    for (i = 0; i < count; i++) {
        if (Ov022_RunCommandHandlers(self, &emit, &prm) == 0) {
            continue;
        }
        if ((*(unsigned int *)(self + 0x26bc) & 1) != 0) {
            continue;
        }
        if ((*(unsigned int *)(self + 0x26bc) & 0x40) != 0) {
            continue;
        }
        variant = Session_RandNextScaled(3);
        at = *(VecFx32 *)(self + 0x2c8 + 0x2400);
        r = Session_RandNext() - 0x800;
        at.x += (int)(((s64)r * 0x99a + 0x800) >> 12);
        r = Session_RandNext() - 0x800;
        at.y += (int)(((s64)r * 0x4cd + 0x800) >> 12);
        r = Session_RandNext() - 0x800;
        at.z += (int)(((s64)r * 0x99a + 0x800) >> 12);
        rec.bSlot = *(u8 *)(self + 9);
        rec.vPos = at;
        rec.uScale = 0x1000;
        rec.nAngle = angle;
        rec.bVariant = variant;
        rec.b15 = 1;
        rec.nOwner = *(short *)(self + 0x7a6);
        rec.uTag = 4;
        Ov022_SendAimMessage(self + 0x248 + 0x2400, 5, &rec);
        if ((unsigned int)(((unsigned long long)*(unsigned int *)self) & 0x10000ULL) == 0) {
            *(u8 *)(self + 0x47a) = 3;
            *(u8 *)(self + 0x47b) = 0;
        }
    }
}
