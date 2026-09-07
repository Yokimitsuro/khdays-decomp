/* ov022: work out where the actor's sub-object should aim.
 *
 * The aim point is the actor's position with its height adjusted. Which
 * adjustment applies depends on the hit reaction: a knockdown (3) picks between
 * dropping to the facing height minus half the sub-object's own height and a
 * fifth of the actor's reach, while the launch reactions (0xe, 0xf, 0x13) use a
 * quarter of it. Everything else aims at the plain position.
 *
 * The reach is clamped to a floor before dividing, so a small actor still aims
 * somewhere sensible.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define AIM_MIN_REACH 0xb33

struct Vec3 {
    int x, y, z;
};

struct Bounds {
    u8 pad00[0x70];
    int nHeight;                  /* 0x70 */
};

struct Sub {
    u8 pad000[0x1d8];
    struct Bounds *pBounds;       /* 0x1d8 */
};

struct Actor {
    u8 pad000[0x48c];
    struct Vec3 vecPos;           /* 0x048c */
    u8 pad498[0x54];
    struct Sub *pSub;             /* 0x04ec */
    u8 pad4f0[0x1cc];
    int nHitReaction;             /* 0x06bc */
    u8 pad6c0[0x238];
    struct Vec3 vecFacing;        /* 0x08f8 */
    u8 pad904[0x1db4];
    int nReach;                   /* 0x26b8 */
    u8 pad26bc[0x4f6];
    signed char nAimMode;         /* 0x2bb2 */
};

void func_ov022_0209a3a4(struct Vec3 *pOut, struct Actor *pActor)
{
    struct Vec3 vecAim;
    int bUseFacing;
    int nOffset;
    int nReach;

    vecAim = pActor->vecPos;
    bUseFacing = 0;
    nOffset = 0;
    if (pActor->pSub == 0) {
        *pOut = vecAim;
        return;
    }
    switch (pActor->nHitReaction) {
    case 3:
        switch (pActor->nAimMode) {
        case -1:
        case 0:
        case 2:
            bUseFacing = 1;
            nOffset = -(pActor->pSub->pBounds->nHeight / 2);
            break;
        case 1:
            nReach = pActor->nReach;
            if (nReach < AIM_MIN_REACH) {
                nReach = AIM_MIN_REACH;
            }
            nOffset = nReach / 5;
            break;
        default:
            break;
        }
        break;
    case 0xe:
    case 0xf:
    case 0x13:
        nReach = pActor->nReach;
        if (nReach < AIM_MIN_REACH) {
            nReach = AIM_MIN_REACH;
        }
        nOffset = nReach / 4;
        break;
    default:
        break;
    }
    if (bUseFacing != 0) {
        vecAim.y = pActor->vecFacing.y;
    }
    if (nOffset != 0) {
        vecAim.y += nOffset;
    }
    *pOut = vecAim;
}
