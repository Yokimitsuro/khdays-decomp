/* func_ov015_02081ca8 -- Ov015_ChestUpdate: per-frame state function of a treasure chest
 * (frame delta from ov002 0207687c).  A refresh request (bit 0 of +0x724) clears the state
 * bits and, unless the render node is already bound (bit 1 of +0x4a0), binds it to the
 * kind's model (ov002 0207285c, 0202ba9c), marks it bound and, when visible, drops its bit 3.
 * Then by state: opened (bit 4) -- the closed-lid sequence is held at frame 0 (020817f0)
 * and the open sequence (+0x61c) driven to 0x98000 (ov002 0207c700, timer +0x728); past
 * 0x97000 the local player (02030788 == 0) queues a type-5 message (kind 6) with the opener
 * (+0x726); the open node follows the lid position (+0x54c -> +0x6c0) and is drawn when
 * visible.  Open request (bit 5) -- the timer is set to 0x2000, the lid sequence started at
 * 0x2000, bit 5 swaps for the rising bit 6, the collidable flag (bit 3 of +0x12) drops, the
 * render node's resources are released (0202bc30), the rise (+0x73c) reset and the rise
 * speed (+0x740) set to 1 / 30 (FX_Inv), and slot 0x2e (def class 0x1b) or 0x2f spawns at the
 * lid position.  Rising (bit 6) -- the lid sequence is driven to 0x34000; past 0x33000 bit 6
 * swaps for the done bit 7, the node is released and the terminal state function (ov002
 * 0207cea4) returned; otherwise, for the local player while the timer is in 0x5000..0x23000,
 * the rise grows by speed * delta and its 5-unit extent notifies the neighbours (020813c4),
 * pushes nearby players (02081554) and starts the actor routine (020817bc).  Otherwise an
 * opening chest (bit 2 of +0x464) takes bit 4, resets the timer and holds the open sequence
 * at 0; the lid sequence is held at 0.  A visible chest draws the lid node; unless rising,
 * the knockback step (ov002 0207caa4 on +0x1c) is polled: 1 (moved) copies the lid
 * position into the position (+0x488) and clears the local player's ack bit (+0x725);
 * 2 (finished) acknowledges the local player (02081824) and, outside a session (02030670),
 * drops the opening flag -- a remote player instead queues a type-3 message (kind 6) with
 * its index and drops the flag once accepted.  Returns 0. */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef void *Ov015StateFn(void *pPiece);

typedef struct Ov015SeqNode {
    u16  nFlags;              /* 0x00 */
    u8   pad_02[0xa4 - 0x02];
    VecFx32 position;         /* 0xa4 */
    u8   pad_b0[0x104 - 0xb0];
} Ov015SeqNode;                /* 0x104 */

typedef struct Ov015RenderNode {
    u8   pad_00[8];
    u8   nBindBits;           /* 0x08: bit 1 bound */
    u8   pad_09[3];
    int  nBits;               /* 0x0c */
    Ov015SeqNode node;        /* 0x10 */
} Ov015RenderNode;             /* 0x114 */

typedef struct Ov015ChestDef {
    u8   pad_00[0x4c];
    u16  nClass;              /* 0x4c: 0x1b / 0x1c */
} Ov015ChestDef;

typedef struct Ov015Chest {
    u8   pad_000[8];
    Ov015ChestDef *pDef;      /* 0x008 */
    u8   pad_00c[4];
    u8   nKind;               /* 0x010 */
    u8   pad_011;
    u16  nFlags;              /* 0x012: bit 2 visible, bit 3 collidable */
    u8   pad_014[8];
    u8   knockback[0x464 - 0x1c]; /* 0x01c: knockback element view (ov002 0207caa4) */
    u16  nChestFlags;         /* 0x464: bit 2 opening */
    u8   pad_466[0x488 - 0x466];
    VecFx32 position;         /* 0x488 */
    u8   pad_494[4];
    Ov015RenderNode render;   /* 0x498: closed-lid node, sequence at +0x4a8, lid position +0x54c */
    u8   pad_5ac[0x61c - 0x5ac];
    Ov015SeqNode openNode;    /* 0x61c: open sequence, position +0x6c0 */
    u8   pad_720[4];
    u8   nStateBits;          /* 0x724: bit 0 refresh, 4 opened, 5 open request, 6 rising, 7 done */
    u8   nAckMask;            /* 0x725 */
    s8   nOpener;             /* 0x726 */
    u8   pad_727;
    int  nTimer;              /* 0x728 */
    u8   pad_72c[0x73c - 0x72c];
    int  nRise;               /* 0x73c */
    int  nRiseSpeed;          /* 0x740 */
} Ov015Chest;

typedef struct Ov015ChestNotify {
    u8   nType;               /* 0x00: 3 acknowledge / 5 open request */
    u8   pad_01[3];
    u8   nPlayer;             /* 0x04 */
    u8   pad_05;
} Ov015ChestNotify;

