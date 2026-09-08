/* ov022: has this owner's run finished this frame?
 *
 * Answers 1 when the session is live and any of four things is true: the actor
 * is out of hit points, the run has outspent its budget, the actor carries both
 * cut-short flags, or -- for the local player's own actor only -- either the
 * abort query or the actor's own reach test answers.
 *
 * Anyone else's actor takes a shortcut: a locked action alone ends the run and
 * none of the earlier answers matter.
 *
 * The cut-short test reads the first flag word as 64 bits and narrows the result
 * with a cast. That is not decoration. The narrowing lets the low half compile to
 * a single `tst`, while the discarded high half still leaves a register holding
 * zero, and the 64-bit test on the second flag word spends that register for its
 * own zero half and for both halves of its comparison. Written as a plain 32-bit
 * mask the same function comes out four bytes shorter, with immediates in place
 * of that register.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* Both bits have to be up for a run to count as cut short. */
#define FLAGS_CUTSHORT 0x10000ULL
#define FLAGS2_CUTSHORT 0x8000000000ULL

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 nOwner;                   /* 0x0008 */
    u8 pad0009[9];
    u16 nHp;                     /* 0x0012 */
    u8 pad0014[0x450];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x228];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nSpare694 : 1;
    u8 bActionLocked : 1;        /* bit 3 */
    u8 bSequenceRunning : 1;     /* bit 4 */
    u8 nFlags694Top : 3;
};

/* Ov022ActionOwner */
struct ActionOwner {
    u8 pad000[0x328];
    struct Actor *pActor;        /* 0x328 */
    int nBudget;                 /* 0x32c */
};

extern int func_02030694(void);
extern int func_02030788(void);
extern int func_ov002_0206b7a4(void);
extern int func_ov022_020946e4(struct ActionOwner *pOwner);
extern int func_ov022_020ab350(struct Actor *pActor);

int func_ov022_020944ec(struct ActionOwner *pOwner)
{
    int bOver;
    struct Actor *pActor;

    pActor = pOwner->pActor;
    bOver = 0;
    if (func_02030694() == 0) {
        return bOver;
    }
    if (pActor->nHp == 0) {
        bOver = 1;
    }
    if (pOwner->nBudget > func_ov022_020946e4(pOwner)) {
        bOver = 1;
    }
    if ((u32)(pActor->nFlags & FLAGS_CUTSHORT) != 0
        && (pActor->nFlags2 & FLAGS2_CUTSHORT) != 0) {
        bOver = 1;
    }
    if (pActor->nOwner == func_02030788()) {
        if (func_ov002_0206b7a4() != 0 || func_ov022_020ab350(pActor) != 0) {
            bOver = 1;
        }
    } else {
        if (pActor->bActionLocked != 0) {
            return 1;
        }
    }
    return bOver;
}
