/*
 * NONMATCHING -- 124/124 bytes, instruction-for-instruction identical; diff @0x51 is a pure
 * register-choice residue in the bitfield-pack tail. The ROM keeps the packed accumulator in r0
 * throughout and loads *reg into r2; mwcc rotates the accumulator through r0->r2->r1 and loads *reg
 * into r0. SOLVED here (keep the source form): the OR chain must be written param_2-FIRST so mwcc's
 * commutative-OR canonicalisation emits the ROM's param_4<<8-first order; and `param_1 <= 3` (not
 * `< 4`) gives the ROM's `cmp #3; bgt`. The `keep = *reg & 0x43` temp did not move the residue.
 * Everything else (bank setup branch, stride-8 index, the 5th stack arg, the mask/shift pack) is
 * byte-exact. x2 twin in main. Attack only the accumulator register choice.
 *
 * func_02012c2c (main; x2). Program one of the sound-capture/mixer registers.
 * For channel param_1, run the per-bank setup (020128c0 for banks <4, 02012904 for >=4, indexed
 * into data_02041a14 by 8-byte stride), then pack the four field args into the 16-bit register
 * data_02041ac0[param_1], preserving its bits 0/1/6 (mask 0x43):
 *   param_4<<8 | param_2<<0xe | param_5<<2 | param_3<<0xd.
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
    packed = param_2 << 0xe;
    packed |= param_4 << 8;
    packed |= param_5 << 2;
    packed |= param_3 << 0xd;
    *reg = (*reg & 0x43) | (unsigned short)packed;
}
