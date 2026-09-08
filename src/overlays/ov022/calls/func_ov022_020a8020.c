/* ov022: run one frame of a state that can be interrupted into another.
 *
 * The third of the state steps. Before anything it marks the step on the first
 * player's machine, and afterwards it takes that mark back down.
 *
 * The interruption comes first and skips the step entirely: it needs the mode
 * not to be the second one, a reach test to pass, the action bit released, one
 * button pair to read exactly two, and then a second test on the same block. That
 * last one, when it passes, pushes a large amount into one counter and runs an
 * extra routine before the state changes either way.
 *
 * The step itself takes the drift's vertical as the new recoil when there is
 * one, and otherwise decays a positive recoil by the same amount the drift is
 * decayed by. The floor is then applied, and it is written out once per mode
 * rather than once with a chosen bound: the two clamps are identical apart from
 * the constant, so the compiler shares their tail and the only thing that
 * differs between the two paths is how the bound is built.
 *
 * The animation is asked how far along it is and pushed forward if it has gone
 * past the mark. After the state's own hook the ending is the usual two ways,
 * except the early one lands in a different state, and the ending is reached on
 * three separate grounds rather than one.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define ACTION_BIT 4
#define NODE_NO_ANIM 0x20
#define MODE_SECOND 2
#define BUTTON_GATE 2
#define COUNTER_PUSH 0x2d000
#define RECOIL_DECAY 0xc80
#define RECOIL_FLOOR (-0x420)
#define RECOIL_FLOOR_SECOND (-0x34d)
#define ANIM_PUSH 0x9000
#define ANIM_EARLY 0x3000
#define ANIM_LATE 0x20000
#define STATE_INTERRUPT 0x1b
#define STATE_EARLY 0x16

#define FLAGS_DONE 0x2000000000000ULL
#define FLAGS_SKILL 0x1000000000ULL
#define FLAGS2_IN_STEP 0x100ULL
#define FLAGS2_REQUEST 0x2ULL
#define FLAGS2_SKILL 0x80ULL

struct VecFx32 {
    int x;
    int y;
    int z;
};

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
    u8 pad0008[0x10];
    u16 nButtons;                /* 0x0018 */
    u16 nButtons2;               /* 0x001a */
    u8 pad001c[4];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x30];
    /* volatile: the sibling steps read it twice in a row with nothing between */
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x408];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x10];
    struct VecFx32 vecDrift;     /* 0x047c */
    u8 pad0488[0x10];
    struct VecFx32 vecStep;      /* 0x0498 */
    u8 pad04a4[0x10];
    int nInterruptCharge;        /* 0x04b4 */
    u8 pad04b8[0x14];
    int nAnimPos;                /* 0x04cc */
    u8 pad04d0[0x18c];
    int nStepScratch;            /* 0x065c */
    u8 pad0660[4];
    PreDrawFn pfnPreDraw;        /* 0x0664 */
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nSpare694 : 1;
    u8 bActionLocked : 1;        /* bit 3 */
    u8 nFlags694High : 4;
    u8 pad0695[0x15f7];
    u8 blkReach;                 /* 0x1c8c */
};

extern int func_02030788(void);
extern int func_ov022_0209bd04(struct Actor *pActor);
extern int func_ov022_020940a0(u8 *pBlk, int nAnimPos);
extern int func_ov022_02094120(u8 *pBlk, int nAnimPos);
extern void func_ov022_0209ccf4(struct Actor *pActor);
extern void func_ov022_02097e14(struct Actor *pActor, struct VecFx32 *pOutStep);
extern void func_ov022_02097038(struct Actor *pActor, int nPos);
/* Ov022_ActorSetState */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);
extern void func_ov022_0209c700(struct Actor *pActor);
extern int func_0202aee0(u16 *pAnimFlags, int nArg);
/* SceneNode_Enable */
extern void func_0202af1c(u16 *pAnimFlags);
extern void VEC_Add(const struct VecFx32 *pA, const struct VecFx32 *pB,
                    struct VecFx32 *pOut);

