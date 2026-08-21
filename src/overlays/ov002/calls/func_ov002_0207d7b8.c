typedef unsigned short u16;

/* One operand of a script command: a tag saying how the value is fetched and
 * the word that carries either the value itself or the reference to it. */
typedef struct {
    short kind;
    short pad;
    int   value;
} OperandSlot;

#define OPERAND_INT             1
#define OPERAND_REFERENCE       2
#define OPERAND_PACKED_SHORTS   4
#define OPERAND_PACKED_ALIAS    8
#define OPERAND_FX32            0x10
#define OPERAND_FX32_ALIAS      0x40

extern int func_02021980(void *pContext, OperandSlot *pOperand);
extern int func_02021994(void *pContext, OperandSlot *pOperand);
extern int func_02021948(void *pContext, OperandSlot *pOperand);
extern int func_ov002_0207679c(int nKind, u16 wId);
extern void func_ov002_02076e6c(int nObject, int nCount, void *pVals);

/* Script command with a variable-length operand list: resolve the target
 * object from the first two operands, gather the value list named by the
 * third, and invoke the object's callback slot 0x48 with it.
 *
 * Each trailing operand carries a tag saying how its value is fetched: a plain
 * integer, a resolved reference, a fixed point number, or - for tags 4 and 8 -
 * a pair of halfwords unpacked straight out of the descriptor's own word. The
 * word is read unsigned on purpose; a signed field shifts arithmetically and
 * the high halfword comes out wrong. Any other tag leaves the slot untouched.
 *
 * Two things about the shape, both of which cost bytes if written otherwise:
 *
 *   pArgs is reused as the cursor. A separate cursor variable makes mwcc keep
 *   the parameter and the cursor live at the same time, which needs a fifth
 *   callee-saved register and grows the function by two bytes.
 *
 *   pCountOp exists only to control SCHEDULING. The original forms the count
 *   operand's address, THEN advances the cursor, THEN calls; mwcc emits that
 *   order only when the argument is already in a temporary at the point the
 *   advance is written. Written as one expression the advance sinks below the
 *   call instead. Same instructions either way - only the position of
 *   `adds r4, #0x18` differs.
 *
 * Always returns 1.
 */
int func_ov002_0207d7b8(void *pContext, OperandSlot *pArgs)
{
    int aVals[32];
    int nKind;
    int nId;
    int nCount;
    int i;
    OperandSlot *pCountOp;

    nKind = func_02021980(pContext, &pArgs[0]);
    nId = func_02021980(pContext, &pArgs[1]);

    pCountOp = &pArgs[2];
    pArgs += 3;
    nCount = func_02021980(pContext, pCountOp);

    for (i = 0; i < nCount; i++) {
        switch (pArgs->kind) {
        case OPERAND_INT:
            aVals[i] = func_02021980(pContext, pArgs);
            break;
        case OPERAND_REFERENCE:
            aVals[i] = func_02021948(pContext, pArgs);
            break;
        case OPERAND_FX32:
        case OPERAND_FX32_ALIAS:
            aVals[i] = func_02021994(pContext, pArgs);
            break;
        case OPERAND_PACKED_SHORTS:
        case OPERAND_PACKED_ALIAS:
            ((u16 *)&aVals[i])[0] = (u16)pArgs->value;
            ((u16 *)&aVals[i])[1] = (u16)((unsigned int)pArgs->value >> 0x10);
            break;
        }
        pArgs++;
    }

    func_ov002_02076e6c(func_ov002_0207679c((unsigned char)nKind, (u16)nId), nCount, &aVals[0]);
    return 1;
}
