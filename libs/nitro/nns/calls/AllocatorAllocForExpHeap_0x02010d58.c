/* Allocator vtable hook twin: allocates from the heap at allocator+4 with the alignment at
 * allocator+8. */
extern void *NNS_FndAllocFromExpHeapEx_0x02010bcc();

void *AllocatorAllocForExpHeap_0x02010d58(void **allocator, unsigned int size) {
    return NNS_FndAllocFromExpHeapEx_0x02010bcc(allocator[1], size, allocator[2]);
}
