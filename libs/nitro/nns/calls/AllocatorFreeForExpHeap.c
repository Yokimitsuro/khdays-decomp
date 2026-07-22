/* Allocator vtable hook: frees `block` from the expanded heap stored at allocator+4. */
extern void *func_0201098c();

void *AllocatorFreeForExpHeap(void **allocator, void *block) {
    return func_0201098c(allocator[1], block);
}
