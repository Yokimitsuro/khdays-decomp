/* Allocator vtable hook: allocates from the expanded heap at allocator+4 with the
 * alignment stored at allocator+8. */
extern void *NNS_FndAllocFromExpHeapEx();

void *AllocatorAllocForExpHeap(void **allocator, unsigned int size) {
    return NNS_FndAllocFromExpHeapEx(allocator[1], size, allocator[2]);
}
