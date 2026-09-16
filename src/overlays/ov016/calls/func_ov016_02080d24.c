/* func_ov016_02080d24 -- Ov016_BreakableBreakStep: state function of a breaking breakable.  The
 * frame counter (+0x2b8) advances by the frame delta (ov002 0207687c) up to the definition's
 * length minus one frame (def +0x7c - 0x1000); while the model is bound (bit 2 of +0x12) the
 * node (+0x3c) is set to that frame (ov002 0207c67c) and drawn (0202aa9c).  When the end is
 * reached the track (+0x2bf) advances: past the last track (+0x2be) the piece is retired
 * (ov002 02076bd8 mode 0) and the terminal state (ov002 0207cea4) returned, otherwise the node
 * is rewound to the new track (ov002 0207c618) and enabled (0202af1c).  Returns 0 to stay. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef void *Ov016StateFn(void *pPiece);

typedef struct Ov016BreakableDef {
    u8 pad_00[0x7c];
    int nLength;              /* 0x7c */
} Ov016BreakableDef;

typedef struct Ov016Breakable {
    u8 pad_000[0x8];
    Ov016BreakableDef *pDef;  /* 0x08 */
    u8 pad_00c[0x6];
    u16 nPieceFlags;          /* 0x12: bit 2 = model bound */
    u8 pad_014[0x3c - 0x14];
    u16 nNodeFlagsB;          /* 0x3c: the model node */
    u8 pad_03e[0x2b8 - 0x3e];
    int nFrame;               /* 0x2b8 */
    u8 pad_2bc[2];
    u8 nFrames;               /* 0x2be: tracks */
    u8 nTrack;                /* 0x2bf */
} Ov016Breakable;

extern int  func_ov002_0207687c(void);                               /* frame delta */
extern void func_ov002_0207c67c(void *pNode, int nFrame);            /* set the node's frame */
extern void func_0202aa9c(void *pNode);                              /* Scene_DrawNode */
extern void func_ov002_0207c618(void *pNode, int nTrack, int nFrame); /* rewind a sequence */
extern void func_0202af1c(void *pNode);                              /* SceneNode_Enable */
extern void func_ov002_02076bd8(void *pPiece, int nMode);            /* retire a piece */
extern Ov016StateFn func_ov002_0207cea4;                             /* terminal state */

Ov016StateFn *func_ov016_02080d24(Ov016Breakable *pSelf)
{
    Ov016BreakableDef *pDef;
    int nFrame;
    int nEnd;
    int bDone;

    pDef = pSelf->pDef;
    nFrame = pSelf->nFrame + func_ov002_0207687c();
    pSelf->nFrame = nFrame;
    bDone = 0;
    nEnd = pDef->nLength - 0x1000;
    if (nFrame >= nEnd) {
        pSelf->nFrame = nEnd;
        bDone = 1;
    }
    if (pSelf->nPieceFlags & 4) {
        func_ov002_0207c67c(&pSelf->nNodeFlagsB, pSelf->nFrame);
        func_0202aa9c(&pSelf->nNodeFlagsB);
    }
    if (bDone) {
        pSelf->nTrack++;
        if (pSelf->nTrack < pSelf->nFrames) {
            if (pSelf->nPieceFlags & 4) {
                func_ov002_0207c618(&pSelf->nNodeFlagsB, pSelf->nTrack, 0);
                func_0202af1c(&pSelf->nNodeFlagsB);
            }
        } else {
            func_ov002_02076bd8(pSelf, 0);
            return func_ov002_0207cea4;
        }
    }
    return 0;
}
