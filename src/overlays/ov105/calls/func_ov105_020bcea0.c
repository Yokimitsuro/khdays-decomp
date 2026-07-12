/* Store param_2 at +0x18 of element param_1 of the second ov105 global array. */
extern int data_ov105_020bfa20;
void func_ov105_020bcea0(int param_1, int param_2) {
    *(int *)((&data_ov105_020bfa20)[1] + param_1 * 4 + 0x18) = param_2;
}
