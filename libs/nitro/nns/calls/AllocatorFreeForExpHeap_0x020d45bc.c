/* Allocator vtable hook: frees `block` through func_ov292_020d3e58 from the heap at allocator+4.
 * Twin of AllocatorFreeForExpHeap. */
extern void *func_ov292_020d3e58();

void *AllocatorFreeForExpHeap_0x020d45bc(void **allocator, void *block) {
    return func_ov292_020d3e58(allocator[1], block);
}
