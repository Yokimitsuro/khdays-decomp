/* NONMATCHING — single-register coloring tie. Every instruction matches in opcode,
 * operand and order; the ROM colors the loop-invariant base pointer to r5 and the
 * first product to r6, while every mwcc build we have swaps just those two (base->r6,
 * first product->r5). All other registers (r4, r1, r2, ip, lr) and the store order are
 * identical. Swept 27 builds x 6 opts, none flips the r5/r6 choice.
 *
 * Publish five sub-object transform pointers into the shared draw record
 * (data_020423fc): field +8..+0x18 each get base (data_02042418) + param_N * 0x18. */
extern char data_020423fc[];
extern char data_02042418[];
void func_02010e38(int param_1, int param_2, int param_3, int param_4, int param_5) {
    int base = (int)data_02042418;
    char *dest = data_020423fc;
    *(int *)(dest + 8) = param_1 * 0x18 + base;
    *(int *)(dest + 0xc) = param_2 * 0x18 + base;
    *(int *)(dest + 0x10) = param_3 * 0x18 + base;
    *(int *)(dest + 0x14) = param_4 * 0x18 + base;
    *(int *)(dest + 0x18) = param_5 * 0x18 + base;
}
