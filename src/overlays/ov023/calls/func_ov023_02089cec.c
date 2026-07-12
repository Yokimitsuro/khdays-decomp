/* Read the global array (base at data_ov023_0208a7c0) at slot param_1, field +0x68. */
extern int data_ov023_0208a7c0;
int func_ov023_02089cec(int param_1) {
    return *(int *)(*(int *)&data_ov023_0208a7c0 + param_1 * 4 + 0x68);
}
