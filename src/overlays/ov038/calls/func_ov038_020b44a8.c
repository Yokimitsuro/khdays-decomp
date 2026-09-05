/* Fires the ov038 charge burst once the gauge reaches the window the current
 * scene stage asks for: stage 0 and 1 want exactly 0x15000, stage 2 anywhere in
 * [0x1b000, 0x21000] and rings a cue right at 0x1e000. Each stage picks its own
 * spin, kind and scale.
 *
 * It then fills the emitter block, points it backwards along the actor's own
 * heading through the shared sin/cos table, builds the burst parameters with a
 * scaled extent, and submits them. If the submit takes and neither of the two
 * busy bits is set, it also pushes the muzzle position out as event 5. */
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

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

extern void func_ov022_020a2954(int self);
extern void func_ov022_020ad44c(struct Emit *emit, int self);
extern void func_ov022_020a23a4(int self, int spin, void *a, void *b);
extern void func_01ffa724(int scale, const struct Vec3 *v, struct Vec3 *out);
extern int func_ov022_020a0fb8(int self, struct Emit *emit, void *params);
extern void func_ov022_020ad208(int self, int event, struct Vec3 *pos, int range,
                                int angle, int flag);

extern int data_ov038_020b4ca0;
extern short data_0203d210[];

void func_ov038_020b44a8(int self)
{
    struct Emit emit;
    struct Params prm;
    struct Vec3 vMuzzle;
    int scene = data_ov038_020b4ca0 + 0x2c + 0x2c00;
    int bFire = 0;
    int nKind;
    int nSpin;
    int nScale;
    int angle;
    int idx;
    int nFlag;

    switch (*(int *)(scene + 4)) {
    case 0:
        if (*(int *)(self + 0x7b0) == 0x15000) {
            bFire = 1;
            nSpin = 0x1c00;
            nKind = 0x2000;
            nScale = 0x800;
        }
        break;
    case 1:
        if (*(int *)(self + 0x7b0) == 0x15000) {
            bFire = 1;
            nSpin = 0x2400;
            nKind = 0x3000;
            nScale = 0x1000;
        }
        break;
    case 2:
        if (*(int *)(self + 0x7b0) >= 0x1b000 && *(int *)(self + 0x7b0) <= 0x21000) {
            if (*(int *)(self + 0x7b0) == 0x1e000) {
                func_ov022_020a2954(self);
            }
            bFire = 1;
            nKind = 0x4000;
            nSpin = 0x2900;
            nScale = 0x2000;
        }
        break;
    }
    if (bFire == 0) {
        return;
    }

    func_ov022_020ad44c(&emit, self);
    angle = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000);
    idx = angle >> 4;
    emit.nKind = nKind;
    emit.nDirX = -data_0203d210[idx * 2];
    emit.nDirZ = -data_0203d210[idx * 2 + 1];
    emit.nDirY = 0;
    emit.nOwner = *(short *)(self + 0x66);
    emit.nRange = 0x1000;
    emit.pAnchor = (char *)self + 0x2bd4;
    emit.nFlags28 = 0;
    func_ov022_020a23a4(self, nSpin, &prm.pA, &prm.pB);

    prm.uFlags = 0x205;
    if (*(int *)(scene + 4) == 2 && (*(unsigned int *)self & 0x10000) == 0) {
        *(u8 *)(self + 0x47a) = 3;
        *(u8 *)(self + 0x47b) = 1;
        prm.uFlags |= 0x420;
    }
    prm.w0c = 0;
    prm.vExtent.x = 0xa00;
    prm.vExtent.y = 0x66;
    prm.vExtent.z = 0xa00;
    func_01ffa724(nScale, &prm.vExtent, &prm.vExtent);
    prm.w20 = 0;
    prm.b25 &= ~1;
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
    vMuzzle = *(struct Vec3 *)(self + 0x26c8);
    nFlag = 0;
    if (*(int *)(scene + 4) == 2) {
        nFlag = 1;
    }
    func_ov022_020ad208(self, 5, &vMuzzle, 0x1000, angle, nFlag);
    if (*(int *)(scene + 4) == 2) {
        return;
    }
    if ((u32)(((u64)*(u32 *)self) & 0x10000ULL) == 0) {
        *(u8 *)(self + 0x47a) = 3;
        *(u8 *)(self + 0x47b) = 0;
    }
}
