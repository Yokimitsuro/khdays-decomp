/*
 * Game_ActionAssign - action-command handler for opcode group 0, sub-index 0 (the first entry of the
 * data_020425ec dispatch table): an operand-to-operand assignment. Reached from the gameplay action
 * interpreter (Game_RunActionScript); st is the action-system state, operand points at the command's
 * operand block (cmd+4). Always returns 1 (advance to the next command).
 *
 * The block's first halfword selects the mode:
 *  - mode 8: resolve both the source operand (operand+8) and the destination operand (operand+0) to
 *    their storage slots and copy the source slot's {kind, value} into the destination, zeroing the
 *    slot's middle halfword.
 *  - mode 4: resolve the source operand (operand+8), evaluate it to a scalar, then emit it through
 *    func_020235e8 together with the packed 32-bit immediate at operand+4 (split into its low and
 *    high halfwords).
 *  - any other mode: no-op (only the unconditional source resolve happens).
 *
 * THUMB. func_020218a4 resolves an operand reference to an 8-byte OperandSlot; func_02021980
 * evaluates a resolved slot to a scalar; func_020235e8 takes three u16 args.
 */

typedef struct {
    short kind;
    short pad;
    int   value;
} OperandSlot;

extern OperandSlot *func_020218a4(void *st, void *operand);
extern int  func_02021980(void *st, OperandSlot *slot);
extern void func_020235e8(unsigned short a, unsigned short b, unsigned short c);

int func_02021e84(void *st, short *operand)
{
    OperandSlot *src = func_020218a4(st, (char *)operand + 8);

    if (operand[0] == 8) {
        OperandSlot *dst = func_020218a4(st, operand);
        dst->kind  = src->kind;
        dst->pad   = 0;
        dst->value = src->value;
    } else if (operand[0] == 4) {
        int r = func_02021980(st, src);
        unsigned v = *(int *)((char *)operand + 4);
        func_020235e8((unsigned short)v, (unsigned short)(v >> 16), (unsigned short)r);
    }
    return 1;
}
