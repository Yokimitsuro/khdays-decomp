/* func_02012ca8 -- program a BGxCNT register (variant 1 of two).
 *
 * Byte-identical to func_02012c2c except for the VRAM display-mode table it hands to the
 * bank setup: data_020419f4 here, data_02041a14 there.  See that file for what the five
 * arguments mean and for the codegen notes (single-expression pack, param_2-first OR,
 * `param_1 <= 3`).
 */
extern void func_020128c0(int p);
extern void func_02012904(int p);
extern int data_020419f4;
extern unsigned short *data_02041ac0[];

void func_02012ca8(int param_1, int param_2, int param_3, int param_4, int param_5) {
    unsigned short *reg;
    int packed;

    if (param_1 <= 3) {
        func_020128c0((int)&data_020419f4 + (param_1 - 2) * 8);
    } else {
        func_02012904((int)&data_020419f4 + (param_1 - 6) * 8);
    }
    reg = data_02041ac0[param_1];
    packed = (param_2 << 0xe) | (param_4 << 8) | (param_5 << 2) | (param_3 << 0xd);
    *reg = (*reg & 0x43) | (unsigned short)packed;
}
