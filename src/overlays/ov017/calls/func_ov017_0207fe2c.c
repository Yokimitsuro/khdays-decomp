/* func_ov017_0207fe2c -- Ov017_DepositStep: state function of the deposit (the multi-hit
 * prize object), switching on its hit state (+0x4da).  State 0 (idle): the idle sequence
 * (+0x1b0) loops and the hit-effect (+0x2b8) / crack (+0x3c0) sequences run while their
 * animation flags (bits 0 / 1 of +0x4db) are set, each flag dropping when its animation ends
 * (Ov017_DepositAdvanceFrame 0207fa7c / Ov017_DepositAdvanceCrackFrame 0207fb34).  State 2 (a
 * hit was acknowledged): the hit count (+0x4d8) grows and is written to its GameState field
 * (+0x4e0 / +0x4e2); below the maximum (+0x4d9, and 4) the idle sequence restarts on the new
 * track (Ov017_DepositPlayAnim 0207fa40), otherwise the render node's resources are released
 * (0202bc30), the piece leaves the room (bit 3 of +0x12) and the idle sequence's scale
 * (+0x260) is zeroed; the drop point (+0x1c) sinks by 0x100; the crack sequence takes the
 * position (+0x464) and the hit effect a copy of it lowered by 0x800 and jittered by
 * +/- (0..9) * 100 on each axis (Session_RandNextScaled 020307f4) (+0x35c), the effect is
 * played over 0x1e000 (0207fa40) and the cracks on track hits - 1 (at most 2) over 0xf000
 * (0207faf8); the next state is 4 (cooldown, timer +0x4dc cleared, effect scale 0xccd) while
 * hits remain, else 5 (spent, scale 0x1333) (+0x368..+0x370, a chained assignment); in session mode (bit 2 of
 * 0204c240) a prize of (drop multiplier ov002 0206e6d0 * 10, rounded up) is dropped at the
 * start position (ov002 02077cec on a six-byte amount table); both animation flags are set.
 * State 5 (spent): the sequences run on and once the hit effect ends the piece retires
 * (ov002 02076bd8) into state 6 and returns the terminal state (ov002 0207cea4).  State 4
 * (cooldown): the idle loops, the cooldown grows by 0xcd (60 Hz, 02023c40 == 1) or 0x89 per
 * frame, the crack and hit-effect sequences run, and at 0x800 the state returns to 0.  States
 * 1 and 3 wait.  Finally, while the model is bound (bit 2 of +0x12), the idle sequence is
 * drawn (0202aa9c) and the hit effect / cracks too while their flags are set.  Returns 0. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov017DepositDef {
    u8   pad_00[0x58];
    char szSeqA[0x10];        /* 0x58: idle */
    char szSeqB[0x10];        /* 0x68: hit effect */
    char szSeqC[0x10];        /* 0x78: cracks */
} Ov017DepositDef;

typedef struct Ov017Deposit {
    u8   pad_000[8];
    Ov017DepositDef *pDef;    /* 0x008 */
    u8   pad_00c[4];
    u8   nBucket;             /* 0x010 */
    u8   pad_011;
    u16  nPieceFlags;         /* 0x012: bit 2 = model bound, bit 3 = in the room */
    u8   pad_014[0x1c - 0x14];
    VecFx32 start;            /* 0x01c: the drop point, sinking 0x100 per hit */
    int  nTop;                /* 0x028 */
    u8   renderNode[0xe0 - 0x2c]; /* 0x02c */
    VecFx32 position;         /* 0x0e0 */
    u8   pad_0ec[0x1b0 - 0xec];
    u16  nSeqFlagsA;          /* 0x1b0: the idle sequence node */
    u8   pad_1b2[0x260 - 0x1b2];
    VecFx32 seqScaleA;        /* 0x260 */
    u8   pad_26c[0x2b8 - 0x26c];
    u16  nSeqFlagsB;          /* 0x2b8: the hit-effect sequence node */
    u8   pad_2ba[0x35c - 0x2ba];
    VecFx32 seqPositionB;     /* 0x35c */
    VecFx32 seqScaleB;        /* 0x368 */
    u8   pad_374[0x3c0 - 0x374];
    u16  nSeqFlagsC;          /* 0x3c0: the crack sequence node */
    u8   pad_3c2[0x464 - 0x3c2];
    VecFx32 seqPositionC;     /* 0x464 */
    u8   pad_470[0x4c8 - 0x470];
    int  nMainFrame;          /* 0x4c8 */
    int  nMainLength;         /* 0x4cc */
    int  nCrackFrame;         /* 0x4d0 */
    int  nCrackLength;        /* 0x4d4 */
    u8   nHits;               /* 0x4d8 */
    u8   nMaxHits;            /* 0x4d9 */
    u8   nHitState;           /* 0x4da */
    u8   nAnimFlags;          /* 0x4db: bit 0 hit effect playing, bit 1 cracks playing */
    u32  nCooldown;           /* 0x4dc */
    u16  nHitField;           /* 0x4e0: GameState field holding the hit count */
    u8   nHitBit;             /* 0x4e2 */
} Ov017Deposit;

