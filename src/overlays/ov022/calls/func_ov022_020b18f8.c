/* ov022: route a new animation request into the actor's request slot.
 *
 * The slot is a small state machine, and where a request goes depends on what
 * the slot is already doing. While it is idle or settling the resolver decides
 * which track the request lands on, and if that is the track already active the
 * slot only re-arms the charge instead of restarting; while it is running or
 * tearing down the request is queued behind the current one.
 *
 * Caching the active track before the branch is what keeps the compiler from
 * reloading it: writing the requested id can alias the same object.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Actor;
struct AnimTrack;

struct AnimRequest {
    struct AnimTrack *pTrack;    /* 0x00 */
    struct Actor *pOwner;        /* 0x04 */
    u8 nState;                   /* 0x08 */
    u8 nHeld;                    /* 0x09 */
    signed char nSlot;           /* 0x0a */
    signed char nPending;        /* 0x0b */
    u8 pad0c[1];
    signed char nCharge;         /* 0x0d */
    signed char nActive;         /* 0x0e */
};

extern int func_ov022_020b1660(struct AnimRequest *pReq, int nWhich);
extern void func_ov022_020ad358(struct Actor *pOwner, int nCharge);
extern void func_ov022_020b1730(struct AnimRequest *pReq, int nTrack);

void func_ov022_020b18f8(struct AnimRequest *pReq, int nWhich)
{
    int nAnswer;
    int nActive;

    switch (pReq->nState) {
    case 0:
        nAnswer = func_ov022_020b1660(pReq, nWhich);
        nActive = pReq->nActive;
        if (nActive == nAnswer) {
            pReq->nSlot = nWhich;
            func_ov022_020ad358(pReq->pOwner, pReq->nCharge);
            return;
        }
        pReq->nSlot = nWhich;
        func_ov022_020b1730(pReq, nActive);
        return;
    case 1:
        pReq->nSlot = nWhich;
        break;
    case 2:
        if (pReq->nPending != nWhich && pReq->nSlot != nWhich) {
            pReq->nPending = nWhich;
        }
        break;
    case 3:
        if (pReq->nActive == func_ov022_020b1660(pReq, nWhich)) {
            pReq->nSlot = nWhich;
            func_ov022_020ad358(pReq->pOwner, pReq->nCharge);
            return;
        }
        if (pReq->nPending == nWhich) {
            return;
        }
        pReq->nState = 4;
        pReq->nPending = nWhich;
        return;
    case 4:
        if (pReq->nPending != nWhich) {
            pReq->nPending = nWhich;
        }
        break;
    default:
        break;
    }
}
