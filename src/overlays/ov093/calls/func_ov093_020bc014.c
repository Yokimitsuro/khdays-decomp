/* Releases the ov037 enemy's charge (x4: ov037/055/075/092): samples the anchor position, builds
 * the backwards heading through the shared sin/cos table and places the two emitter positions
 * 0x2000 either side of the anchor along it (range 0x1400, anchored at +0x2bd4), builds the
 * burst parameters with spin 0x1d20, flags 0x625 and the fixed 0xa00/0x66/0xa00 extent, and
 * submits the pair; if the submit takes and busy bit 0 of +0x26bc is clear, it queues effect
 * record 5 on the emitter at +0x2648: the +0x26c8 muzzle jittered by 0x99a/0x4cd/0x99a, the
 * actor's heading, a random variant, cue 0xcf, kind 2. */
typedef unsigned short u16;
typedef unsigned char u8;

struct Vec3 { int x, y, z; };

struct EmitPair {
    struct Vec3 vPosB;
    struct Vec3 vPosA;
    int nOwner;
    int nRange;
    void *pAnchor;
    int nFlags24;
};

struct EffectRecord {
    u8 nOwnerId;
    u8 pad01[3];
    struct Vec3 vPos;
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
    struct Vec3 vExtent;
    int w20;
    u8 pad24;
    u8 b25;
    u8 pad26[2];
};

extern void func_ov022_020ad44c(struct Vec3 *out, char *self);
extern void func_01ffa724(int scale, const struct Vec3 *v, struct Vec3 *out);
extern void VEC_Add(const struct Vec3 *a, const struct Vec3 *b, struct Vec3 *out);
extern void func_ov022_020a23a4(char *self, int spin, void *a, void *b);
extern int func_ov022_020a1064(char *self, struct EmitPair *emit, void *params);
extern int func_020307f4(int n);                                             /* Session_RandNextScaled */
extern int func_0203084c(void);                                              /* Session_RandNext */
extern void func_ov022_0209246c(char *emitter, int slot, struct EffectRecord *rec);
extern short data_0203d210[];

void func_ov093_020bc014(char *self)
{
    struct EmitPair emit;
    struct Params prm;
    struct Vec3 tmp;
    struct Vec3 dir;
    struct Vec3 anchor;
    struct Vec3 at;
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
    func_01ffa724(0x2000, &dir, &tmp);
    VEC_Add(&tmp, &anchor, &emit.vPosA);
    func_01ffa724(-0x2000, &dir, &tmp);
    VEC_Add(&tmp, &anchor, &emit.vPosB);
    emit.nRange = 0x1400;
    emit.pAnchor = self + 0x2bd4;
    emit.nOwner = *(short *)(self + 0x66);
    emit.nFlags24 = 0;
    prm.uFlags = 0x625;
    func_ov022_020a23a4(self, 0x1d20, &prm.pA, &prm.pB);
    prm.w0c = 0;
    prm.w20 = 0;
    prm.b10 = 0;
    prm.vExtent.x = 0xa00;
    prm.vExtent.z = 0xa00;
    prm.vExtent.y = 0x66;
    prm.b25 &= ~1;
    prm.b25 &= ~2;
    if (func_ov022_020a1064(self, &emit, &prm) == 0) {
        return;
    }
    if ((*(unsigned int *)(self + 0x26bc) & 1) != 0) {
        return;
    }
    variant = func_020307f4(3);
    at = *(struct Vec3 *)(self + 0x2c8 + 0x2400);
    randomOffset = func_0203084c() - 0x800;
    at.x += (int)(((long long)randomOffset * 0x99a + 0x800) >> 12);
    randomOffset = func_0203084c() - 0x800;
    at.y += (int)(((long long)randomOffset * 0x4cd + 0x800) >> 12);
    randomOffset = func_0203084c() - 0x800;
    at.z += (int)(((long long)randomOffset * 0x99a + 0x800) >> 12);
    rec.nOwnerId = *(u8 *)(self + 9);
    rec.vPos = at;
    rec.nScale = 0x1000;
    rec.nAngle = angle;
    rec.nVariant = variant;
    rec.b15 = 1;
    rec.nCue = 0xcf;
    rec.nKind = 2;
    func_ov022_0209246c(self + 0x248 + 0x2400, 5, &rec);
}
