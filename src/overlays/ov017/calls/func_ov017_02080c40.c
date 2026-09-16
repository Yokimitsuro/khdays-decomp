/* func_ov017_02080c40 -- Ov017_ScriptOpRetirePiece: script op that resolves the piece named
 * by its two operands (key and argument, ov002 0207679c) and retires it: an item piece (class
 * kinds 0x1d / 0x1e) through Ov017_ItemRetire (02080a60), any other through the kind dispatch
 * Ov017_RetireByKind (020804b4).  Always 1. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov017PieceDef {
    u8   pad_00[0x4c];
    u16  nKind;               /* 0x4c */
} Ov017PieceDef;

typedef struct Ov017Piece {
    u8   pad_00[8];
    Ov017PieceDef *pDef;      /* 0x08 */
} Ov017Piece;

extern int   func_02021980(int vm, u16 *pc);                          /* ScriptVm_ReadOperandInt */
extern Ov017Piece *func_ov002_0207679c(int nKey, u16 nArg);           /* resolve a piece */
extern void  func_ov017_02080a60(Ov017Piece *pPiece);                 /* Ov017_ItemRetire */
extern void  func_ov017_020804b4(Ov017Piece *pPiece);                 /* Ov017_RetireByKind */

int func_ov017_02080c40(int vm, u16 *pc)
{
    int nKey;
    int nArg;
    Ov017Piece *pPiece;

    nKey = func_02021980(vm, pc);
    nArg = func_02021980(vm, pc + 4);
    pPiece = func_ov002_0207679c(nKey & 0xff, nArg & 0xffff);
    if ((u16)(pPiece->pDef->nKind + 0xffe3) <= 1) {
        func_ov017_02080a60(pPiece);
    } else {
        func_ov017_020804b4(pPiece);
    }
    return 1;
}
