extern int data_ov023_0208a784;
/* Store value at +0xf0 of the index-th slot of the ov023 table. */
void func_ov023_02083bc0(int param_1, int param_2) {
    *(int *)((&data_ov023_0208a784)[1] + param_2 * 4 + 0xf0) = param_1;
}
