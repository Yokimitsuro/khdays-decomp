/* func_02012c2c -- program a BGxCNT register (variant 0 of two; see func_02012ca8).
 *
 * data_02041ac0 is the table of the eight BG control registers
 * { 0x04000008, 0x0400000A, 0x0400000C, 0x0400000E, 0x04001008, ... 0x0400100E },
 * so param_1 is the BG index: 0-3 on the main engine, 4-7 on the sub engine.
 *
 * First rebind the BG's VRAM bank -- func_020128c0 (main) / func_02012904 (sub) look the
 * current display mode up in the 8-byte row at data_02041a14 + (bg - 2) * 8 -- then fold the
 * four field arguments into BGxCNT while preserving bits 0, 1 and 6 (priority and mosaic):
 *   param_4 -> screen base block (bits 8-12)
 *   param_5 -> character base block (bits 2-5)
 *   param_3 -> area overflow (bit 13)
 *   param_2 -> screen size (bits 14-15)
 *
 * CODEGEN NOTE -- the pack has to be ONE expression.  Written as a chain of `packed |= x;`
 * statements mwcc gives every partial result its own register and rotates the accumulator
 * r0 -> r2 -> r1 -> r2, which also pushes the `ldrh` of the old register value into r0.
 * As a single OR expression the accumulator stays in r0 for all three `orr`s and the
 * `ldrh` lands in r2, exactly like the ROM.  Two more shapes are load-bearing: the OR is
 * written param_2-first, so mwcc's commutative canonicalisation emits the ROM's
 * `param_4 << 8` first, and the bank test is `param_1 <= 3` (not `< 4`) for `cmp #3; bgt`.
 */
extern void func_020128c0(int p);
extern void func_02012904(int p);
extern int data_02041a14;
extern unsigned short *data_02041ac0[];

void func_02012c2c(int param_1, int param_2, int param_3, int param_4, int param_5) {
    unsigned short *reg;
    int packed;

    if (param_1 <= 3) {
        func_020128c0((int)&data_02041a14 + (param_1 - 2) * 8);
    } else {
        func_02012904((int)&data_02041a14 + (param_1 - 6) * 8);
    }
    reg = data_02041ac0[param_1];
    packed = (param_2 << 0xe) | (param_4 << 8) | (param_5 << 2) | (param_3 << 0xd);
    *reg = (*reg & 0x43) | (unsigned short)packed;
}
