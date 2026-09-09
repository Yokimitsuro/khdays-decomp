/* NOT MATCHING -- 665 of 704 bytes, 172 of 176 instructions aligned.
 *
 * Exact size, exact instruction count and exact relocations. Four instructions
 * differ, and only in which of two registers holds which value: the ROM makes
 * the hit-list address in r1 and the cone constant in r2 and stores them in
 * that order, this source has them the other way round, and the two
 * instructions after them inherit the swap.
 *
 * The cause is measured from several directions.
 *
 * Of two independent short-lived values filling a stack structure, the one
 * written later in the source takes the lower register; that never broke in any
 * measurement. Their emission and store order follow the source when anything
 * precedes the pair in its basic block, and reverse when the pair leads it.
 * Position beats kind: leading the block gives the forward direction whatever
 * the values are, while mid-block the forward direction needs the higher-offset
 * value to be a load from memory -- an address or a constant there always comes
 * out backward. This window is mid-block, six instructions in, with nothing
 * branching into it, and its higher-offset value is an address computed from
 * the context, which the layout forces: the context holds no pointer to its own
 * hit array, only the array itself at 0x5c.
 *
 * The two halves are also mutually exclusive by position. Writing the pair
 * early gives the ROM's order and the low register, but the stores then follow
 * at once and the second value reuses the first's register. Writing it late
 * defers the stores and forces two live registers, which is exactly where the
 * direction runs backward.
 *
 * Enumerated, not argued: all 408 arrangements of the five fills crossed with
 * every position of the fifth, inside the block or anywhere in the parameter
 * block. Exactly one reproduces the ROM's pair, and it scores 625 because it
 * moves the group's load behind the pair. Filtering on the whole register
 * triple the ROM uses gives zero arrangements. Hill climbs, free and
 * constrained, with and without the block copies in the pool, all terminate
 * here.
 *
 * Also closed: pointer and union views, nested sub-structs, splitting the
 * structure into two locals, aggregate initialisers, compound literals, the
 * comma operator, duplicate and dead stores, every type and signedness and
 * const combination, fourteen compiler pragmas including register_coloring,
 * volatile on either field, the C++ lane, inline helpers, hoisting either value
 * into a local, a second use of the value, and nested scopes.
 *
 * Across the whole ROM the shape appears in nine ARM functions, none matched;
 * the cheapest place to learn the spelling is the 65-instruction routine
 * duplicated across ov046, ov065, ov084 and ov101.
 */

/* Ov022_MovePartTo -- move a slot part to a point along a direction.
 *
 * When the owner wants it, the part first casts the move: the probe carries
 * where the part is going, which way, the owner's spawn radius and drop, and
 * the group the part may hit. A cast that reports a hit ends the run there.
 *
 * The part then asks whether its action lands at that point, with the same
 * query the other parts use: the point, the direction, the owner's spawn
 * radius, a full-circle cone and the context's already-struck list, and the
 * owner's numbers as the parameters. Only answers one and two mean anything.
 *
 * What happens next is the owner's state's business. Most states simply end the
 * run. State one and state ten end it only on answer two, and only while the
 * owner's flag is set; state one also publishes the record with the direction
 * turned around when the run is not ending. States three and five end on answer
 * two, and state three notifies the point first when the answer is one.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022SlotTail */
struct SlotTail {
    u8 nState;                       /* 0x00 */
    u8 pad01;
    u16 nTag;                        /* 0x02 */
    int nSpawn;                      /* 0x04 */
    int nField08;                    /* 0x08 */
    u8 pad0c[0x20];
    int nField2c;                    /* 0x2c */
    int nField30;                    /* 0x30 */
    int nField34;                    /* 0x34 */
    struct VecFx32 vecField38;       /* 0x38 */
    u8 nLevel;                       /* 0x44 */
    u8 pad45[3];
    int nField48;                    /* 0x48 */
    int nField4c;                    /* 0x4c */
};

/* Ov022SlotPart */
struct SlotPart {
    u8 pad000[0xc0];
    struct VecFx32 vecAt;            /* 0x0c0 */
    u8 pad0cc[0x7c];
    struct SlotTail *pOwner;         /* 0x148 */
    u8 pad14c;
    u8 nGroup : 3;                   /* 0x14d */
    u8 nRest : 5;
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                       /* 0x0c */
    u8 pad10[0x48];
    void *pActor;                    /* 0x58 */
    short aHitIds[8];                /* 0x5c */
};

/* Ov022MoveProbe: what the cast is handed. */
struct MoveProbe {
    struct VecFx32 vecPos;           /* 0x00 */
    struct VecFx32 vecDir;           /* 0x0c */
    int nRadius;                     /* 0x18 */
    int nDrop;                       /* 0x1c */
    int nSlotIndex;                  /* 0x20 */
    struct VecFx32 vecHit;           /* 0x24 */
};

