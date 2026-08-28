typedef unsigned short u16;
typedef signed short s16;

/* An event slot carrying one arithmetic step on a game-state field: the record
 * builder allocates 0x24 bytes and fills the four halfwords behind the slot's
 * own 0x1c. */
typedef struct {
    char pad0000[0x1c];
    u16 nFieldOffset;   /* 0x1c */
    u16 nFieldWidth;    /* 0x1e */
    s16 nOp;            /* 0x20 */
    u16 nOperand;       /* 0x22 */
} Ov002FieldOpItem;

/* The game-state bit-array accessors: GameState_GetField and GameState_SetField
 * in Ghidra, still linked under their addresses here. */
extern unsigned int func_020235d0(unsigned int nOffset, unsigned int nWidth);
extern void func_020235e8(unsigned int nOffset, unsigned int nWidth, unsigned int nValue);
extern long long func_0202060c(int nNumerator, int nDenominator);

/* Runs one arithmetic step against a game-state field: read the field, fold the
 * record's operand into it the way the opcode says, and write the result back.
 *
 * Every arm truncates to sixteen bits.  Opcodes 0 and 2 write a plain zero, as
 * does anything outside the table -- the opcode is read signed, so a negative
 * one falls through the unsigned range test into the same store.
 */
int func_ov002_02071030(Ov002FieldOpItem *pItem)
{
    unsigned int nValue;
    u16 nResult;

    nResult = 0;
    nValue = func_020235d0(pItem->nFieldOffset, pItem->nFieldWidth);
    switch (pItem->nOp) {
    case 0:
    case 2:
        break;
    case 7:
        nResult = pItem->nOperand;
        break;
    case 3:
        nResult = nValue + pItem->nOperand;
        break;
    case 4:
        nResult = nValue - pItem->nOperand;
        break;
    case 5:
        nResult = nValue * pItem->nOperand;
        break;
    case 6:
        nResult = (u16)func_0202060c(nValue, pItem->nOperand);
        break;
    case 1:
        nResult = ~nValue;
        break;
    }
    func_020235e8(pItem->nFieldOffset, pItem->nFieldWidth, nResult);
    return 2;
}
