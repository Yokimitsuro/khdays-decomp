/* func_ov025_020ab558 -- draw one mission-list row's caption and advance the running width.
 * The row is param_2 (stride 0x48); its text starts at +0x18e and its "available" word at +0x188.
 * Rows that are unavailable use colour 0xf9 instead of 0xf5. The caption is drawn at column
 * param_2 * 0x10 + 3, and its measured width (func_ov025_020aa168) is added to the total at +0x14c.
 *
 * The availability test is written BEFORE the column arithmetic: the ROM issues the `cmp` ahead of
 * the `lsl`, and with the column computed first mwcc swaps the pair. The predicated `moveq` still
 * lands after the column add either way -- that part is the scheduler and does not need steering.
 * Byte-identical twin of func_ov008_02075f00. */
extern void func_02030278(int dst, int a, unsigned int col, int colour, unsigned short *text, int d);
extern int  func_ov025_020aa168(unsigned short *text);

void func_ov025_020ab558(int param_1, int param_2) {
    unsigned short *text = (unsigned short *)(param_1 + 0x18e + param_2 * 0x48);
    int colour = 0xf5;
    unsigned int col;

    if (*(int *)(param_1 + param_2 * 0x48 + 0x188) == 0) {
        colour = 0xf9;
    }
    col = param_2 * 0x10 + 3;

    func_02030278(param_1 + 0xc, 3, col, colour, text, 1);
    *(int *)(param_1 + 0x14c) = *(int *)(param_1 + 0x14c) + func_ov025_020aa168(text);
}
