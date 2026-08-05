/*
 * func_ov002_02076bd8 - set bit 0 of a game-state field to a boolean (ARM).
 *
 * Reads the game-state field addressed by (param_1[0x14], param_1[0x16]) via func_020235d0, clears
 * its low bit, sets that bit to (param_2 != 0), and writes it back via func_020235e8. The field id
 * pair is re-read for the store because the get call may touch the same state. The value is kept as
 * a u16 (mask 0xfffe), which is why each step re-truncates to 16 bits.
 */
extern int func_020235d0(int a, int b);
extern void func_020235e8(int a, int b, int c);

void func_ov002_02076bd8(int param_1, int param_2)
{
    unsigned short v = func_020235d0(*(unsigned short *)(param_1 + 0x14),
                                     *(unsigned char *)(param_1 + 0x16)) & 0xfffe;
    if (param_2 != 0) v |= 1;
    func_020235e8(*(unsigned short *)(param_1 + 0x14),
                  *(unsigned char *)(param_1 + 0x16), v);
}
