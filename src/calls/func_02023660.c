extern void *NNS_FndAllocFromExpHeapEx(int heap, unsigned size, int align);
extern int *data_0204c028;

void *func_02023660(unsigned size) {
    return NNS_FndAllocFromExpHeapEx(*data_0204c028, size, 4);
}
