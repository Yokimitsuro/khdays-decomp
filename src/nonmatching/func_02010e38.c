/* NONMATCHING -- 76/76 B, one register pair: the ROM puts `base` in r5 and the first
 * mla result in r6; mwcc does the reverse (base r6, result r5). Everything else matches.
 *
 * Ruled out 2026-07-18: swapping the base/dest declaration order, and dropping the `base`
 * local entirely so each store inlines `(int)data_02042418`. The colouring does not move.
 * Note mwcc gives the FIRST-declared value the highest callee-saved register (r6) while the
 * ROM gives r6 to the first computed RESULT -- so it is an allocation-order difference, not
 * something the source spells. */
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