extern int   func_ov002_0207687c(void);                               /* frame delta */
extern int   func_ov017_0207fa7c(Ov017Deposit *pSelf, void *pNode, int nDelta, int bLoop); /* Ov017_DepositAdvanceFrame */
extern int   func_ov017_0207fb34(Ov017Deposit *pSelf, void *pNode, int nDelta, int bLoop); /* Ov017_DepositAdvanceCrackFrame (the loop flag is ignored) */
extern void  func_020235e8(u16 nField, u8 nBit, u16 nValue);          /* GameState_SetField */
extern void  func_0202bc30(void *pNode);                              /* release the node's resources */
extern void  func_ov017_0207fa40(Ov017Deposit *pSelf, void *pNode, int nTrack, int nLength, int nFrame); /* Ov017_DepositPlayAnim */
extern void  func_ov017_0207faf8(Ov017Deposit *pSelf, void *pNode, int nTrack, int nLength, int nFrame); /* Ov017_DepositPlayCrackAnim */
extern u32   func_020307f4(int nRange);                               /* Session_RandNextScaled */
extern int   func_ov002_0206e6d0(void);                               /* the drop multiplier */
extern void  func_ov002_02077cec(const u8 *aAmount, int nCtxIndex, const VecFx32 *pPlace); /* spawn the drops */
extern void  func_ov002_02076bd8(void *pPiece, int nMode);            /* retire a piece */
extern int   func_02023c40(void);                                     /* frame-rate flag, 1 when running 60Hz */
extern void  func_0202aa9c(void *pNode);                              /* Scene_DrawNode */
extern void *func_ov002_0207cea4(void *pPiece);                       /* terminal state */
extern u8    data_0204c240;                                           /* session bits */

