/* Script opcode: hand a resolved target and an int operand to the ov002
 * dispatcher as request 0x11, then drop BG3 and BG1 to priority 0.
 *
 * Two codegen notes about the register pair. BG3CNT and BG1CNT are four bytes
 * apart, so the original loads one pointer and walks it back rather than
 * loading a second address; that is what keeps the literal pool to one word.
 * And the masked value is computed into a temporary before being stored: a
 * plain read-modify-write on the register keeps the pointer in the second
 * scratch register instead of the first and swaps the pair throughout.
 */
extern int func_02021948(void *vm, unsigned short *pc);
extern int func_02021980(void *vm, unsigned short *pc);
extern void func_ov002_0206aeb8(int target, int value, int flags, int request);

int func_ov020_0207fac8(void *vm, unsigned short *pc)
{
    volatile unsigned short *reg = (volatile unsigned short *)0x0400000e;
    int target;
    int value;
    unsigned short h;

    target = func_02021948(vm, pc);
    value = func_02021980(vm, pc + 4);
    func_ov002_0206aeb8(target, value, 0, 0x11);

    h = *reg & ~3;
    *reg = h;
    reg -= 2;
    h = *reg & ~3;
    *reg = h;
    return 1;
}
