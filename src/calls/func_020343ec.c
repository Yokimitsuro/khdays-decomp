extern void *func_020236cc(unsigned int size, int heap);
extern void MI_CpuFill8(void *dst, unsigned char val, unsigned int size);

extern int data_0204c024;
extern unsigned char *data_0204c238;

void func_020343ec(void) {
    int i;

    data_0204c238 = func_020236cc(0x294, data_0204c024);
    MI_CpuFill8(data_0204c238, 0, 0x294);

    for (i = 0; i < 0x21; i++) {
        *(int *)(data_0204c238 + i * 0x14 + 0x10) = 0x10;
    }
}
