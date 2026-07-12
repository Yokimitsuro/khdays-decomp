/* Copy 0x58 bytes from (global + 0x436) into the caller's buffer. */
extern void MI_CpuCopy8(const void *src, void *dest, unsigned int size);
extern int data_ov008_02090f24;

void func_ov008_0207b78c(void *param_1) {
    int g = *(int *)&data_ov008_02090f24;
    MI_CpuCopy8((const void *)(g + 0x436), param_1, 0x58);
}
