/* func_ov017_0207fa7c -- Ov017_DepositAdvanceFrame: advance the deposit's main animation frame
 * (+0x4c8) by nDelta and play it on pNode (ov002 0207c67c) while the model is bound (bit 2 of
 * +0x12).  Past the last frame (length +0x4cc minus one frame) a looping animation wraps the
 * frame back by the length, a one-shot one clamps to the last frame and stops advancing.
 * Answers 1 while the animation still runs, 0 once a one-shot has finished. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov017Deposit {
    u8   pad_000[0x12];
    u16  nPieceFlags;         /* 0x012: bit 2 = model bound */
    u8   pad_014[0x4c8 - 0x14];
    int  nMainFrame;          /* 0x4c8 */
    int  nMainLength;         /* 0x4cc */
} Ov017Deposit;

extern void func_ov002_0207c67c(void *pNode, int nFrame);            /* set the node's frame */

int func_ov017_0207fa7c(Ov017Deposit *pSelf, void *pNode, int nDelta, int bLoop)
{
    int bDone;
    int nEnd;

    bDone = 0;
    if (bLoop) {
        nEnd = pSelf->nMainLength - 0x1000;
        if (pSelf->nMainFrame > nEnd) {
            pSelf->nMainFrame -= nEnd;
        }
    } else {
        nEnd = pSelf->nMainLength - 0x1000;
        if (pSelf->nMainFrame > nEnd) {
            pSelf->nMainFrame = nEnd;
            bDone = 1;
        }
    }
    if (pSelf->nPieceFlags & 4) {
        func_ov002_0207c67c(pNode, pSelf->nMainFrame);
    }
    if (!bDone) {
        pSelf->nMainFrame += nDelta;
    }
    return !bDone;
}
