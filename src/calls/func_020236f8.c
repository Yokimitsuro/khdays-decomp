extern void *NNS_FndAllocFromExpHeapEx(int heap, unsigned size, int align);
extern int **data_0204c028;

void *func_020236f8(unsigned size, int align, int **heapPP) {
    if (heapPP == 0) heapPP = data_0204c028;
    return NNS_FndAllocFromExpHeapEx(*(int *)heapPP, size, align);
}