int func_ov022_020a8020(struct Actor *pActor)
{
    struct VecFx32 vecDrift;
    struct VecFx32 vecMove;
    int nRet;
    int bEnd;

    nRet = 0;
    bEnd = 0;
    if (func_02030788() == 0) {
        pActor->nFlags2 = pActor->nFlags2 | FLAGS2_IN_STEP;
    }
    if (func_ov022_0209bd04(pActor) != MODE_SECOND
        && func_ov022_020940a0(&pActor->blkReach, pActor->nAnimPos) != 0
        && (pActor->nInputMask & ACTION_BIT) == 0
        && (pActor->nButtons & BUTTON_GATE) == BUTTON_GATE) {
        if (func_ov022_02094120(&pActor->blkReach, pActor->nAnimPos) != 0) {
            pActor->nInterruptCharge = pActor->nInterruptCharge + COUNTER_PUSH;
            func_ov022_0209ccf4(pActor);
        }
        nRet = func_ov022_020a35f4(pActor, STATE_INTERRUPT);
    } else {
        func_ov022_02097e14(pActor, &vecDrift);
        if (vecDrift.y != 0) {
            pActor->nRecoil = vecDrift.y;
        } else if (pActor->nRecoil > 0) {
            pActor->nRecoil = (int)(((long long)pActor->nRecoil * RECOIL_DECAY
                                     + 0x800) >> 12);
        }
        vecMove = vecDrift;
        vecMove.y = 0;
        VEC_Add(&pActor->vecStep, &vecMove, &pActor->vecStep);
        if (func_ov022_0209bd04(pActor) != MODE_SECOND) {
            if (pActor->nRecoil < RECOIL_FLOOR) {
                pActor->nRecoil = RECOIL_FLOOR;
            }
        } else {
            if (pActor->nRecoil < RECOIL_FLOOR_SECOND) {
                pActor->nRecoil = RECOIL_FLOOR_SECOND;
            }
        }
        if (func_0202aee0(&pActor->pNode->nAnimFlags, 0) >= ANIM_PUSH) {
            func_ov022_02097038(pActor, ANIM_PUSH);
        }
        pActor->bStateOver = pActor->pfnPostDraw(pActor);
        if (pActor->bStateOver != 0) {
            pActor->nFlags = pActor->nFlags | FLAGS_DONE;
            if ((pActor->pNode->nFlags & NODE_NO_ANIM) == 0) {
                func_0202af1c(&pActor->pNode->nAnimFlags);
            }
            if (func_02030788() == 0) {
                pActor->nFlags2 = pActor->nFlags2 | FLAGS2_REQUEST;
            }
        }
        if (pActor->nAnimPos >= ANIM_EARLY
            && (pActor->nInputMask & ACTION_BIT) != 0) {
            bEnd = 1;
        } else if (func_ov022_0209bd04(pActor) != MODE_SECOND) {
            if ((pActor->nFlags2 & FLAGS2_REQUEST) != 0
                || pActor->nAnimPos >= ANIM_LATE) {
                bEnd = 1;
            }
        }
        if (bEnd != 0) {
            pActor->vecDrift.z = 0;
            pActor->vecDrift.y = 0;
            pActor->vecDrift.x = 0;
            if ((pActor->nInputMask & ACTION_BIT) != 0
                && ((pActor->nFlags & FLAGS_SKILL) == 0
                    || (pActor->nFlags2 & FLAGS2_SKILL) == 0)) {
                nRet = func_ov022_020a35f4(pActor, STATE_EARLY);
            } else {
                nRet = func_ov022_020a35f4(pActor, 2);
            }
            pActor->nFlags2 = pActor->nFlags2 & ~FLAGS2_IN_STEP;
        }
    }
    if (nRet != 0) {
        func_ov022_0209c700(pActor);
    }
    pActor->nStepScratch = 0;
    return nRet;
}
