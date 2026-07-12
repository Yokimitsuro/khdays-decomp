/* Copy param_2 bytes from param_1 into the global buffer at data_0204be08. */
extern void MI_CpuCopy8(const void *src, void *dest, unsigned int size);
extern int data_0204be08;
void func_02023470(int param_1, int param_2) {
    MI_CpuCopy8((const void *)param_1, &data_0204be08, param_2);
}
