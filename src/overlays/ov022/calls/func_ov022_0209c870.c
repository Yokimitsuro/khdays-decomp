/* Ov022_DropGroundMark -- cast the actor's mark straight down and place it.
 *
 * Only an actor with flag bit 0, without bit 9 and with a slot index casts:
 * from its aim point half a unit downward through its node. A hit lands the
 * mark, unless the surface's owner reports it is not solid. Then, with flag
 * bit 6, the hit point becomes the mark's position, its shade comes from how
 * close the ground is (ten times the inverse of the 3-unit gap, never below
 * four), its angle follows the node's, and a draw-suppressed actor pushes the
 * mark through.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct HitOwner {
    u8 pad000[0x158];
    int nSolid;                      /* 0x158 */
};

struct HitState {
    u8 pad00[0x28];
    struct HitOwner *pOwner;         /* 0x28 */
};

struct Hit {
    void *pModel;                    /* 0x00 */
    void *pInfo;                     /* 0x04 */
    struct HitState *pState;         /* 0x08 */
    int nNearestHit;                 /* 0x0c */
};

/* Ov022ActorNode */
struct ActorNode {
    u8 pad00[0x80];
    u16 nAngle;                      /* 0x80 */
};

/* Ov022GroundMark: the shadow mark under the actor */
struct GroundMark {
    struct VecFx32 vecPos;           /* 0x00 */
    u8 pad0c[8];
    u8 nShade;                       /* 0x14 five bits */
    u8 pad15[1];
    short nAngle;                    /* 0x16 */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                      /* 0x0000 */
    u8 pad0008[0x18];
    struct ActorNode *pNode;         /* 0x0020 */
    u8 pad0024[0x42];
    short nSlotIndex;                /* 0x0066 */
    u8 pad0068[0x424];
    struct VecFx32 vecAim;           /* 0x048c */
    u8 pad0498[0x1fc];
    u8 bSuppressDraw : 1;            /* 0x0694 bit 0 */
    u8 nRest694 : 7;
    u8 pad0695[0x1fd7];
    struct GroundMark mark;          /* 0x266c */
};

#define FLAG_BIT0 (1ULL << 0)
#define FLAG_BIT6 (1ULL << 6)
#define FLAG_BIT9 (1ULL << 9)
#define DROP_HALF (-0x8000)
#define GAP_FULL 0x3000
#define SHADE_SCALE 10
#define SHADE_MIN 0x4000
#define ANGLE_BIAS 0x8000

extern struct Hit *func_0202c268(u16 nMask, struct VecFx32 *pFrom, struct VecFx32 *pDir,
                                 struct ActorNode *pNode);
extern void func_01ffd0e8(int nScale, struct VecFx32 *pDir, struct VecFx32 *pBase,
                          struct VecFx32 *pOut);
extern int FX_Inv(int nNumerator, int nDenominator);
extern void func_0202df34(struct VecFx32 *pMark);

void func_ov022_0209c870(struct Actor *pActor)
{
    struct VecFx32 vecHit;
    struct VecFx32 vecFrom;
    struct VecFx32 vecDown;
    int bLanded;
    int nSlot;
    struct Hit *pHit;
    int nGap;
    int nShade;

    bLanded = 0;
    if ((pActor->nFlags & FLAG_BIT0) == 0) {
        return;
    }
    if ((pActor->nFlags & FLAG_BIT9) != 0) {
        return;
    }
    nSlot = pActor->nSlotIndex;
    if (nSlot < 0) {
        return;
    }
    vecFrom = pActor->vecAim;
    vecDown.z = 0;
    vecDown.x = 0;
    vecDown.y = DROP_HALF;
    pHit = func_0202c268((u16)nSlot, &vecFrom, &vecDown, pActor->pNode);
    if (pHit != 0) {
        bLanded = 1;
        func_01ffd0e8(pHit->nNearestHit, &vecDown, &vecFrom, &vecHit);
        if (pHit->pState != 0 && pHit->pState->pOwner->nSolid == 0) {
            bLanded = 0;
        }
    }
    if (bLanded == 0) {
        return;
    }
    if ((pActor->nFlags & FLAG_BIT6) == 0) {
        return;
    }
    pActor->mark.vecPos = vecHit;
    nGap = pActor->vecAim.y - vecHit.y;
    if (nGap < 0) {
        nGap = -nGap;
    }
    nShade = FX_Inv(GAP_FULL - nGap, GAP_FULL) * SHADE_SCALE;
    if (nShade < SHADE_MIN) {
        nShade = SHADE_MIN;
    }
    pActor->mark.nAngle = pActor->pNode->nAngle - ANGLE_BIAS;
    pActor->mark.nShade = (u8)(nShade >> 12) & 0x1f;
    if (pActor->bSuppressDraw) {
        func_0202df34(&pActor->mark.vecPos);
    }
}
