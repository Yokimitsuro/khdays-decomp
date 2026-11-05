/* ov022: the actor's per-frame tick.
 *
 * Snapshots the previous position, refreshes the facing angle from the node,
 * then takes either the local player's path -- input, state machine, recoil,
 * ground clamp, position write-back -- or the remote replay path, steps the
 * cue queue, drives the sub-object and finally re-enables rendering.
 *
 * The object carries TWO 64-bit flag words, at 0x00 and 0x464, and every test
 * and clear touches both halves; the low mask of a clear is derived from the
 * high one with a single add.
 */

/* The game copies vectors through a pointer round-trip rather than by plain
 * struct assignment. Where the two objects are distinct this compiles to the
 * same ldm/stm pair a plain assignment would, but it also survives the two
 * cases the compiler would otherwise fold away: copying the position onto
 * itself, and staging a value through a local before storing it.
 */

#include "nitro/types.h"
#include "nitro/fx_types.h"

#define VEC_COPY(pDst, pSrc) (*(pDst) = *(VecFx32 *)(void *)(pSrc))

struct NodeAnim {
    u32 nOpaque;
};

struct Node {
    u32 nFlags;                  /* 0x000 */
    struct NodeAnim anim;        /* 0x004 */
    u8 pad008[0x1c];
    u32 nRenderFlags;            /* 0x024 */
    u8 pad028[0x58];
    u16 nAngle;                  /* 0x080 */
    u8 pad082[0x26];
    VecFx32 vecPos;          /* 0x0a8 */
    u8 pad0b4[0x94];
    u32 nField148;               /* 0x148 */
};

struct Sub {
    u8 pad000[0x60];
    u16 nAim : 8;                /* 0x060, extracted with a shift pair */
    u16 nRest60 : 8;
    u8 pad062[0x12e];
    VecFx32 vecTarget;       /* 0x190 */
};

struct Actor;
typedef void *(*PfnState)(struct Actor *pActor);

struct Actor {
    unsigned long long nFlags;   /* 0x000 */
    u8 nOwner;                   /* 0x008 */
    u8 nId;                      /* 0x009 */
    u8 pad00a[8];
    u16 nHp;                     /* 0x012 */
    u8 pad014[0xc];
    struct Node *pNode;          /* 0x020 */
    u8 pad024[4];
    VecFx32 vecVel;          /* 0x028 */
    u8 pad034[0x24];
    int nRecoil;                 /* 0x058 */
    u8 pad05c[0xa];
    short nSlotIndex;            /* 0x066 */
    u8 pad068[0x9c];
    int nFloorY;                 /* 0x104 */
    u8 pad108[4];
    int nHasFloor;               /* 0x10c */
    u8 pad110[0x350];
    PfnState pfnState;           /* 0x460 */
    unsigned long long nFlags2;  /* 0x464 */
    u8 pad46c[0xe];
    char nField47a;              /* 0x47a */
    char nField47b;              /* 0x47b */
    u8 pad47c[0xc];
    u32 nFacingAngle;            /* 0x488 */
    VecFx32 vecPos;          /* 0x48c */
    VecFx32 vecStep;         /* 0x498 */
    u8 pad4a4[0x28];
    int nStateTimer;             /* 0x4cc */
    u8 pad4d0[0x1c];
    struct Sub *pSub;            /* 0x4ec */
    u8 pad4f0[0x1a4];
    u8 bSuppressDraw : 1;        /* 0x694 */
    u8 nRest694 : 7;
    u8 pad695[0x11b];
    int nAnimHandle;             /* 0x7b0 */
    u8 pad7b4[0x144];
    VecFx32 vecFacing;       /* 0x8f8 */
    VecFx32 vecPrevPos;      /* 0x904 */
    u8 pad910[0x480];
    u8 subA[0x10];               /* 0xd90 */
    u8 subB[0x1558];             /* 0xda0 */
    u8 subC[0x370];              /* 0x22f8 */
    int nField2668;              /* 0x2668 */
};

extern u8 data_0204be04;