extern int   func_ov002_0207687c(void);                                    /* frame delta */
extern int   func_ov002_0207285c(int nKind);                               /* model id of a kind */
extern void  func_0202ba9c(void *pNode, u16 nId, int nArg, void *pParams);  /* bind a render node */
extern void  func_0202bedc(void *pNode, int nFlag);                        /* Obj_SetFlagBit3 */
extern void  func_ov015_020817f0(void *pChest, void *pNode, int nArg, int nFrame); /* Ov015_ChestSeekSequence */
extern int   func_ov002_0207c700(void *pPiece, void *pNode, int nDelta, int nFlag, int nLimit, int *pElapsed); /* drive a sequence */
extern int   func_02030788(void);                                          /* local player index */
extern int   func_ov002_020766e0(void *pPiece, void *pMessage, int nKind); /* queue a message on the piece */
extern void  func_0202aa9c(void *pNode);                                   /* Scene_DrawNode */
extern void  func_0202bc30(void *pNode);                                   /* ReleaseNodeResources */
extern int   FX_Inv(int nNumerator, int nDenominator);
extern void  func_02033d0c(int nSlot, int nArg, VecFx32 *pPos, int nD);    /* Slot_Spawn */
extern void  func_ov015_020813c4(Ov015Chest *pChest, int nExtent);         /* Ov015_ChestNotifyNeighbours */
extern void  func_ov015_02081554(Ov015Chest *pChest, int nRange);          /* Ov015_ChestPushNearbyPlayers */
extern void  func_ov015_020817bc(void *pChest, int nArg);                  /* Ov015_StartActorRoutine */
extern int   func_ov002_0207caa4(void *pPiece, void *pElement, VecFx32 *pOutDelta); /* knockback step */
extern int   func_ov015_02081824(void *pChest, int nPlayer);               /* Ov015_ChestAckPlayer */
extern int   func_02030670(void);                                          /* session active */
extern Ov015StateFn func_ov002_0207cea4;                                   /* terminal state */

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

Ov015StateFn *func_ov015_02081ca8(Ov015Chest *pChest)
{
    Ov015ChestNotify notify;
    Ov015ChestNotify ack;
    Ov015ChestDef *pDef;
    int nDelta;
    u8 nBits;
    int nRise;
    int nExtent;
    int nResult;

    pDef = pChest->pDef;
    nDelta = func_ov002_0207687c();
    if (pChest->nStateBits & 1) {
        pChest->nStateBits = 0;
        if ((pChest->render.nBindBits & 2) == 0) {
            func_0202ba9c(&pChest->render, func_ov002_0207285c(pChest->nKind), 0, 0);
            pChest->render.nBindBits |= 2;
            if (pChest->nFlags & 4) {
                func_0202bedc(&pChest->render, 0);
            }
        }
    }
    nBits = pChest->nStateBits;
    if (nBits & 0x10) {
        func_ov015_020817f0(pChest, &pChest->render.node, 0, 0);
        func_ov002_0207c700(pChest, &pChest->openNode, nDelta, 0, 0x98000, &pChest->nTimer);
        if (pChest->nTimer >= 0x97000 && func_02030788() == 0) {
            notify.nType = 5;
            notify.nPlayer = pChest->nOpener;
            func_ov002_020766e0(pChest, &notify, 6);
        }
        pChest->openNode.position = pChest->render.node.position;
        if (pChest->nFlags & 4) {
            func_0202aa9c(&pChest->openNode);
        }
    } else if (nBits & 0x20) {
        pChest->nTimer = 0x2000;
        func_ov015_020817f0(pChest, &pChest->render.node, 0, pChest->nTimer);
        pChest->nStateBits &= ~0x20;
        pChest->nStateBits |= 0x40;
        pChest->nFlags &= ~8;
        func_0202bc30(&pChest->render);
        pChest->nRise = 0;
        pChest->nRiseSpeed = FX_Inv(0x1000, 0x1e000);
        func_02033d0c(pDef->nClass == 0x1b ? 0x2e : 0x2f, 0, &pChest->render.node.position, 0);
    } else if (nBits & 0x40) {
        func_ov002_0207c700(pChest, &pChest->render.node, nDelta, 0, 0x34000, &pChest->nTimer);
        if (pChest->nTimer >= 0x33000) {
            pChest->nStateBits &= ~0x40;
            pChest->nStateBits |= 0x80;
            func_0202bc30(&pChest->render);
            return func_ov002_0207cea4;
        }
        if (func_02030788() == 0 && pChest->nTimer >= 0x5000 && pChest->nTimer < 0x23000) {
            nRise = pChest->nRise + FX_Mul(pChest->nRiseSpeed, nDelta);
            nExtent = FX_Mul(nRise, 0x5000);
            pChest->nRise = nRise;
            func_ov015_020813c4(pChest, nExtent);
            func_ov015_02081554(pChest, nExtent);
            func_ov015_020817bc(pChest, nExtent);
        }
    } else {
        if (pChest->nChestFlags & 4) {
            pChest->nStateBits = nBits | 0x10;
            pChest->nTimer = 0;
            func_ov015_020817f0(pChest, &pChest->openNode, 0, 0);
        }
        func_ov015_020817f0(pChest, &pChest->render.node, 0, 0);
    }
    if (pChest->nFlags & 4) {
        func_0202aa9c(&pChest->render.node);
    }
    if ((pChest->nStateBits & 0x40) == 0) {
        nResult = func_ov002_0207caa4(pChest, pChest->knockback, 0);
        if (nResult == 1) {
            pChest->position = pChest->render.node.position;
            if (func_02030788() == 0) {
                pChest->nAckMask &= ~(1 << func_02030788());
            }
        } else if (nResult == 2) {
            if (func_02030788() != 0) {
                ack.nType = 3;
                ack.nPlayer = func_02030788();
                if (func_ov002_020766e0(pChest, &ack, 6) != 0) {
                    pChest->nChestFlags &= ~4;
                }
            } else {
                func_ov015_02081824(pChest, func_02030788());
                if (func_02030670() == 0) {
                    pChest->nChestFlags &= ~4;
                }
            }
        }
    }
    return 0;
}
