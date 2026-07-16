/* NONMATCHING: instruction-scheduling tie — the ROM emits `mov r3,#0xf5` before the guard cmp and
 * the `lsl#4` column shift after it; mwcc swaps those two independent movs around the cmp.
 * Declaration order does not steer it. */
/* func_ov008_02075f00 -- draw mission row param_2's label and grow the panel height.
 * Text lives at obj+0x18e+row*0x48; colour 0xf5 normally, 0xf9 when the row is disabled
 * (obj+row*0x48+0x188 == 0). Adds the rendered height (func_ov008_02074b10) to obj+0x14c. */
extern void func_02030278(int dst, int a, unsigned int col, int colour, unsigned short *text, int d);
extern int  func_ov008_02074b10(unsigned short *text);

void func_ov008_02075f00(int param_1, int param_2) {
    unsigned short *text = (unsigned short *)(param_1 + 0x18e + param_2 * 0x48);
    int colour = 0xf5;
    unsigned int col = param_2 * 0x10 + 3;
    if (*(int *)(param_1 + param_2 * 0x48 + 0x188) == 0) {
        colour = 0xf9;
    }
    func_02030278(param_1 + 0xc, 3, col, colour, text, 1);
    *(int *)(param_1 + 0x14c) = *(int *)(param_1 + 0x14c) + func_ov008_02074b10(text);
}
