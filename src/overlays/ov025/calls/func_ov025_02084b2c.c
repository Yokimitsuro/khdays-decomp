extern int NNSi_FndAllocFromDefaultExpHeap();
extern void MI_CpuFill8();
extern void NNS_FndAppendListObject();
extern int data_ov025_020b5744;

unsigned int * func_ov025_02084b2c(unsigned int arg0) {
    unsigned int *p;
    if (arg0 == 0) return (unsigned int *)arg0;
    p = (unsigned int *)NNSi_FndAllocFromDefaultExpHeap(0x10);
    MI_CpuFill8(p, 0, 0x10);
    *p = arg0;
    NNS_FndAppendListObject((int *)(*(int *)((char *)&data_ov025_020b5744 + 4) + 0x9660), (int)p);
    return p;
}
