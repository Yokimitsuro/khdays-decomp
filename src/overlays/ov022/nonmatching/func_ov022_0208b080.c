/* NOT MATCHING -- 313 of 328 bytes, 76 of 82 instructions aligned.
 *
 * Exact size, exact instruction count and exact relocations. The prologue is
 * byte identical and so is everything from 0x98 on, including the whole
 * parameter block and the modulo-three phase. Six instructions differ, and only
 * by one register: the ROM puts the context's hit-list address in r1 and the
 * cone limit in r2, this source the other way round, and the three later
 * instructions that go through them inherit the swap.
 *
 * The cause is measured. On a minimal probe -- a call whose first argument is a
 * hoisted field read, plus two stores into a stack struct, one an address and
 * one a constant -- the rule is that the LATER of the two stores takes the
 * LOWER register. The ROM needs the hit list stored first and in the lower
 * register, which is the one combination that rule forbids, and the register
 * and the emitted store order are locked together through the source order.
 *
 * Confirmed from four independent directions: all 120 orderings of the five
 * query fills, the interleaving used by the matched sibling that calls the same
 * routine, dead stores singly and in pairs, and declaring the fields as a
 * nested sub-struct. In every arrangement the hit list reaches r1 only when its
 * store is emitted last. A scan of every matched ARM source for a
 * counterexample -- an address stored before a constant with the address in the
 * lower register -- returns zero hits in 15861 functions, so this compiler does
 * not emit the shape anywhere in the game.
 *
 * Also closed: Ghidra's exact field types, the hit array's element type, the
 * phase spelled four ways, the guard spelled four ways, the six declaration
 * orders, declaration initialisers, all six prologue orderings, and the call's
 * arguments and result through locals. Dropping the hoisted actor read does
 * give both the register and the store order, but costs the hoisted load and
 * lands at 324 bytes and 81 instructions, and the ROM has that hoist.
 */

/* Ov022_StepPartStrike -- one frame of a slot part that is winding up a strike.
 *
 * The part's timer takes the frame. On the single frame the timer reads the
 * mark, and only while the owner has a radius at all, the part asks whether its
 * action lands: the query carries where the part is, the group it may hit, the
 * owner's radius, a full-circle cone and the context's already-struck list. The
 * parameters carry the owner's numbers, with the actor's scaled value first and
 * the context's slot index modulo three as the phase.
 *
 * The part ends its run when its own tracks report done.
 */

typedef unsigned char u8;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022SlotTail: the owner the part hangs off. */
struct SlotTail {
    u8 pad00[0x1c];
    int nRadius;                     /* 0x1c */
    u8 pad20[0xc];
    int nField2c;                    /* 0x2c */
    int nField30;                    /* 0x30 */
    int nField34;                    /* 0x34 */
    struct VecFx32 vecField38;       /* 0x38 */
    u8 nLevel;                       /* 0x44 */
};

/* Ov022SlotPart */
struct SlotPart {
    int nTimer;                      /* 0x000 */
    u8 pad004[0x18];
    int nSlotFlags;                  /* 0x01c */
    u8 pad020[0xa0];
    struct VecFx32 vecAt;            /* 0x0c0 */
    u8 pad0cc[0x7c];
    struct SlotTail *pOwner;         /* 0x148 */
    u8 nState;                       /* 0x14c */
    u8 nGroup : 3;                   /* 0x14d */
    u8 nRest : 5;
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                       /* 0x0c */
    u8 pad10[0x48];
    void *pActor;                    /* 0x58 */
    u8 aHitIds[0x20];                /* 0x5c */
};

/* Ov022ActionQuery: what the part asks about. */
struct ActionQuery {
    struct VecFx32 vecPos;           /* 0x00 */
    int nRadius;                     /* 0x0c */
    int nGroup;                      /* 0x10 */
    struct VecFx32 vecDir;           /* 0x14 */
    int nConeLimit;                  /* 0x20 */
    void *pHitIds;                   /* 0x24 */
    int nField28;                    /* 0x28 */
};

/* Ov022ActionParams: the numbers the action carries. */
struct ActionParams {
    int nValue;                      /* 0x00 */
    int nField04;                    /* 0x04 */
    int nField08;                    /* 0x08 */
    int nField0c;                    /* 0x0c */
    u8 nLevel;                       /* 0x10 */
    u8 pad11[3];
    struct VecFx32 vecField14;       /* 0x14 */
    int nField20;                    /* 0x20 */
    u8 nPhase;                       /* 0x24 */
    u8 bFlagA : 1;                   /* 0x25 */
    u8 bFlagB : 1;
    u8 nRest : 6;
    u8 pad26[2];
};

#define STRIKE_MARK 0x3000
#define CONE_FULL 0x1000
#define PART_STATE_DONE 4
#define PHASE_COUNT 3

extern int func_ov022_020a216c(void *pActor, int nField);
extern void func_ov022_0208ac10(struct ReactionCtx *pCtx,
                                struct ActionQuery *pQuery,
                                struct ActionParams *pParams);
extern int func_0202a818(int *pTracks, int nDelta);

int func_ov022_0208b080(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                        int nDelta)
{
    struct ActionQuery query;
    struct ActionParams params;
    struct SlotTail *pOwner;
    void *pActor;
    int nSlot;

    pActor = pCtx->pActor;
    pOwner = pPart->pOwner;
    pPart->nTimer = pPart->nTimer + nDelta;
    if (pOwner->nRadius > 0 && pPart->nTimer == STRIKE_MARK) {
        query.vecPos = pPart->vecAt;
        query.vecDir.z = 0;
        query.vecDir.y = 0;
        query.vecDir.x = 0;
        query.nGroup = pPart->nGroup;
        query.nRadius = pOwner->nRadius;
        query.pHitIds = pCtx->aHitIds;
        query.nField28 = 0;
        query.nConeLimit = CONE_FULL;
        params.nField0c = pOwner->nField34;
        params.nValue = func_ov022_020a216c(pActor, pOwner->nField2c);
        params.nField08 = pOwner->nField30;
        params.vecField14 = pOwner->vecField38;
        params.nField20 = 0;
        params.bFlagA = 0;
        params.bFlagB = 0;
        params.nLevel = pOwner->nLevel;
        params.nField04 = 0;
        nSlot = pCtx->nSlot;
        params.nPhase = (u8)(nSlot % PHASE_COUNT);
        func_ov022_0208ac10(pCtx, &query, &params);
    }
    if (func_0202a818(&pPart->nSlotFlags, nDelta) != 0) {
        pPart->nTimer = 0;
        pPart->nState = PART_STATE_DONE;
    }
    return 0;
}
