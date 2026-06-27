extern void INITi_CpuClear32_0x01ff86fc(unsigned int data, void *dst, unsigned int size);
extern int func_02031ac4(void);
extern void func_02031af4(void *dst, int a, int b, int c);
extern void *func_02031c30(void *a, int b);
extern void NNS_FndAppendDoubleListObject(void *a, void *b);

int func_02032288(void *a0, int a1, int a2) {
    int idx;
    char *p;
    char *q;

    idx = func_02031ac4();
    p = (char *)a0 + 4 + idx * 0x8c;

    *(unsigned int *)(p + 0x78) &= ~1u;
    *(unsigned int *)(p + 0x78) |= 7u;
    *(unsigned int *)(p + 0x78) &= ~8u;
    *(unsigned int *)(p + 0x78) &= ~0x10u;
    *(unsigned int *)(p + 0x78) &= ~0x20u;
    *(unsigned int *)(p + 0x7c) = 0x1000;
    *(unsigned int *)(p + 0x80) = 0;
    *(unsigned int *)(p + 0x84) = 0x1000;
    *(unsigned int *)(p + 0x88) = 0x1000;
    *(unsigned int *)(p + 0x70) = 0;
    *(int *)(p + 0x74) = a2;

    INITi_CpuClear32_0x01ff86fc(0, p + 0xc, 8);

    q = (char *)func_02031c30(a0, a2);

    func_02031af4(p + 0x14, *(int *)(q + 0x10), *(int *)(q + 0xc), a1);

    *(int *)(p + 0x6c) = *(short *)(q + 0x60);
    NNS_FndAppendDoubleListObject(a0, p);

    return idx;
}
