/* Ov022_RunShotCommand -- carry out one packed shot command.
 *
 * The owner field picks the actor and the channel field one of its shot
 * channels; a command for an owner with no actor is dropped.
 *
 * Command 1 clears a shot's state, command 3 sets bit 0 of its flags -- both
 * index the channel's shots by the low byte of the fuse field -- and command 2
 * refills the channel's budget.
 *
 * Command 0 unpacks the rest of the command into a shot request on the stack
 * and, while the channel still has budget, hands it to the channel's spawn
 * handler with the command's mode. A spawn that reports success spends one
 * unit of budget, unless bit 0 of the chosen descriptor's flags says this shot
 * is free.
 *
 * Two shapes carry the original's codegen: the two direction halfwords are
 * copied as one two-byte-aligned pair, which is what loads both before either
 * is stored, and the whole of command 0 lives inside its own switch arm, which
 * is what leaves the other three arms out of line behind it.
 */

typedef unsigned char u8;
typedef unsigned short u16;

struct ShotDir2 {
    short nDirX;
    short nDirY;
};

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct ShotCommand {
    u8 nOp : 2;                      /* 0x00 */
    u8 nOwner : 2;
    u8 nMode : 3;
    u8 : 1;
    u8 nChannel : 3;                 /* 0x01 */
    u8 nId0 : 3;
    u8 nId1 : 2;
    union {
        short nFuse;                 /* 0x02 */
        u8 nShot;
    } u;
    struct VecFx32 vecPos;           /* 0x04 */
    struct ShotDir2 dir;             /* 0x10 */
    u16 nDirZ;                       /* 0x14 */
    u8 nId2 : 3;                     /* 0x16 */
    u8 nDesc : 3;
    u8 nRig : 2;
};

struct ShotRequest {
    struct VecFx32 vecPos;           /* 0x00 */
    struct ShotDir2 dir;             /* 0x0c */
    short nDirZ;                     /* 0x10 */
    short nFuse;                     /* 0x12 */
    u8 pad14[4];
    int nId0;                        /* 0x18 */
    int nId1;                        /* 0x1c */
    int nId2;                        /* 0x20 */
    int nRig;                        /* 0x24 */
    int nDesc;                       /* 0x28 */
};

struct Shot {
    u8 nFlags;                       /* 0x00 */
    u8 pad01;
    signed char nState;              /* 0x02 */
    u8 pad03[0x1c5];
};

struct ShotDesc {
    unsigned int nFlags;             /* 0x00 */
    u8 pad04[0x4c];
};

struct ShotChannel {
    u8 pad00[0xc];
    struct Shot *pShots;             /* 0x0c */
    struct ShotDesc *pDescs;         /* 0x10 */
    u8 pad14[4];
    u8 nBudget;                      /* 0x18 */
    u8 nBudgetMax;                   /* 0x19 */
    u8 pad1a[2];
    int (*pfnSpawn)(struct ShotChannel *, struct ShotRequest *, int);
    u8 pad20[0x10];
};

struct Actor {
    u8 pad0000[0x2644];
    struct ShotChannel *pShotChannels;   /* 0x2644 */
};

extern struct Actor *func_01fffde0(int nOwner);

void func_ov022_02090a50(struct ShotCommand *pCmd)
{
    struct Actor *pActor;
    struct ShotChannel *pChannel;
    struct ShotRequest request;

    pActor = func_01fffde0(pCmd->nOwner);
    if (pActor == 0) {
        return;
    }
    pChannel = &pActor->pShotChannels[pCmd->nChannel];
    switch (pCmd->nOp) {
    case 0:
        request.vecPos = pCmd->vecPos;
        request.dir = pCmd->dir;
        request.nDirZ = pCmd->nDirZ;
        request.nFuse = pCmd->u.nFuse;
        request.nId0 = pCmd->nId0;
        request.nId1 = pCmd->nId1;
        request.nId2 = pCmd->nId2;
        request.nDesc = pCmd->nDesc;
        request.nRig = pCmd->nRig;
        if (pChannel->nBudget == 0) {
            return;
        }
        if (pChannel->pfnSpawn(pChannel, &request, pCmd->nMode) == 0) {
            return;
        }
        if ((pChannel->pDescs[pCmd->nDesc].nFlags & 1) != 0) {
            return;
        }
        pChannel->nBudget--;
        return;
    case 1:
        pChannel->pShots[pCmd->u.nShot].nState = 0;
        return;
    case 2:
        pChannel->nBudget = pChannel->nBudgetMax;
        return;
    case 3:
        pChannel->pShots[pCmd->u.nShot].nFlags |= 1;
    default:
        return;
    }
}
