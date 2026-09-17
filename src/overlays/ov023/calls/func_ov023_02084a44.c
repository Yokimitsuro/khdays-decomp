/* func_ov023_02084a44 -- Ov023_TurnActorToward: turn an actor's heading (+0x1a30 of its 0x1a64-byte
 * entry in the event block's table, +0x440) one step toward a target angle, the shorter way
 * round, at most 0x1000 (1/16 turn) a frame, and store it (02088ea8).  Once the target is
 * reached the actor's speed pair (+0x15b8) is set to 0x1000 / -1 (020895dc) and 1 returned,
 * else 0. */
typedef unsigned char  u8;

typedef struct Ov023Actor {
    u8   pad_0000[0x1a30];
    int  nAngle;              /* 0x1a30 */
    int  nAngleTarget;        /* 0x1a34 */
    u8   pad_1a38[0x1a64 - 0x1a38];
} Ov023Actor;

typedef struct Ov023EventBlock {
    u8   pad_000[0x440];
    Ov023Actor *pActors;      /* 0x440 */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

extern void func_ov023_02088ea8(Ov023Actor *pActor, int nAngle);   /* Ov023_ActorSetAngleTarget */
extern void func_ov023_020895dc(Ov023Actor *pActor, int nSpeed, int nArg); /* Ov023_ActorSetSpeedPair */

int func_ov023_02084a44(Ov023ScriptCtx *pCtx, int nActor, int nTarget)
{
    int nCurrent;
    Ov023Actor *pActors;
    int nDelta;
    int nNew;
    int nOffset;

    nOffset = nActor * sizeof(Ov023Actor);
    pActors = pCtx->pEvent->pActors;
    nCurrent = pActors[nActor].nAngle;
    nDelta = nTarget - nCurrent;
    if (nDelta < 0) {
        nDelta += 0x10000;
    }
    if (nDelta < 0x8000) {
        if (nDelta >= 0x1000) {
            nDelta = 0x1000;
        }
        nNew = nDelta + nCurrent;
        if (nNew > 0xffff) {
            nNew -= 0x10000;
        }
    } else {
        if (nDelta <= 0xf000) {
            nDelta = 0x1000;
        } else {
            nDelta = 0x10000 - nDelta;
        }
        nNew = nCurrent - nDelta;
        if (nNew < 0) {
            nNew += 0x10000;
        }
    }
    func_ov023_02088ea8(&pActors[nActor], nNew);
    if (nNew == nTarget) {
        /* the actor's byte offset is the value the compiler keeps across the call (r5); the
         * first two uses index the table, this one re-reads the table and adds it */
        func_ov023_020895dc((Ov023Actor *)((u8 *)pCtx->pEvent->pActors + nOffset), 0x1000, -1);
        return 1;
    }
    return 0;
}
