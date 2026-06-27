extern void *NNS_FndAllocFromExpHeapEx(void *heap, unsigned int size, int align);

extern void **data_0204c028;

void *func_02023684(unsigned int size, int align)
{
    return NNS_FndAllocFromExpHeapEx(*data_0204c028, size, align);
}
