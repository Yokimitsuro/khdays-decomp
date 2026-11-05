/* Releases the ov037 enemy's charge (x4: ov037/055/075/092): samples the anchor position, builds
 * the backwards heading through the shared sin/cos table and places the two emitter positions
 * 0x2000 either side of the anchor along it (range 0x1400, anchored at +0x2bd4), builds the
 * burst parameters with spin 0x1d20, flags 0x625 and the fixed 0xa00/0x66/0xa00 extent, and
 * submits the pair; if the submit takes and busy bit 0 of +0x26bc is clear, it queues effect
 * record 5 on the emitter at +0x2648: the +0x26c8 muzzle jittered by 0x99a/0x4cd/0x99a, the
 * actor's heading, a random variant, cue 0xcf, kind 2. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

struct EmitPair {
    VecFx32 vPosB;
    VecFx32 vPosA;
    int nOwner;
    int nRange;
    void *pAnchor;
    int nFlags24;
};

struct EffectRecord {
    u8 nOwnerId;
    u8 pad01[3];
    VecFx32 vPos;
    u16 nScale;
    u16 nAngle;
    u8 nVariant;
    u8 b15;
    u16 nCue;
    u16 nKind;
    u8 pad1a[2];
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

extern void func_ov022_020ad44c(VecFx32 *out, char *self);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Ov022_ScaleMoveDamage(char *self, int spin, void *a, void *b);
extern int Ov022_RunReachHandlers(char *self, struct EmitPair *emit, void *params);
extern void Ov022_SendAimMessage(char *emitter, int slot, struct EffectRecord *rec);
extern short data_0203d210[];

void Ov076_ReleaseCharge(char *self)
{
    struct EmitPair emit;
    struct Params prm;
    VecFx32 tmp;
    VecFx32 dir;
    VecFx32 anchor;
    VecFx32 at;
    struct EffectRecord rec;
    int angle;
    int idx;
    int variant;
    int randomOffset;

    angle = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000);
    func_ov022_020ad44c(&anchor, self);
    idx = angle >> 4;
    dir.x = -data_0203d210[idx * 2];
    dir.z = -data_0203d210[idx * 2 + 1];
    dir.y = 0;
    ScaleVec3Fx12(0x2000, &dir, &tmp);
    VEC_Add(&tmp, &anchor, &emit.vPosA);
    ScaleVec3Fx12(-0x2000, &dir, &tmp);
    VEC_Add(&tmp, &anchor, &emit.vPosB);
    emit.nRange = 0x1400;
    emit.pAnchor = self + 0x2bd4;
    emit.nOwner = *(short *)(self + 0x66);
    emit.nFlags24 = 0;
    prm.uFlags = 0x625;
    Ov022_ScaleMoveDamage(self, 0x1d20, &prm.pA, &prm.pB);
    prm.w0c = 0;
    prm.w20 = 0;
    prm.b10 = 0;
    prm.vExtent.x = 0xa00;
    prm.vExtent.z = 0xa00;
    prm.vExtent.y = 0x66;
    prm.b25 &= ~1;
    prm.b25 &= ~2;
    if (Ov022_RunReachHandlers(self, &emit, &prm) == 0) {
        return;
    }
    if ((*(unsigned int *)(self + 0x26bc) & 1) != 0) {
        return;
    }
    variant = Session_RandNextScaled(3);
    at = *(VecFx32 *)(self + 0x2c8 + 0x2400);
    randomOffset = Session_RandNext() - 0x800;
    at.x += (int)(((long long)randomOffset * 0x99a + 0x800) >> 12);
    randomOffset = Session_RandNext() - 0x800;
    at.y += (int)(((long long)randomOffset * 0x4cd + 0x800) >> 12);
    randomOffset = Session_RandNext() - 0x800;
    at.z += (int)(((long long)randomOffset * 0x99a + 0x800) >> 12);
    rec.nOwnerId = *(u8 *)(self + 9);
    rec.vPos = at;
    rec.nScale = 0x1000;
    rec.nAngle = angle;
    rec.nVariant = variant;
    rec.b15 = 1;
    rec.nCue = 0xcf;
    rec.nKind = 2;
    Ov022_SendAimMessage(self + 0x248 + 0x2400, 5, &rec);
}