void *func_ov017_0207fe2c(Ov017Deposit *pSelf)
{
    VecFx32 position;
    Ov017DepositDef *pDef;
    int nDelta;
    u8 nHits;
    int i;
    int nOffset;

    pDef = pSelf->pDef;
    nDelta = func_ov002_0207687c();
    switch (pSelf->nHitState) {
    case 0:
        if (pDef->szSeqA[0] != 0) {
            func_ov017_0207fa7c(pSelf, &pSelf->nSeqFlagsA, nDelta, 1);
        }
        if ((pSelf->nAnimFlags & 1) && !func_ov017_0207fa7c(pSelf, &pSelf->nSeqFlagsB, nDelta, 0)) {
            pSelf->nAnimFlags &= ~1;
        }
        if ((pSelf->nAnimFlags & 2) && !func_ov017_0207fb34(pSelf, &pSelf->nSeqFlagsC, nDelta, 0)) {
            pSelf->nAnimFlags &= ~2;
        }
        break;
    case 1:
        break;
    case 2:
        pSelf->nHits++;
        func_020235e8(pSelf->nHitField, pSelf->nHitBit, pSelf->nHits);
        nHits = pSelf->nHits;
        if (!(nHits < pSelf->nMaxHits && nHits < 4)) {
            func_0202bc30(pSelf->renderNode);
            pSelf->nPieceFlags &= ~8;
            if (pDef->szSeqA[0] != 0) {
                pSelf->seqScaleA.z = 0;
                pSelf->seqScaleA.y = 0;
                pSelf->seqScaleA.x = 0;
            }
        } else if (pDef->szSeqA[0] != 0) {
            func_ov017_0207fa40(pSelf, &pSelf->nSeqFlagsA, nHits, pSelf->nMainLength, pSelf->nMainFrame);
        }
        pSelf->start.y -= 0x100;
        position = pSelf->position;
        pSelf->seqPositionC = position;
        position.y -= 0x800;
        for (i = 0; i < 3; i++) {
            nOffset = func_020307f4(10) * 100;
            if (func_020307f4(2) == 0) {
                nOffset *= -1;
            }
            if (i == 0) {
                position.x += nOffset;
            } else if (i == 1) {
                position.y += nOffset;
            } else {
                position.z += nOffset;
            }
        }
        pSelf->seqPositionB = position;
        func_ov017_0207fa40(pSelf, &pSelf->nSeqFlagsB, 0, 0x1e000, 0);
        func_ov017_0207faf8(pSelf, &pSelf->nSeqFlagsC, pSelf->nHits > 3 ? 2 : pSelf->nHits - 1, 0xf000, 0);
        if (pSelf->nHits < pSelf->nMaxHits) {
            pSelf->nCooldown = 0;
            pSelf->nHitState = 4;
            pSelf->seqScaleB.x = pSelf->seqScaleB.y = pSelf->seqScaleB.z = 0xccd;
        } else {
            pSelf->nHitState = 5;
            pSelf->seqScaleB.x = pSelf->seqScaleB.y = pSelf->seqScaleB.z = 0x1333;
        }
        if (data_0204c240 & 4) {
            u8 aDrop[6] = {0, 0, 0, 0, 0, 0};
            aDrop[0] = (func_ov002_0206e6d0() * 10 + 0xfff) >> 12;
            func_ov002_02077cec(aDrop, pSelf->nBucket, &pSelf->start);
        }
        pSelf->nAnimFlags |= 3;
        break;
    case 3:
        break;
    case 5:
        if (pDef->szSeqA[0] != 0) {
            func_ov017_0207fa7c(pSelf, &pSelf->nSeqFlagsA, nDelta, 1);
        }
        if ((pSelf->nAnimFlags & 2) && !func_ov017_0207fb34(pSelf, &pSelf->nSeqFlagsC, nDelta, 0)) {
            pSelf->nAnimFlags &= ~2;
        }
        if (!func_ov017_0207fa7c(pSelf, &pSelf->nSeqFlagsB, nDelta, 0)) {
            pSelf->nAnimFlags &= ~1;
            pSelf->nHitState = 6;
            func_ov002_02076bd8(pSelf, 0);
            return func_ov002_0207cea4;
        }
        break;
    case 4:
        if (pDef->szSeqA[0] != 0) {
            func_ov017_0207fa7c(pSelf, &pSelf->nSeqFlagsA, nDelta, 1);
        }
        pSelf->nCooldown += func_02023c40() == 1 ? 0xcd : 0x89;
        if ((pSelf->nAnimFlags & 2) && !func_ov017_0207fb34(pSelf, &pSelf->nSeqFlagsC, nDelta, 0)) {
            pSelf->nAnimFlags &= ~2;
        }
        if (!func_ov017_0207fa7c(pSelf, &pSelf->nSeqFlagsB, nDelta, 0)) {
            pSelf->nAnimFlags &= ~1;
        }
        if (pSelf->nCooldown >= 0x800) {
            pSelf->nHitState = 0;
        }
        break;
    }
    if (pSelf->nPieceFlags & 4) {
        if (pDef->szSeqA[0] != 0) {
            func_0202aa9c(&pSelf->nSeqFlagsA);
        }
        if (pDef->szSeqB[0] != 0 && (pSelf->nAnimFlags & 1)) {
            func_0202aa9c(&pSelf->nSeqFlagsB);
        }
        if (pDef->szSeqC[0] != 0 && (pSelf->nAnimFlags & 2)) {
            func_0202aa9c(&pSelf->nSeqFlagsC);
        }
    }
    return 0;
}
