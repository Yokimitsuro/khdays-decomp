extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void MI_CpuFill8(void *dst, unsigned char val, unsigned int size);

extern void *data_0204c208;

int func_0202b73c(void) {
    int i;

    if (data_0204c208 == 0) {
        data_0204c208 = NNSi_FndAllocFromDefaultExpHeap(0xa4d4);
    }
    MI_CpuFill8(data_0204c208, 0, 0xa4d4);

    for (i = 0; i < 0x40; i++) {
        *(unsigned int *)((unsigned char *)data_0204c208 + i * 0x184 + 0x244) = 0x1000;
    }
    return 1;
}
