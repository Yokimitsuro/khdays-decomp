/* Ov022_TurnAwayFromDrift -- face the actor away from the way it is drifting.
 *
 * The drift is flattened and normalised, and the angle back along it is the
 * aim. If the actor is already looking within a quarter turn of that aim it
 * keeps it, otherwise it takes the opposite; either way one of two actions is
 * picked at random for the pair.
 *
 * The new angle only reaches the node when the node is not already holding one
 * of its own. The three drift words are cleared, the step is reset, and the
 * actor is put back through its state entry.
 */

#include "nitro/types.h"
#include "nitro/fx_types.h"

struct ActorNode {
    unsigned int nFlags;         /* 0x00 */
    u16 nAnimFlags;              /* 0x04 */
    u8 pad006[0x7a];
    u16 nAngle;                  /* 0x80 */
};

struct Actor;

typedef void (*ActorAction)(struct Actor *pActor, int nAction);

struct Actor {
    u8 pad0000[0x20];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad0024[0x40];
    u16 nField64;                /* 0x0064 */
    u8 pad0066[0x416];
    VecFx32 vecDrift;     /* 0x047c */
    u8 pad0488[0x1dc];
    ActorAction pfnPreDraw;      /* 0x0664 */
    u8 pad0668[0x30];
    int nStateWordA;             /* 0x0698 */
    int nStateWordB;             /* 0x069c */
    int nStateWordC;             /* 0x06a0 */
};

extern int VEC_Mag(VecFx32 *pVec);
extern int VEC_Normalize(VecFx32 *pOut, VecFx32 *pIn);
extern short FX_Atan2Idx(int x, int y);
extern int Session_RandNextScaled(int nRange);
extern void func_ov022_02097038(struct Actor *pActor, int nArg);

#define NODE_ANGLE_HELD 0x20
#define HALF_TURN 0x8000
#define QUARTER_TURN 0x4000
#define STEP_RESET 0x1800

void Ov022_TurnAwayFromDrift(struct Actor *pActor, int nArg1, int nArg2, int nArg3)
{
    VecFx32 vecDrift;
    struct ActorNode *pNode;
    u16 nFacing;
    u16 nAim;
    int nDiff;
    int nAction;
    int nRand;

    nFacing = pActor->pNode->nAngle - HALF_TURN;
    vecDrift = pActor->vecDrift;
    vecDrift.y = 0;
    if (VEC_Mag(&vecDrift) != 0) {
        VEC_Normalize(&vecDrift, &vecDrift);
    }
    nAim = FX_Atan2Idx(-vecDrift.x, -vecDrift.z);
    nDiff = (u16)(nAim - nFacing);
    if (nDiff > HALF_TURN) {
        nDiff = (u16)(0x10000 - nDiff);
    }
    nRand = Session_RandNextScaled(2);
    if (nDiff > QUARTER_TURN) {
        nAction = (nRand & 1) != 0 ? 0xb : 9;
        nAim = nAim + HALF_TURN;
    } else {
        nAction = (nRand & 1) != 0 ? 0xa : 8;
    }
    pActor->pfnPreDraw(pActor, nAction);
    pNode = pActor->pNode;
    if ((pNode->nFlags & NODE_ANGLE_HELD) == 0) {
        pNode->nAngle = nAim + HALF_TURN;
        pNode->nAnimFlags = pNode->nAnimFlags | 0x20;
    }
    pActor->nStateWordC = 0;
    pActor->nStateWordB = 0;
    pActor->nStateWordA = 0;
    pActor->nField64 = STEP_RESET;
    func_ov022_02097038(pActor, 0);
}
