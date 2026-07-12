/*
 * Program a pair of window-coordinate registers at 0x04001042: pack (param_1 high
 * byte, param_3 low byte) into the halfword at +0 and (param_2, param_4) into the
 * halfword at +4.
 */
void func_ov002_02055934(unsigned int param_1, unsigned int param_2,
                         unsigned int param_3, unsigned int param_4) {
    volatile unsigned short *reg = (volatile unsigned short *)0x04001042;

    reg[0] = ((param_1 << 8) & 0xff00) | (param_3 & 0xff);
    reg[2] = ((param_2 << 8) & 0xff00) | (param_4 & 0xff);
}
