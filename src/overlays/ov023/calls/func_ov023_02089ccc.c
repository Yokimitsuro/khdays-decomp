/* Store param_1 into the global array (base at data_ov023_0208a7c0) at slot
 * param_2, field +0x60. */
extern int data_ov023_0208a7c0;
void func_ov023_02089ccc(int param_1, int param_2) {
    *(int *)(*(int *)&data_ov023_0208a7c0 + param_2 * 4 + 0x60) = param_1;
}
