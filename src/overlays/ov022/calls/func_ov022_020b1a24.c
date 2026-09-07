/* ov022: step one animation request.
 *
 * The per-frame tick runs this on the actor's request slot. State 1 starts a
 * request, state 2 toggles it, and state 4 tears it down: it releases whichever
 * of the two tracks are still held, and before releasing the second it checks
 * that the node's animation block is idle and that the track actually owns the
 * node's animation, rebinding it if so.
 *
 * Once the teardown finishes, the slot either goes idle or immediately starts
 * the request that was queued behind it.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct AnimTrack {
    u8 pad00[4];
    short nCount;                /* 0x04 */
    u8 pad06[0xe];
    void **pIds;                   /* 0x14 */
};

struct Node {
    u8 pad00[4];
    u16 nAnimFlags;              /* 0x04 */
    u8 pad06[0xa];
    void *pAnimSrc;                 /* 0x10 */
    u8 pad14[0xd0];
    u8 animBind;                 /* 0xe4 */
};

struct Owner {
    u8 pad00[0x20];
    struct Node *pNode;          /* 0x20 */
};

struct AnimRequest {
    struct AnimTrack *pTrack;    /* 0x00 */
    struct Owner *pOwner;        /* 0x04 */
    u8 nState;                   /* 0x08 */
    u8 nFlags;                   /* 0x09 */
    signed char nSlot;           /* 0x0a */
    signed char nPending;        /* 0x0b */
};

extern void func_ov022_020b1730(struct AnimRequest *pReq);
extern int func_ov022_020b1848(struct AnimRequest *pReq);
extern void func_ov022_020b152c(struct AnimTrack *pTrack);
extern void func_0202accc(u16 *pAnim, int nA, u8 *pBind, int nB);
extern void func_ov022_020b18f8(struct AnimRequest *pReq, int nWhich);

int func_ov022_020b1a24(struct AnimRequest *pReq)
{
    struct Node *pNode;
    int nResult;
    int bDone;
    int bFound;
    int i;

    nResult = 0;
    if (pReq->nState == 0) {
        return nResult;
    }
    switch (pReq->nState) {
    case 1:
        func_ov022_020b1730(pReq);
        break;
    case 2:
        nResult = func_ov022_020b1848(pReq);
        break;
    case 4:
        bDone = 1;
        if ((pReq->nFlags & 1) != 0) {
            func_ov022_020b152c(pReq->pTrack);
            pReq->nFlags &= ~1;
        }
        if ((pReq->nFlags & 2) != 0) {
            pNode = pReq->pOwner->pNode;
            if ((pNode->nAnimFlags & 4) != 0) {
                bDone = 0;
            } else {
                bFound = 0;
                for (i = 0; i < pReq->pTrack->nCount; i++) {
                    if (pReq->pTrack->pIds[i] == pNode->pAnimSrc) {
                        bFound = 1;
                        break;
                    }
                }
                if (bFound != 0) {
                    func_0202accc(&pNode->nAnimFlags, 0, &pNode->animBind, 0);
                }
            }
            if (bDone != 0) {
                func_ov022_020b152c(pReq->pTrack);
                pReq->nFlags &= ~2;
            }
        }
        if (bDone != 0) {
            pReq->nState = 0;
            if (pReq->nPending == -1) {
                pReq->nFlags = 0;
                pReq->nSlot = -1;
            } else {
                pReq->nSlot = -1;
                func_ov022_020b18f8(pReq, pReq->nPending);
                pReq->nPending = -1;
            }
        }
        break;
    default:
        break;
    }
    return nResult;
}
