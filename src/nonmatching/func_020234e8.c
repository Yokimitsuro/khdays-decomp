/* NONMATCHING -- and the blocker is NOT the C. Size is exact at 76 bytes, every
 * instruction matches, and all six reloc OFFSETS line up. The single difference
 * is the SYMBOL NAME on the second literal-pool word:
 *
 *     mine: {..., 64: data_0204be08, 68: data_0204be0a}
 *     orig: {..., 64: data_0204be08, 68: data_0204be08}
 *
 * The ROM's pool holds 0x0204be08 TWICE, in two separate words. mwcc will not
 * emit two pool entries for one symbol -- it CSEs them, which lands at 72 bytes
 * (tried plain, and with the halfword declared volatile). Two entries appear only
 * when the two references are to DIFFERENT symbols, which is why pointing the
 * func_02031384 argument at the adjacent data_0204be0a produces a byte- and
 * offset-perfect function with one wrong reloc name.
 *
 * So the original translation unit had TWO distinct declarations both resolving
 * to 0x0204be08, and our config/arm9/symbols.txt has only one symbol there
 * (data_0204be04, data_0204be08 and data_0204be0a all exist, but nothing gives
 * two names to be08). This is a SYMBOL-MAP limitation, not a source-form problem,
 * and it cannot be closed from the C alone.
 *
 * NEXT STEP, and it needs a decision rather than an experiment: adding a second
 * symbol at 0x0204be08 to the delink config would let this compile exactly, but
 * it changes the symbol map that every other module shares, so it is not a call
 * to make inside a routine decomp batch. Ask first.
 *
 * The working C is below with the be0a spelling, since that is the form that
 * proves the analysis -- swap it back to be08 the moment a second symbol exists. */
extern unsigned short data_0204be08;
extern unsigned short data_0204be0a;

extern int func_02030788(void);
extern short func_02031384(int a, void *b, int c);
extern void func_ov023_02083aa8(void);
extern void func_020235e8(int flag, int a, int b);

void func_020234e8(void) {
    char *self = *(char **)((char *)&data_0204be08 + 4);

    if (func_02030788() != 0) {
        return;
    }
    if ((&data_0204be08)[1] != 1) {
        return;
    }
    if (data_0204be08 != 0) {
        return;
    }

    data_0204be08 = 1;
    func_02031384(0x11, (void *)&data_0204be0a, 2);
    func_ov023_02083aa8();
    func_020235e8(0x2484, 1, 1);
    *(int *)(self + 0xe8) = 1;
}
