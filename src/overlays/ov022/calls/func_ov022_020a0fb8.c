/* ov022: run the frame's three command handlers, then the fallback.
 *
 * Each of the three gets the same arguments and answers whether it took the
 * command. If any of them did, that is the answer and nothing else runs.
 *
 * Only when all three pass does the fallback get a turn, and even then it has
 * to resolve, and the hit it resolves has to be of the one kind this path
 * accepts, before the last handler is asked to deal with it.
 *
 * The hit slot is cleared up front so a handler that does not fill it cannot
 * leave the previous frame's answer behind.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Command {
    u8 pad00[0x14];
    u8 nTail;                    /* 0x14 */
};

struct Actor {
    u8 pad0000[0x26bc];
    int nHit;                    /* 0x26bc */
    int nHitKind;                /* 0x26c0 */
    u8 bHitHeld;                 /* 0x26c4 */
};

extern int func_ov022_0209e1b0(struct Actor *pActor, struct Command *pCmd,
                               void *pCtx);
extern int func_ov022_0209e540(struct Actor *pActor, struct Command *pCmd,
                               void *pCtx);
extern int func_ov022_0209eac4(struct Actor *pActor, struct Command *pCmd,
                               void *pCtx);
extern int func_ov022_020a1c28(struct Actor *pActor, struct Command *pCmd,
                               int *pHit);
extern int func_ov022_0209e4a4(struct Actor *pActor, void *pCtx, u8 *pTail);

int func_ov022_020a0fb8(struct Actor *pActor, struct Command *pCmd, void *pCtx)
{
    int bTaken;

    bTaken = 0;
    pActor->nHit = 0;
    pActor->bHitHeld = 0;
    if (func_ov022_0209e1b0(pActor, pCmd, pCtx) != 0) {
        bTaken = 1;
    }
    if (func_ov022_0209e540(pActor, pCmd, pCtx) != 0) {
        bTaken = 1;
    }
    if (func_ov022_0209eac4(pActor, pCmd, pCtx) != 0) {
        bTaken = 1;
    }
    if (bTaken == 0) {
        if (func_ov022_020a1c28(pActor, pCmd, &pActor->nHit) != 0) {
            if (pActor->nHitKind == 4) {
                bTaken = func_ov022_0209e4a4(pActor, pCtx, &pCmd->nTail);
            }
        }
    }
    return bTaken;
}
