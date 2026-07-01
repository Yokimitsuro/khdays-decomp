extern void *NNS_FndAllocFromExpHeapEx(void *heap, unsigned int size, int align);

extern void **data_0204c028;

void *NNS_FndAllocFromDefaultExpHeapEx(unsigned int size, int align)
{
    return NNS_FndAllocFromExpHeapEx(*data_0204c028, size, align);
}
