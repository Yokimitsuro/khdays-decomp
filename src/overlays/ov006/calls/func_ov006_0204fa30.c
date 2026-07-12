/* Copy 0x58 bytes from (global + 0x436) into the caller's buffer. */
extern void MI_CpuCopy8(const void *src, void *dest, unsigned int size);
extern int data_ov006_020565e4;

void func_ov006_0204fa30(void *param_1) {
    int g = *(int *)&data_ov006_020565e4;
    MI_CpuCopy8((const void *)(g + 0x436), param_1, 0x58);
}
