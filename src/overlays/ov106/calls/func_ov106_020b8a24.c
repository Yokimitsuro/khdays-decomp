/* Store param_1 into the global array (base at data_ov106_020b8b68) at slot
 * param_2, field +0x60. */
extern int data_ov106_020b8b68;
void func_ov106_020b8a24(int param_1, int param_2) {
    *(int *)(*(int *)&data_ov106_020b8b68 + param_2 * 4 + 0x60) = param_1;
}