extern void func_ov022_020ad44c(VecFx32 *pOut, struct Actor *pActor);
extern void Ov022_StepScaledAnimTracks(struct Actor *pActor);
extern int Session_GetLocalPlayerIndex(void);
extern int Ov022_IsInputAllowedForActiveSlot(void);
extern void Ov022_UpdateCommandInput(struct Actor *pActor);
extern int Anim_GetFrame(struct NodeAnim *pAnim, int nFlags);
extern void *Ov022_SelectForcedState(struct Actor *pActor);
extern void Ov022_TranslateCommandToAction(struct Actor *pActor);
extern void Ov022_ApplySurfaceReactions(struct Actor *pActor);
extern void Ov022_TrackWallPress(struct Actor *pActor);
extern int Ov022_GetGlobal34(void);
extern void *Ov022_SelectStunState(struct Actor *pActor);
extern void Ov022_IntegrateRecoilVec(struct Actor *pActor);
extern void func_ov022_0209a1ac(struct Actor *pActor);
extern void Ov022_ApplyExternalPush(struct Actor *pActor);
extern int Ov002_GetSlotTableByte(int nSlot);
extern int Ov002_GetSlotGround(int nArea);
extern int VEC_Mag(const VecFx32 *pVec);
extern void Mover_StepActor(struct Node **ppNode, int nOn);
extern void Actor_SetVecAndSyncChild(struct Node *pNode, const VecFx32 *pPos);
extern int VEC_Distance(const VecFx32 *pA, const VecFx32 *pB);
extern int func_ov022_02088338(void);
extern void Ov022_RunReplayFrame(struct Actor *pActor);
extern void func_ov022_020965b8(struct Actor *pActor);
extern void Ov022_StepAnimRequest(void *pObj);
extern void Ov022_StepCueQueue(void *pObj);
extern void Ov022_UpdateRumble(struct Actor *pActor);
extern void Ov022_UpdateSubsystems(struct Actor *pActor);
extern int func_ov022_020ad7b0(struct Actor *pActor);
extern int Ov022_IsState9Or6WithFlag200(void *pObj);
extern void Ov002_ShowSeatHpGauge(int nSeat, int bOn);
extern void Ov022_SpendDecodeBudget(struct Actor *pActor);
extern void Ov022_ComputeAimPoint(VecFx32 *pOut, struct Actor *pActor);
extern void Ov107_MoveNodeAndRelayout(struct Sub *pSub, const VecFx32 *pPos);
extern void Ov002_CollectNearbySpots(int nArea, struct Sub *pSub, u32 nId);
extern void func_ov022_0209a68c(struct Actor *pActor, int nOn);
extern void Scene_DrawNode(struct NodeAnim *pAnim);

