extern void *NNSi_AllocFromTailOfExpHeap(void *hh, unsigned size, unsigned align);
extern void *NNSi_AllocFromHeadOfExpHeap(void *hh, unsigned size, unsigned align);

void *NNS_FndAllocFromExpHeapEx_0x02010bcc(void *heap, unsigned size, int align) {
    if (size == 0) size = 1;
    size = (size + 3) & ~3;
    heap = (char *)heap + 0x24;
    if (align >= 0) {
        return NNSi_AllocFromHeadOfExpHeap(heap, size, (unsigned)align);
    } else {
        return NNSi_AllocFromTailOfExpHeap(heap, size, (unsigned)-align);
    }
}
