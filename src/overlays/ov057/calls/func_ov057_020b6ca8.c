/* Fires the ov057 charge burst once the gauge reaches the window the current
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
    int burstKind;
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

extern void func_ov022_020a2954(int pActor);
extern void func_ov022_020ad44c(struct Emit *emit, int pActor);
extern void func_ov022_020a23a4(int pActor, int spin, void *a, void *b);
extern void func_01ffa724(int scale, const struct Vec3 *v, struct Vec3 *out);
extern int func_ov022_020a0fb8(int pActor, struct Emit *emit, void *params);
extern void func_ov022_020ad208(int pActor, int event, struct Vec3 *pos, int range,
                                int heading, int flag);

extern int data_ov057_020b74a0;
extern short data_0203d210[];

void func_ov057_020b6ca8(int pActor)
{
    struct Emit emit;
    struct Params prm;
    struct Vec3 vMuzzle;
    int pSceneBlock = data_ov057_020b74a0 + 0x2c + 0x2c00;
    int fireBurst = 0;
    int burstKind;
    int burstSpin;
    int burstScale;
    int heading;
    int sinCosIndex;
    int eventFlag;

    switch (*(int *)(pSceneBlock + 4)) {
    case 0:
        if (*(int *)(pActor + 0x7b0) == 0x15000) {
            fireBurst = 1;
            burstSpin = 0x1c00;
            burstKind = 0x2000;
            burstScale = 0x800;
        }
        break;
    case 1:
        if (*(int *)(pActor + 0x7b0) == 0x15000) {
            fireBurst = 1;
            burstSpin = 0x2400;
            burstKind = 0x3000;
            burstScale = 0x1000;
        }
        break;
    case 2:
        if (*(int *)(pActor + 0x7b0) >= 0x1b000 && *(int *)(pActor + 0x7b0) <= 0x21000) {
            if (*(int *)(pActor + 0x7b0) == 0x1e000) {
                func_ov022_020a2954(pActor);
            }
            fireBurst = 1;
            burstKind = 0x4000;
            burstSpin = 0x2900;
            burstScale = 0x2000;
        }
        break;
    }
    if (fireBurst == 0) {
        return;
    }

    func_ov022_020ad44c(&emit, pActor);
    heading = (u16)(*(u16 *)(*(char **)(pActor + 0x20) + 0x80) - 0x8000);
    sinCosIndex = heading >> 4;
    emit.burstKind = burstKind;
    emit.nDirX = -data_0203d210[sinCosIndex * 2];
    emit.nDirZ = -data_0203d210[sinCosIndex * 2 + 1];
    emit.nDirY = 0;
    emit.nOwner = *(short *)(pActor + 0x66);
    emit.nRange = 0x1000;
    emit.pAnchor = (char *)pActor + 0x2bd4;
    emit.nFlags28 = 0;
    func_ov022_020a23a4(pActor, burstSpin, &prm.pA, &prm.pB);

    prm.uFlags = 0x205;
    if (*(int *)(pSceneBlock + 4) == 2 && (*(unsigned int *)pActor & 0x10000) == 0) {
        *(u8 *)(pActor + 0x47a) = 3;
        *(u8 *)(pActor + 0x47b) = 1;
        prm.uFlags |= 0x420;
    }
    prm.w0c = 0;
    prm.vExtent.x = 0xa00;
    prm.vExtent.y = 0x66;
    prm.vExtent.z = 0xa00;
    func_01ffa724(burstScale, &prm.vExtent, &prm.vExtent);
    prm.w20 = 0;
    prm.b25 &= ~1;
    prm.b10 = 0;

    if (func_ov022_020a0fb8(pActor, &emit, &prm) == 0) {
        return;
    }
    if ((*(unsigned int *)(pActor + 0x26bc) & 1) != 0) {
        return;
    }
    if ((*(unsigned int *)(pActor + 0x26bc) & 0x40) != 0) {
        return;
    }
    vMuzzle = *(struct Vec3 *)(pActor + 0x26c8);
    eventFlag = 0;
    if (*(int *)(pSceneBlock + 4) == 2) {
        eventFlag = 1;
    }
    func_ov022_020ad208(pActor, 5, &vMuzzle, 0x1000, heading, eventFlag);
    if (*(int *)(pSceneBlock + 4) == 2) {
        return;
    }
    if ((u32)(((u64)*(u32 *)pActor) & 0x10000ULL) == 0) {
        *(u8 *)(pActor + 0x47a) = 3;
        *(u8 *)(pActor + 0x47b) = 0;
    }
}
