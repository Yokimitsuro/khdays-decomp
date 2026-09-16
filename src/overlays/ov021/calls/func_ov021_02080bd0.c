/* func_ov021_02080bd0 -- Ov021_EmblemCreate: creates an emblem piece from its class (ov002
 * 02076a38): sets the model node up (+0x124, 0202b87c with the piece as owner, mode 0), fills
 * the piece -- position (+0x2a8), facing (+0x18), state 0 (+0x2b4), no player (+0x2bc = -1),
 * a timer of 300 seconds (+0x2b8 = 0x12c000), bucket, the step function (+0xc =
 * Ov021_EmblemStep 020809e0), the GameState field / bit (+0x14 / +0x16) and +0x17 = 0xff --
 * and registers it (ov002 02076480). */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov021Emblem {
    u8   pad_000[0xc];
    void *pfnStep;            /* 0x00c */
    u8   nBucket;             /* 0x010 */
    u8   pad_011;
    u16  nPieceFlags;         /* 0x012 */
    u16  nStateField;         /* 0x014: GameState field */
    u8   nStateBit;           /* 0x016 */
    u8   nField17;            /* 0x017 */
    short nFacing;            /* 0x018 */
    u8   pad_01a[0x124 - 0x1a];
    u8   modelNode[0x2a8 - 0x124]; /* 0x124 */
    VecFx32 position;         /* 0x2a8 */
    u8   nState;              /* 0x2b4 */
    u8   pad_2b5[3];
    int  nTimer;              /* 0x2b8 */
    char nPlayer;             /* 0x2bc */
} Ov021Emblem;

extern Ov021Emblem *func_ov002_02076a38(void *pClass, int nSlot);    /* take a piece from the class table */
extern void  func_0202b87c(void *pNode, int nA, void *pOwner, void *pB, int nMode);
extern void  func_ov002_02076480(int nBucket, void *pPiece);          /* register the piece */
extern void *func_ov021_020809e0(Ov021Emblem *pSelf);                 /* Ov021_EmblemStep */

void func_ov021_02080bd0(void *pClass, u16 nSlot, u8 nBucket, VecFx32 *pPos, short nFacing, u16 nField, u8 nBit)
{
    Ov021Emblem *pPiece;

    pPiece = func_ov002_02076a38(pClass, nSlot);
    func_0202b87c(pPiece->modelNode, 0, pPiece, 0, 0);
    pPiece->position = *pPos;
    pPiece->nFacing = nFacing;
    pPiece->nState = 0;
    pPiece->nPlayer = -1;
    pPiece->nTimer = 0x12c000;
    pPiece->nBucket = nBucket;
    pPiece->pfnStep = (void *)func_ov021_020809e0;
    pPiece->nStateField = nField;
    pPiece->nStateBit = nBit;
    pPiece->nField17 = 0xff;
    func_ov002_02076480(nBucket, pPiece);
}