/* Ov022ActionQuery */
struct ActionQuery {
    struct VecFx32 vecPos;           /* 0x00 */
    int nRadius;                     /* 0x0c */
    unsigned int nGroup;             /* 0x10 */
    struct VecFx32 vecDir;           /* 0x14 */
    int nConeLimit;                  /* 0x20 */
    short *pHitIds;                  /* 0x24 */
    int nField28;                    /* 0x28 */
};

/* Ov022ActionParams */
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

#define CONE_FULL 0x1000
#define PHASE_COUNT 3
#define ANSWER_NEAR 1
#define ANSWER_FAR 2
#define RECORD_KIND 8

extern int func_ov022_0208aa28(struct ReactionCtx *pCtx,
                               struct MoveProbe *pProbe);
extern int func_ov022_0208acc4(int nState, int nKind);
extern void func_ov022_0208a50c(struct ReactionCtx *pCtx,
                                struct SlotPart *pPart, int nReaction);
extern int func_ov022_020a216c(void *pActor, int nField);
extern int func_ov022_0208ac10(struct ReactionCtx *pCtx,
                               struct ActionQuery *pQuery,
                               struct ActionParams *pParams);
extern s16 FX_Atan2(int x, int z);
extern void func_ov022_020ad208(void *pActor, int nKind,
                                struct VecFx32 *pAt, int nScale,
                                unsigned int nAngle, unsigned int bEnd);
extern void func_ov022_0208acdc(struct ReactionCtx *pCtx,
                                struct VecFx32 *pAt, int nKind);

void func_ov022_0208b400(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                         struct VecFx32 *pAt, struct VecFx32 *pDir)
{
    struct MoveProbe probe;
    struct ActionQuery query;
    struct ActionParams params;
    struct SlotTail *pOwner;
    void *pActor;
    int nReaction;
    int nAnswer;
    unsigned int bEnd;
    int nSlot;
    u16 nAngle;

    pOwner = pPart->pOwner;
    pActor = pCtx->pActor;
    if (pOwner->nField48 != 0) {
        probe.vecPos = *pAt;
        probe.vecDir = *pDir;
        probe.nRadius = pOwner->nSpawn;
        probe.nDrop = pOwner->nField08;
        probe.nSlotIndex = pPart->nGroup;
        if (func_ov022_0208aa28(pCtx, &probe) != 0) {
            func_ov022_0208a50c(pCtx, pPart,
                                func_ov022_0208acc4(pOwner->nState, ANSWER_FAR));
        }
    }
    query.vecPos = *pAt;
    query.vecDir = *pDir;
    query.nGroup = pPart->nGroup;
    query.nRadius = pOwner->nSpawn;
    query.pHitIds = pCtx->aHitIds;
    query.nConeLimit = CONE_FULL;
    query.nField28 = 0;
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
    nAnswer = func_ov022_0208ac10(pCtx, &query, &params);
    switch (nAnswer) {
    case ANSWER_NEAR:
        nReaction = func_ov022_0208acc4(pOwner->nState, ANSWER_NEAR);
        break;
    case ANSWER_FAR:
        nReaction = func_ov022_0208acc4(pOwner->nState, ANSWER_FAR);
        break;
    }
    if (nAnswer != ANSWER_NEAR && nAnswer != ANSWER_FAR) {
        return;
    }
    bEnd = 0;
    switch (pOwner->nState) {
    case 1:
        if ((pOwner->nField4c & 1) != 0) {
            if (nAnswer == ANSWER_FAR) {
                bEnd = 1;
            } else {
                nAngle = FX_Atan2(-pDir->x, -pDir->z);
                func_ov022_020ad208(pActor, RECORD_KIND, pAt, CONE_FULL,
                                    nAngle, bEnd);
            }
        } else {
            bEnd = 1;
        }
        break;
    case 10:
        if ((pOwner->nField4c & 1) != 0) {
            if (nAnswer == ANSWER_FAR) {
                bEnd = 1;
            }
        } else {
            bEnd = 1;
        }
        break;
    case 3:
        if (nAnswer == ANSWER_NEAR) {
            func_ov022_0208acdc(pCtx, &pPart->vecAt, ANSWER_NEAR);
        }
        /* fall through */
    case 5:
        if (nAnswer == ANSWER_FAR) {
            bEnd = 1;
        }
        break;
    default:
        bEnd = 1;
        break;
    }
    if (bEnd != 0) {
        func_ov022_0208a50c(pCtx, pPart, nReaction);
    }
}
