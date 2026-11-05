/* Fires the ov033 enemy's recoil burst (x4: ov033/051/071/089) exactly when the +0x7b0 timer
 * reads 0x9000: fills the emitter block from the anchor sampler, points it backwards along the
 * actor's heading through the shared sin/cos table (kind 0x3000, range 0x1000, no anchor),
 * builds the burst parameters with spin 0x2080 and the fixed 0xa00/0x66/0xa00 extent, and
 * submits them; if the submit takes and neither busy bit of +0x26bc is set, it plays 0xca at
 * +0x26c8. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

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

extern void func_ov022_020ad44c(struct Emit *emit, char *self);
extern void Ov022_ScaleMoveDamage(char *self, int spin, void *a, void *b);
extern int Ov022_RunCommandHandlers(char *self, struct Emit *emit, void *params);
extern void func_ov022_020ad28c(char *self, char *pos, int nSound, int nVariant);
extern short data_0203d210[];

void Ov051_FireRecoilBurst(char *self)
{
    struct Emit emit;
    struct Params prm;
    int angle;
    int idx;

    if (*(int *)(self + 0x7b0) != 0x9000) {
        return;
    }
    func_ov022_020ad44c(&emit, self);
    angle = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000);
    idx = angle >> 4;
    emit.nDirX = -data_0203d210[idx * 2];
    emit.nDirZ = -data_0203d210[idx * 2 + 1];
    emit.nDirY = 0;
    emit.nKind = 0x3000;
    emit.nOwner = *(short *)(self + 0x66);
    emit.nRange = 0x1000;
    emit.pAnchor = 0;
    emit.nFlags28 = 0;
    Ov022_ScaleMoveDamage(self, 0x2080, &prm.pA, &prm.pB);
    prm.uFlags = 0x205;
    prm.w0c = 0;
    prm.vExtent.x = 0xa00;
    prm.vExtent.y = 0x66;
    prm.vExtent.z = 0xa00;
    prm.w20 = 0;
    prm.b25 &= ~1;
    prm.b25 &= ~2;
    prm.b10 = 0;
    if (Ov022_RunCommandHandlers(self, &emit, &prm) == 0) {
        return;
    }
    if ((*(unsigned int *)(self + 0x26bc) & 1) != 0) {
        return;
    }
    if ((*(unsigned int *)(self + 0x26bc) & 0x40) != 0) {
        return;
    }
    func_ov022_020ad28c(self, self + 0x2c8 + 0x2400, 0xca, 2);
}