void Ov022_ActorUpdate(struct Actor *pActor)
{
    VecFx32 vecClamp;
    VecFx32 vecReplay;
    VecFx32 vecSubCopy;
    VecFx32 vecFacing;
    VecFx32 vecSubPos;
    int nGround;
    int nEnable;
    void *pNext;

    VEC_COPY(&pActor->vecPrevPos, &pActor->vecPos);
    VEC_COPY(&pActor->vecPos, &pActor->vecPos);

    pActor->nFacingAngle = (u16)(pActor->pNode->nAngle - 0x8000);
    pActor->nField47a = -1;
    pActor->nField47b = 0;
    func_ov022_020ad44c(&vecFacing, pActor);
    VEC_COPY(&pActor->vecFacing, &vecFacing);
    Ov022_StepScaledAnimTracks(pActor);

    if (((pActor->nFlags & (1ULL << 33)) != 0 || (pActor->nFlags & (1ULL << 28)) != 0)
        && Session_GetLocalPlayerIndex() == 0) {
        pActor->nFlags2 |= (1ULL << 24);
    }
    pActor->pNode->nRenderFlags &= ~1;
    if (data_0204be04 == 0
        && pActor->nOwner == Session_GetLocalPlayerIndex()
        && Ov022_IsInputAllowedForActiveSlot() == 0
        && (pActor->nFlags & (1ULL << 16)) == 0) {
        Ov022_UpdateCommandInput(pActor);
    }

    if (Session_GetLocalPlayerIndex() == 0) {
        pActor->nAnimHandle = Anim_GetFrame(&pActor->pNode->anim, 0);
        pNext = Ov022_SelectForcedState(pActor);
        if (pNext != 0) {
            pActor->pfnState = (PfnState)pNext;
        }
        Ov022_TranslateCommandToAction(pActor);
        Ov022_ApplySurfaceReactions(pActor);
        Ov022_TrackWallPress(pActor);
        if (pActor->pfnState != 0) {
            pNext = pActor->pfnState(pActor);
            if (pNext != 0) {
                pActor->pfnState = (PfnState)pNext;
            } else {
                pActor->nStateTimer += Ov022_GetGlobal34();
            }
        }
        pNext = Ov022_SelectStunState(pActor);
        if (pNext != 0) {
            pActor->pfnState = (PfnState)pNext;
        }
        Ov022_IntegrateRecoilVec(pActor);
        func_ov022_0209a1ac(pActor);
        Ov022_ApplyExternalPush(pActor);
        nGround = Ov002_GetSlotGround(Ov002_GetSlotTableByte(pActor->nSlotIndex)) - 0x2000;
        if (pActor->nRecoil > 0) {
            if (nGround <= pActor->vecPos.y) {
                pActor->nRecoil = 0;
            }
        }
        pActor->vecVel.x = pActor->vecStep.x;
        pActor->vecVel.y = 0;
        pActor->vecVel.z = pActor->vecStep.z;
        if ((pActor->nFlags & (1ULL << 36)) != 0
            && (pActor->nFlags2 & (1ULL << 7)) != 0
            && VEC_Mag(&pActor->vecVel) < 0x200) {
            pActor->vecVel.z = 0;
            pActor->vecVel.y = 0;
            pActor->vecVel.x = 0;
        }
        if ((pActor->nFlags2 & (1ULL << 23)) == 0) {
            Mover_StepActor(&pActor->pNode, 1);
        }
        if (nGround <= pActor->pNode->vecPos.y) {
            VEC_COPY(&vecClamp, &pActor->pNode->vecPos);
            vecClamp.y = nGround;
            Actor_SetVecAndSyncChild(pActor->pNode, &vecClamp);
        }
        pActor->pNode->nField148 = 0x900;
        pActor->vecStep.x = pActor->vecStep.y = pActor->vecStep.z = 0;
        if ((pActor->nFlags & (1ULL << 43)) != 0
            && VEC_Distance(&pActor->pNode->vecPos, &pActor->vecPos) < 4) {
            pActor->nFlags &= ~(1ULL << 43);
        }
        if ((pActor->nFlags & (1ULL << 46)) != 0) {
            VEC_COPY(&vecReplay, &pActor->pNode->vecPos);
            if (pActor->nHasFloor != 0
                && vecReplay.y - pActor->nFloorY < 0x400) {
                vecReplay.y = pActor->nFloorY + 0x400;
                Actor_SetVecAndSyncChild(pActor->pNode, &vecReplay);
                VEC_COPY(&pActor->vecPos, &vecReplay);
            }
            pActor->nFlags &= ~(1ULL << 46);
        }
        VEC_COPY(&pActor->vecPos, &pActor->pNode->vecPos);
    } else if (func_ov022_02088338() != 0) {
        Ov022_ApplySurfaceReactions(pActor);
        Ov022_TrackWallPress(pActor);
        Ov022_RunReplayFrame(pActor);
        pActor->nAnimHandle = Anim_GetFrame(&pActor->pNode->anim, 0);
    }

    if (pActor->nOwner == Session_GetLocalPlayerIndex() && pActor->nHp == 0) {
        pActor->nField2668 = 0;
    }
    func_ov022_020965b8(pActor);
    Ov022_StepAnimRequest(pActor->subA);
    Ov022_StepCueQueue(pActor->subB);
    Ov022_UpdateRumble(pActor);
    Ov022_UpdateSubsystems(pActor);
    if (data_0204be04 == 0 && (pActor->nFlags & (1ULL << 8)) == 0) {
        if (func_ov022_020ad7b0(pActor) != 0
            && Ov022_IsState9Or6WithFlag200(pActor->subC) == 0) {
            if (pActor->nHp != 0) {
                Ov002_ShowSeatHpGauge(pActor->nId, 1);
            }
        } else {
            Ov002_ShowSeatHpGauge(pActor->nId, 0);
        }
    }
    Ov022_SpendDecodeBudget(pActor);
    nEnable = 0;
    if (pActor->pSub != 0) {
        struct Sub *pSub;

        Ov022_ComputeAimPoint(&vecSubPos, pActor);
        VEC_COPY(&vecSubCopy, &vecSubPos);
        pSub = pActor->pSub;
        VEC_COPY(&pSub->vecTarget, &vecSubCopy);
        Ov107_MoveNodeAndRelayout(pSub, &pSub->vecTarget);
        if ((pActor->nFlags & (1ULL << 34)) == 0
            && (pActor->pSub->nAim & 0x80) > 0
            && Session_GetLocalPlayerIndex() == 0) {
            pActor->nFlags2 |= (1ULL << 33);
        }
        if (pActor->nSlotIndex >= 0 && pActor->nHp != 0) {
            Ov002_CollectNearbySpots(Ov002_GetSlotTableByte(pActor->nSlotIndex), pActor->pSub,
                                     pActor->nId);
        }
    }
    if ((pActor->nFlags & (1ULL << 42)) != 0) {
        nEnable = 1;
    }
    if ((pActor->nFlags2 & (1ULL << 33)) != 0) {
        nEnable = 1;
    }
    func_ov022_0209a68c(pActor, nEnable);
    pActor->pNode->nRenderFlags |= 1;
    if (pActor->bSuppressDraw != 0) {
        return;
    }
    pActor->pNode->nRenderFlags |= 3;
    if ((pActor->pNode->nFlags & 0x20) == 0) {
        Scene_DrawNode(&pActor->pNode->anim);
    }
    pActor->pNode->nRenderFlags &= ~3;
}

