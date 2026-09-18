/* Fires the ov034 enemy's rapid burst (x4: ov034/052/072/090) on every third tick of the +0x7b0
 * timer: fills the emitter block from the anchor sampler, points it backwards along the actor's
 * heading through the shared sin/cos table (kind 0x2000, range 0x1000, no anchor), builds the
 * burst parameters with spin 0x80, flags 0x205, the fixed 0xa00/0x66/0xa00 extent and the extra
 * word set, and submits them; if the submit takes and neither busy bit of +0x26bc is set, it
 * marshals record 0 (kind 1) at the +0x26c8 muzzle with the actor's heading. */
typedef unsigned short u16;
typedef unsigned char u8;

struct Vec3 { int x, y, z; };

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
    struct Vec3 vExtent;
    int w20;
    u8 pad24;
    u8 b25;
    u8 pad26[2];
};

extern void func_ov022_020ad44c(struct Emit *emit, char *self);
extern void func_ov022_020a23a4(char *self, int spin, void *a, void *b);
extern int func_ov022_020a0fb8(char *self, struct Emit *emit, void *params);
extern void func_ov022_020ad208(char *self, int record, struct Vec3 *at, int scale, unsigned int angle, int kind);
extern short data_0203d210[];

void func_ov053_020b73f8(char *self)
{
    struct Vec3 at;
    struct Emit emit;
    struct Params prm;
    int angle;
    int idx;

    if (*(int *)(self + 0x7b0) % 3 != 0) {
        return;
    }
    func_ov022_020ad44c(&emit, self);
    angle = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000);
    idx = angle >> 4;
    emit.nDirX = -data_0203d210[idx * 2];
    emit.nDirZ = -data_0203d210[idx * 2 + 1];
    emit.nDirY = 0;
    emit.nKind = 0x2000;
    emit.nOwner = *(short *)(self + 0x66);
    emit.nRange = 0x1000;
    emit.pAnchor = 0;
    emit.nFlags28 = 0;
    func_ov022_020a23a4(self, 0x80, &prm.pA, &prm.pB);
    prm.uFlags = 0x205;
    prm.w0c = 0;
    prm.vExtent.x = 0xa00;
    prm.vExtent.y = 0x66;
    prm.vExtent.z = 0xa00;
    prm.w20 = 1;
    prm.b25 &= ~1;
    prm.b25 &= ~2;
    prm.b10 = 0;
    if (func_ov022_020a0fb8(self, &emit, &prm) == 0) {
        return;
    }
    if ((*(unsigned int *)(self + 0x26bc) & 1) != 0) {
        return;
    }
    if ((*(unsigned int *)(self + 0x26bc) & 0x40) != 0) {
        return;
    }
    at = *(struct Vec3 *)(self + 0x2c8 + 0x2400);
    func_ov022_020ad208(self, 0, &at, 0x1000, angle, 1);
}
