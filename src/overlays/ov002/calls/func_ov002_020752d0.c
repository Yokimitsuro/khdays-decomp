/* Script command: read four operands and set the values on a peer row.
 *
 * Operands are eight bytes apart, as everywhere in this command family. The first two go through
 * untouched; the third and fourth are narrowed to SIGNED bytes, which is what the row setter
 * expects, since it treats a negative fourth operand as "leave this field alone". The 0xffff
 * handed over as the third argument is the same idea for the middle field: the setter compares
 * against it and skips the write.
 *
 * Ghidra carries the operands as OperandSlot.
 */

extern int func_02021980(void *vm, char *operand);
extern void func_ov002_02072194(int a, int b, int c, int d, int e);

int func_ov002_020752d0(void *vm, char *table) {
    int first = func_02021980(vm, table);
    int second = func_02021980(vm, table + 8);
    int third = func_02021980(vm, table + 0x10);
    int fourth = func_02021980(vm, table + 0x18);

    func_ov002_02072194(first, second, 0xffff, (signed char)fourth, (signed char)third);
    return 1;
}
