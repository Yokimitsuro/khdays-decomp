extern int data_ov022_020b2ea4;
extern void MI_CpuFill8(void *dest, int value, int size);

void func_ov022_0208a1a4(void) {
    int obj = *(int *)&data_ov022_020b2ea4;
    int i;
    unsigned short *p;
    if (obj == 0) return;
    MI_CpuFill8((void *)(obj + 0x58), 0, 0x40);
    p = (unsigned short *)(obj + 100);
    i = 0;
    do {
        i = i + 1;
        *p = *p & 0xffff0007 | 0x8000;
        p = p + 8;
    } while (i < 4);
}
