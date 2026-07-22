/* Allocator vtable hook: frees `block` through func_02010d24 from the heap at allocator+4.
 * Twin of AllocatorFreeForExpHeap. */
extern void *func_02010d24();

void *AllocatorFreeForExpHeap_0x02010d90(void **allocator, void *block) {
    return func_02010d24(allocator[1], block);
}
