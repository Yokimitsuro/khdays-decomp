/* If the global source pointer at data_0205ac38 is set, copy 8 bytes of it into the destination
 * and return the destination; otherwise return null. */
extern void MI_CpuCopy8(void *src, void *dst, int size);
extern int data_ov006_020565e0;
int func_ov006_0204d5c4(int param_1) {
    int src = data_ov006_020565e0;
    if (src == 0) return 0;
    MI_CpuCopy8((void *)src, (void *)param_1, 8);
    return param_1;
}
