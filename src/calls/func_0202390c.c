extern void MI_CpuFill8(void *dst, int value, int size);
extern char data_0204c068[];
extern char data_0204c058[];
/* Clear the 0x100-byte scratch table and reset the three cursor words of its header. */
void func_0202390c(void) {
    MI_CpuFill8(data_0204c068, 0, 0x100);
    *(int *)(data_0204c058 + 0xc) = 0;
    *(int *)(data_0204c058 + 4) = 0;
    *(int *)(data_0204c058 + 8) = 0;
}
