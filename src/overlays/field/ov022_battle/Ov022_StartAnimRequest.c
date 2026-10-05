/* ov022: start the request slot on a part model.
 *
 * Builds the path of the model the request wants and hands it to the loader.
 * The resolver answers with a shape index; the first nine name a file in the
 * table, anything else falls back to the numbered variant the request carries.
 * The path is always under the owning character's own folder.
 *
 * If the loader hands back a track the slot goes to running and remembers which
 * shape it is on; if it hands back nothing the slot goes to starting so the
 * stepper retries.
 */

#include "nitro/types.h"

struct AnimTrack;

struct Node {
    u8 pad00[4];
    u16 nAnimFlags;              /* 0x04 */
};

struct Actor {
    u8 pad00[9];
    u8 nId;                      /* 0x09 */
    u8 pad0a[2];
    int nModel;                  /* 0x0c */
    u8 pad10[0x10];
    struct Node *pNode;          /* 0x20 */
};

struct AnimRequest {
    struct AnimTrack *pTrack;    /* 0x00 */
    struct Actor *pOwner;        /* 0x04 */
    u8 nState;                   /* 0x08 */
    u8 nHeld;                    /* 0x09 */
    signed char nSlot;           /* 0x0a */
    signed char nPending;        /* 0x0b */
    signed char nVariant;        /* 0x0c */
    signed char nCharge;         /* 0x0d */
    signed char nActive;         /* 0x0e */
};

struct ShapeTable {
    const char *aFile[9];
};

extern const struct ShapeTable data_ov022_020b2850;
extern const char *const data_02042a70[];
extern const char gOv022BaChPathFmt[];
extern const char gOv022BaChEtaPackPathFmt[];

extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int Ov022_ResolveRequestPart(struct AnimRequest *pReq, int nWhich);
extern void Ov022_ConfigureGridSlotMode(int nId, int nMode);
extern struct AnimTrack *Ov022_AcquireGridSlot(const char *pPath, int nId,
                                             int nFlags, u16 *pBlock);

void Ov022_StartAnimRequest(struct AnimRequest *pReq, int nTrack)
{
    struct ShapeTable shapes;
    char szPath[128];
    struct Actor *pOwner;
    int nShape;

    pOwner = pReq->pOwner;
    shapes = data_ov022_020b2850;
    nShape = Ov022_ResolveRequestPart(pReq, pReq->nSlot);
    if (nShape < 9) {
        OS_SPrintf(szPath, gOv022BaChPathFmt, data_02042a70[pOwner->nModel],
                   shapes.aFile[nShape]);
    } else if (nShape == 4) {
        OS_SPrintf(szPath, gOv022BaChPathFmt, data_02042a70[pOwner->nModel],
                   shapes.aFile[8]);
    } else {
        OS_SPrintf(szPath, gOv022BaChEtaPackPathFmt, data_02042a70[pOwner->nModel],
                   pReq->nVariant);
    }
    Ov022_ConfigureGridSlotMode(pOwner->nId, 2);
    pReq->pTrack = Ov022_AcquireGridSlot(szPath, pOwner->nId, 0,
                                       &pOwner->pNode->nAnimFlags);
    if (pReq->pTrack == 0) {
        pReq->nState = 1;
        return;
    }
    pReq->nHeld |= 1;
    pReq->nActive = nShape;
    pReq->nState = 2;
}
