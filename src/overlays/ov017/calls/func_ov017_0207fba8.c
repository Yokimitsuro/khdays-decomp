/* func_ov017_0207fba8 -- Ov017_DepositRelease: release handler of the deposit (the multi-hit prize object).  Frees the render
 * node's item (+0x2c, 0202ba18) and each of the three sequence nodes the definition names
 * (+0x1b0 for def +0x58, +0x2b8 for def +0x68, +0x3c0 for def +0x78; 0202a7dc), then drops
 * the model-bound bit (bit 2 of +0x12). */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov017DepositDef {
    u8   pad_00[0x58];
    char szSeqA[0x10];        /* 0x58 */
    char szSeqB[0x10];        /* 0x68 */
    char szSeqC[0x10];        /* 0x78 */
} Ov017DepositDef;

typedef struct Ov017Deposit {
    u8   pad_000[8];
    Ov017DepositDef *pDef;       /* 0x008 */
    u8   pad_00c[6];
    u16  nPieceFlags;         /* 0x012: bit 2 = model bound */
    u8   pad_014[0x2c - 0x14];
    u8   renderNode[0x1b0 - 0x2c]; /* 0x02c */
    u8   seqNodeA[0x2b8 - 0x1b0];  /* 0x1b0 */
    u8   seqNodeB[0x3c0 - 0x2b8];  /* 0x2b8 */
    u8   seqNodeC[0x4c8 - 0x3c0];  /* 0x3c0 */
} Ov017Deposit;

extern void func_0202ba18(void *pNode);                              /* Render_ReleaseNodeItem */
extern void func_0202a7dc(void *pNode);                              /* release a sequence node */

void func_ov017_0207fba8(Ov017Deposit *pSelf)
{
    Ov017DepositDef *pDef;

    pDef = pSelf->pDef;
    func_0202ba18(pSelf->renderNode);
    if (pDef->szSeqA[0] != 0) {
        func_0202a7dc(pSelf->seqNodeA);
    }
    if (pDef->szSeqB[0] != 0) {
        func_0202a7dc(pSelf->seqNodeB);
    }
    if (pDef->szSeqC[0] != 0) {
        func_0202a7dc(pSelf->seqNodeC);
    }
    pSelf->nPieceFlags &= ~4;
}
