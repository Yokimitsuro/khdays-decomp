/* func_ov017_0207fc18 -- Ov017_DepositStart: start handler of the deposit (the multi-hit
 * prize object).  For each sequence the definition names, binds its node (0202a634 mode 1 / 4
 * on the resource from ov002 0206da70), puts it at the deposit's position (+0xe0) with the
 * deposit's facing (+0x18) and raises flag bit 5 on it: the idle sequence (+0x1b0, position
 * +0x254, facing +0x22c) -- taken from a copy of the position made before the bind -- which
 * is also started on the track of the current hit count (Ov017_DepositPlayAnim 0207fa40 with
 * the main length / frame +0x4cc / +0x4c8); the hit-effect sequence (+0x2b8, position +0x35c,
 * facing +0x334); the crack sequence (+0x3c0, position +0x464, facing +0x43c).  Then the hit
 * count (+0x4d8) is read from bits 1.. of the deposit's GameState field and the model marked
 * bound (bit 2 of +0x12). */
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
    u8   pad_00c[6];
    u16  nPieceFlags;         /* 0x012: bit 2 = model bound */
    u16  nStateField;         /* 0x014: GameState field */
    u8   nStateBit;           /* 0x016 */
    u8   pad_017;
    u16  nFacing;             /* 0x018 */
    u8   pad_01a[0xe0 - 0x1a];
    VecFx32 position;         /* 0x0e0 */
    u8   pad_0ec[0x1b0 - 0xec];
    u16  nSeqFlagsA;          /* 0x1b0: the idle sequence node */
    u8   pad_1b2[0x22c - 0x1b2];
    u16  nSeqFacingA;         /* 0x22c */
    u8   pad_22e[0x254 - 0x22e];
    VecFx32 seqPositionA;     /* 0x254 */
    u8   pad_260[0x2b8 - 0x260];
    u16  nSeqFlagsB;          /* 0x2b8: the hit-effect sequence node */
    u8   pad_2ba[0x334 - 0x2ba];
    u16  nSeqFacingB;         /* 0x334 */
    u8   pad_336[0x35c - 0x336];
    VecFx32 seqPositionB;     /* 0x35c */
    u8   pad_368[0x3c0 - 0x368];
    u16  nSeqFlagsC;          /* 0x3c0: the crack sequence node */
    u8   pad_3c2[0x43c - 0x3c2];
    u16  nSeqFacingC;         /* 0x43c */
    u8   pad_43e[0x464 - 0x43e];
    VecFx32 seqPositionC;     /* 0x464 */
    u8   pad_470[0x4c8 - 0x470];
    int  nMainFrame;          /* 0x4c8 */
    int  nMainLength;         /* 0x4cc */
    u8   pad_4d0[8];
    u8   nHits;               /* 0x4d8 */
} Ov017Deposit;

extern void *func_ov002_0206da70(const char *pName);                 /* name -> resource entry */
extern void  func_0202a634(void *pNode, void *pEntry, int nA, int nB); /* RegisterSeqAndInit */
extern void  func_ov017_0207fa40(Ov017Deposit *pSelf, void *pNode, int nTrack, int nLength, int nFrame); /* Ov017_DepositPlayAnim */
extern int   func_020235d0(u16 nField, u8 nBit);                     /* GameState_GetField */

void func_ov017_0207fc18(Ov017Deposit *pSelf)
{
    VecFx32 position;
    Ov017DepositDef *pDef;

    pDef = pSelf->pDef;
    if (pDef->szSeqA[0] != 0) {
        position = pSelf->position;
        func_0202a634(&pSelf->nSeqFlagsA, func_ov002_0206da70(pDef->szSeqA), 1, 4);
        pSelf->seqPositionA = position;
        pSelf->nSeqFacingA = pSelf->nFacing;
        pSelf->nSeqFlagsA |= 0x20;
        func_ov017_0207fa40(pSelf, &pSelf->nSeqFlagsA, pSelf->nHits, pSelf->nMainLength, pSelf->nMainFrame);
    }
    if (pDef->szSeqB[0] != 0) {
        func_0202a634(&pSelf->nSeqFlagsB, func_ov002_0206da70(pDef->szSeqB), 1, 4);
        pSelf->seqPositionB = pSelf->position;
        pSelf->nSeqFacingB = pSelf->nFacing;
        pSelf->nSeqFlagsB |= 0x20;
    }
    if (pDef->szSeqC[0] != 0) {
        func_0202a634(&pSelf->nSeqFlagsC, func_ov002_0206da70(pDef->szSeqC), 1, 4);
        pSelf->seqPositionC = pSelf->position;
        pSelf->nSeqFacingC = pSelf->nFacing;
        pSelf->nSeqFlagsC |= 0x20;
    }
    pSelf->nHits = ((u32)func_020235d0(pSelf->nStateField, pSelf->nStateBit) & 0xfffe) >> 1;
    pSelf->nPieceFlags |= 4;
}
