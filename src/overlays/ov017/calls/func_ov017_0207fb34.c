/* func_ov017_0207fb34 -- Ov017_DepositAdvanceCrackFrame: advance the deposit's secondary animation
 * frame (+0x4d0) by nDelta and play it on pNode (ov002 0207c67c) while the model is bound
 * (bit 2 of +0x12); the frame clamps to the last one (length +0x4d4 minus one frame) and then
 * stops advancing.  Answers 1 while the animation still runs, 0 once it has finished. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov017Deposit {
    u8   pad_000[0x12];
    u16  nPieceFlags;         /* 0x012: bit 2 = model bound */
    u8   pad_014[0x4d0 - 0x14];
    int  nSubFrame;           /* 0x4d0 */
    int  nSubLength;          /* 0x4d4 */
} Ov017Deposit;

extern void func_ov002_0207c67c(void *pNode, int nFrame);            /* set the node's frame */

int func_ov017_0207fb34(Ov017Deposit *pSelf, void *pNode, int nDelta)
{
    int bDone;
    int nFrame;
    int nEnd;

    nFrame = pSelf->nSubFrame;
    nEnd = pSelf->nSubLength - 0x1000;
    bDone = 0;
    if (nFrame > nEnd) {
        pSelf->nSubFrame = nEnd;
        bDone = 1;
    }
    if (pSelf->nPieceFlags & 4) {
        func_ov002_0207c67c(pNode, pSelf->nSubFrame);
    }
    if (!bDone) {
        pSelf->nSubFrame += nDelta;
    }
    return !bDone;
}
