/* func_ov016_0207fa68 -- Ov016_LiftBindSequence: bind the lift's sequence node (+0x1b0) to the
 * definition's sequence resource (name at def +0x58, ov002 0206da70, 0202a634 mode 1 / 4);
 * unless the render node (+0x28) already carries a palette (bit 5 of +0x38), copy the lift's
 * palette id (+0x18) into it (+0xb8) and flag it (bit 5 of +0x3c); the sequence node gets
 * the palette id (+0x22c) and its flag (bit 5 of +0x1b0) unconditionally. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov016LiftDef {
    u8 pad_00[0x58];
    char szSequence[0x10];    /* 0x58 */
} Ov016LiftDef;

typedef struct Ov016Lift {
    u8 pad_000[0x8];
    Ov016LiftDef *pDef;       /* 0x08 */
    u8 pad_00c[0xc];
    u16 nPalette;             /* 0x18 */
    u8 pad_01a[0x38 - 0x1a];
    int nNodeFlagsA;          /* 0x38: bit 5 = palette set (render node +0x10) */
    u16 nNodeFlagsB;          /* 0x3c */
    u8 pad_03e[0xb8 - 0x3e];
    u16 nNodePalette;         /* 0xb8 */
    u8 pad_0ba[0x1b0 - 0xba];
    u16 nSeqFlags;            /* 0x1b0: sequence node */
    u8 pad_1b2[0x22c - 0x1b2];
    u16 nSeqPalette;          /* 0x22c */
} Ov016Lift;

extern void *func_ov002_0206da70(const char *pName);                 /* name -> resource entry */
extern void  func_0202a634(void *pNode, void *pEntry, int nA, int nB); /* RegisterSeqAndInit */

void func_ov016_0207fa68(Ov016Lift *pSelf)
{
    u16 nPalette;

    func_0202a634(&pSelf->nSeqFlags, func_ov002_0206da70(pSelf->pDef->szSequence), 1, 4);
    nPalette = pSelf->nPalette;
    if ((pSelf->nNodeFlagsA & 0x20) == 0) {
        pSelf->nNodePalette = nPalette;
        pSelf->nNodeFlagsB |= 0x20;
    }
    pSelf->nSeqPalette = pSelf->nPalette;
    pSelf->nSeqFlags |= 0x20;
}
