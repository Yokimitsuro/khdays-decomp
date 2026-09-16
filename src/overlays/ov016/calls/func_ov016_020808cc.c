/* func_ov016_020808cc -- Ov016_BreakableRelease: tear the breakable (the class-0x17 object that
 * spawns its drop when hit) down: release the sequence node
 * (+0x1b0, 0202a7dc) when the definition has one (def +0x68 non-zero), release the render
 * node (+0x2c, 0202ba18); when the breakable's GameState field has any of bits 1..15 set (it was
 * taken / consumed) retire the piece (ov002 02076bd8 mode 0); clear the active byte (+0x2be). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov016BreakableDef {
    u8 pad_00[0x68];
    signed char bHasSequence; /* 0x68 */
} Ov016BreakableDef;

typedef struct Ov016Breakable {
    u8 pad_000[0x8];
    Ov016BreakableDef *pDef;       /* 0x08 */
    u8 pad_00c[0x8];
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8 pad_017[0x2c - 0x17];
    u8 renderNode[0x1b0 - 0x2c];   /* 0x2c */
    u8 seqNode[0x2be - 0x1b0];     /* 0x1b0 */
    u8 bActive;               /* 0x2be */
} Ov016Breakable;

extern void func_0202a7dc(void *pNode);                 /* release a sequence node */
extern void func_0202ba18(void *pNode);                 /* Render_ReleaseNodeItem */
extern int  func_020235d0(u16 nField, u8 nBit);        /* GameState_GetField */
extern void func_ov002_02076bd8(void *pPiece, int nMode); /* retire a piece */

void func_ov016_020808cc(Ov016Breakable *pSelf)
{
    if (pSelf->pDef->bHasSequence != 0) {
        func_0202a7dc(pSelf->seqNode);
    }
    func_0202ba18(pSelf->renderNode);
    if ((u16)(((u32)func_020235d0(pSelf->nStateField, pSelf->nStateBit) & 0xfffe) >> 1) != 0) {
        func_ov002_02076bd8(pSelf, 0);
    }
    pSelf->bActive = 0;
}
