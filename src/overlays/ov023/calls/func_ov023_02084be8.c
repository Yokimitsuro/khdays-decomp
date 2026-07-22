/* Bytecode op: resolve two operands, record the first as the current index at +0x488 of the
 * table block, and write the second into that index's 260-byte record (+0x128) and, when the
 * index is at least 2, into the record two slots back as well.  Returns 1 (advance). */
extern int func_02021980(char *vm, char *op);

int func_ov023_02084be8(char *vm, char *op) {
    int a = func_02021980(vm, op + 8);
    int b = func_02021980(vm, op);
    char *tbl = *(char **)(vm + 0x128);
    *(int *)(tbl + 0x488) = a;
    *(int *)(*(char **)(vm + 0x128) + a * 260 + 0x128) = b;
    if (a >= 2) {
        *(int *)(*(char **)(vm + 0x128) + (a - 2) * 260 + 0x128) = b;
    }
    return 1;
}
