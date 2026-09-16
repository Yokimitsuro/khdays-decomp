/* func_ov023_02087564 -- Ov023_ActorFindPending: look up an id in the actor's seven pending
 * entries (+0x984, 0x28 bytes each, id at +0x18).  Returns the index holding the id, else the
 * first free entry (id -1), else -1. */
typedef unsigned char  u8;

typedef struct Ov023Pending {
    u8   pad_00[0x18];
    int  nId;                 /* 0x18 */
    u8   pad_1c[0x28 - 0x1c];
} Ov023Pending;               /* 0x28 */

typedef struct Ov023Actor {
    u8   pad_0000[0x984];
    Ov023Pending aPending[7]; /* 0x0984 */
} Ov023Actor;

int func_ov023_02087564(Ov023Actor *pActor, int nId)
{
    int i;
    int nResult;
    Ov023Pending *pPending;

    pPending = pActor->aPending;
    nResult = -1;
    for (i = 0; i < 7; i++) {
        if (nId == pPending->nId) {
            nResult = i;
            break;
        }
        if (pPending->nId == -1 && nResult == -1) {
            nResult = i;
        }
        pPending++;
    }
    return nResult;
}
