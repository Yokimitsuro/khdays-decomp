/* Fires the ov033 enemy's forward burst (x4: ov033/051/071/089) on the ticks 0x3000, 0x6000,
 * 0x9000 and 0xc000 of the +0x7b0 timer (only checked every third tick): fills the emitter block
 * from the anchor sampler, points it backwards along the actor's heading through the shared
 * sin/cos table and pushes the emitter position one unit along that heading (kind 0x2000, range
 * 0x1000, no anchor), builds the burst parameters with spin 0xa00, flags 0x205 and the fixed
 * 0xa00/0x66/0xa00 extent, and submits them; if the submit takes and neither busy bit of
 * +0x26bc is set, it plays 0xca at +0x26c8. */
typedef unsigned short u16;
typedef unsigned char u8;

struct Vec3 { int x, y, z; };

struct Emit {
    struct Vec3 vPos;
    int nKind;
    int nOwner;
    struct Vec3 vDir;
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
extern void VEC_Add(const struct Vec3 *a, const struct Vec3 *b, struct Vec3 *out);
extern void func_ov022_020a23a4(char *self, int spin, void *a, void *b);
extern int func_ov022_020a0fb8(char *self, struct Emit *emit, void *params);
extern void func_ov022_020ad28c(char *self, char *pos, int nSound, int nVariant);
extern short data_0203d210[];

void func_ov051_020b6a20(char *self)
{
    struct Emit emit;
    struct Params prm;
    int angle;
    int idx;
    int bFire = 1;

    if (*(int *)(self + 0x7b0) % 3 != 0) {
        return;
    }
    switch (*(int *)(self + 0x7b0)) {
    case 0x3000:
    case 0x6000:
    case 0x9000:
    case 0xc000:
        break;
    default:
        bFire = 0;
        break;
    }
    if (bFire == 0) {
        return;
    }
    func_ov022_020ad44c(&emit, self);
    angle = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000);
    idx = angle >> 4;
    emit.vDir.x = -data_0203d210[idx * 2];
    emit.vDir.z = -data_0203d210[idx * 2 + 1];
    emit.vDir.y = 0;
    VEC_Add(&emit.vPos, &emit.vDir, &emit.vPos);
    emit.nKind = 0x2000;
    emit.nOwner = *(short *)(self + 0x66);
    emit.nRange = 0x1000;
    emit.pAnchor = 0;
    emit.nFlags28 = 0;
    func_ov022_020a23a4(self, 0xa00, &prm.pA, &prm.pB);
    prm.vExtent.x = 0xa00;
    prm.vExtent.z = 0xa00;
    prm.w0c = 0;
    prm.w20 = 0;
    prm.b10 = 0;
    prm.b25 &= ~1;
    prm.uFlags = 0x205;
    prm.vExtent.y = 0x66;
    prm.b25 &= ~2;
    if (func_ov022_020a0fb8(self, &emit, &prm) == 0) {
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
