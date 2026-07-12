/* Copy 8 bytes from param_3 into param_2+0x2c. */
extern void MI_CpuCopy8(void *src, void *dst, int size);

void func_ov008_020548a4(int param_1, int param_2, int param_3) {
    MI_CpuCopy8((void *)param_3, (void *)(param_2 + 0x2c), 8);
}
