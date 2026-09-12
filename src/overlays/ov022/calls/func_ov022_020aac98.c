/* Ov022_StepHeldState -- run one frame of a held state and decide whether it
 * is over.
 *
 * The local player raises flag-2 bit 13, and flag-3 bit 7 too when flag bit
 * 36 and flag-2 bit 7 are both up. Without input bit 2 the recoil is cleared.
 * The state's own step then answers whether it is done: that raises flag bit
 * 49, pokes the animation unless the node is already skipping it and raises
 * the end request (flag-2 bit 1) for the local player. Once the request is up
 * the state ends: with flag bit 36 and flag-2 bit 7 it drops flag bit 2, runs
 * the pre-draw hook with 14 and ends into state 6; otherwise into state 0. A
 * state that did not end raises flag-3 bit 13 for the local player.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

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
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[0x1f0];
    PreDrawFn pfnPreDraw;        /* 0x0664 */
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nFlags694Rest : 6;
};

#define FLAG_BIT2 (1ULL << 2)
#define FLAG_BIT36 (1ULL << 36)
#define FLAG_BIT49 (1ULL << 49)
#define FLAG2_BIT1 (1ULL << 1)
#define FLAG2_BIT7 (1ULL << 7)
#define FLAG2_BIT13 (1ULL << 13)
#define FLAG3_BIT7 (1ULL << 7)
#define FLAG3_BIT13 (1ULL << 13)
#define INPUT_BIT2 0x4
#define NODE_NO_ANIM 0x20
#define PREDRAW_HELD 0xe
#define STATE_IDLE 0
#define STATE_HELD_END 6

extern int func_02030788(void);
extern void func_0202af1c(u16 *pAnimFlags);                                    /* SceneNode_Enable */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);             /* Ov022_ActorSetState */

int func_ov022_020aac98(struct Actor *pActor)
{
    int nRet;

    nRet = 0;
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT13;
    }
    if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0
        && func_02030788() == 0) {
        pActor->nFlags3 |= FLAG3_BIT7;
    }
    if ((pActor->nInputMask & INPUT_BIT2) == 0) {
        pActor->nRecoil = 0;
    }
    pActor->bStateOver = pActor->pfnPostDraw(pActor);
    if (pActor->bStateOver != 0) {
        pActor->nFlags |= FLAG_BIT49;
        if ((pActor->pNode->nFlags & NODE_NO_ANIM) == 0) {
            func_0202af1c(&pActor->pNode->nAnimFlags);
        }
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT1;
        }
    }
    if ((pActor->nFlags2 & FLAG2_BIT1) != 0) {
        if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
            pActor->nFlags &= ~FLAG_BIT2;
            pActor->pfnPreDraw(pActor, PREDRAW_HELD);
            nRet = func_ov022_020a35f4(pActor, STATE_HELD_END);
        } else {
            nRet = func_ov022_020a35f4(pActor, STATE_IDLE);
        }
    }
    if (nRet == 0 && func_02030788() == 0) {
        pActor->nFlags3 |= FLAG3_BIT13;
    }
    return nRet;
}
