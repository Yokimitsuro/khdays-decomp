/* ov022: run one frame of the actor and decide whether its state is over.
 *
 * The drift's horizontal part is added to the actor's carried push -- only the
 * horizontal, so a fall is not folded into it -- and then the state's own step
 * runs. Its answer is kept as a single bit.
 *
 * One hit kind gets special handling either way: with the action bit held it
 * starts a reaction and marks it, and without it a sentinel left in one word is
 * cleared instead.
 *
 * A step that reported done raises a flag, pokes the animation unless the node
 * is already skipping it, and on the first player's machine raises the request
 * that ends the state.
 *
 * Once that request is up the state does end, one of two ways. Holding the
 * action bit ends it early and clears nothing, unless a skill is both owned and
 * enabled; otherwise the state ends properly, its own flag goes up and three
 * counters are reset.
 */

#include "nitro/types.h"
#include "nitro/fx_types.h"

#define HIT_KIND_REACT 0xd
#define ACTION_BIT 4
#define NODE_NO_ANIM 0x20
#define SENTINEL 0x80000000
#define FLAGS_DONE 0x2000000000000ULL
#define FLAGS_SKILL 0x1000000000ULL
#define FLAGS_END 0x4ULL
#define FLAGS2_REQUEST 0x2ULL
#define FLAGS2_SKILL 0x80ULL

/* Ov022ActorNode */
struct ActorNode {
    u32 nFlags;                  /* 0x00 */
    u16 nAnimFlags;              /* 0x04 */
    u8 pad06[2];
};

struct Actor;

typedef void (*PreDrawFn)(struct Actor *pActor, int nReplay);
typedef int (*PostDrawFn)(struct Actor *pActor);

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[0x18];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x30];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x408];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x2c];
    VecFx32 vecStep;      /* 0x0498 */
    u8 pad04a4[0x1c0];
    PreDrawFn pfnPreDraw;        /* 0x0664 */
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nSpare694 : 1;
    u8 bActionLocked : 1;        /* bit 3 */
    u8 nFlags694High : 4;
    u8 pad0695[3];
    int nStateWordA;             /* 0x0698 */
    int nStateWordB;             /* 0x069c */
    int nStateWordC;             /* 0x06a0 */
    u8 pad06a4[0x18];
    int nHit;                    /* 0x06bc */
};

extern void Ov022_TakeDriftStep(struct Actor *pActor, VecFx32 *pOutStep);
/* Ov022_PlayEntityVoice */
extern u32 Ov022_PlayEntityVoice(struct Actor *pActor, u32 nSeqArc, u32 nSeq);
/* Ov022_ActorSetState */
extern int Ov022_ActorSetState(struct Actor *pActor, int nState);
/* SceneNode_Enable */
extern void SceneNode_Enable(u16 *pAnimFlags);
extern int Session_GetLocalPlayerIndex(void);
extern void VEC_Add(const VecFx32 *pA, const VecFx32 *pB,
                    VecFx32 *pOut);

int Ov022_StepActorState(struct Actor *pActor)
{
    VecFx32 vecDrift;
    VecFx32 vecMove;
    int nRet;

    nRet = 0;
    Ov022_TakeDriftStep(pActor, &vecDrift);
    vecMove = vecDrift;
    vecMove.y = 0;
    VEC_Add(&pActor->vecStep, &vecMove, &pActor->vecStep);
    pActor->bStateOver = pActor->pfnPostDraw(pActor);
    if (pActor->nHit == HIT_KIND_REACT) {
        if ((pActor->nInputMask & ACTION_BIT) != 0) {
            Ov022_PlayEntityVoice(pActor, 2, 3);
            pActor->bStateOver = 1;
        }
    } else {
        if ((pActor->nInputMask & ACTION_BIT) == 0
            && pActor->nRecoil == SENTINEL) {
            pActor->nRecoil = 0;
        }
    }
    if (pActor->bStateOver != 0) {
        pActor->nFlags = pActor->nFlags | FLAGS_DONE;
        if ((pActor->pNode->nFlags & NODE_NO_ANIM) == 0) {
            SceneNode_Enable(&pActor->pNode->nAnimFlags);
        }
        if (Session_GetLocalPlayerIndex() == 0) {
            pActor->nFlags2 = pActor->nFlags2 | FLAGS2_REQUEST;
        }
    }
    if ((pActor->nFlags2 & FLAGS2_REQUEST) != 0) {
        if ((pActor->nInputMask & ACTION_BIT) != 0
            && ((pActor->nFlags & FLAGS_SKILL) == 0
                || (pActor->nFlags2 & FLAGS2_SKILL) == 0)) {
            pActor->pfnPreDraw(pActor, 0);
            nRet = Ov022_ActorSetState(pActor, 0);
        } else {
            pActor->nFlags = pActor->nFlags | FLAGS_END;
            nRet = Ov022_ActorSetState(pActor, 2);
            pActor->nStateWordC = 0;
            pActor->nStateWordB = 0;
            pActor->nStateWordA = 0;
        }
    }
    return nRet;
}
