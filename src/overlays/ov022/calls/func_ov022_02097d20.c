/* Draw down the remaining byte budget at +0x4b4 by whatever the decoder consumed,
 * clamped at zero. Nothing to do once the budget is spent. */
extern int func_ov022_02083f90(int budget);

void func_ov022_02097d20(char *self) {
    int left = *(int *)(self + 0x4b4);

    if (left == 0) {
        return;
    }

    left = *(int *)(self + 0x4b4) - func_ov022_02083f90(left);
    *(int *)(self + 0x4b4) = left;

    if (left < 0) {
        *(int *)(self + 0x4b4) = 0;
    }
}
