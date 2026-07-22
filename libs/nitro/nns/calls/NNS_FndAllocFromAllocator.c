/* Calls the allocator's first vtable slot (alloc). */
typedef void *(*AllocFn)(void *allocator, unsigned int size);

void *NNS_FndAllocFromAllocator(void *allocator, unsigned int size) {
    AllocFn *vt = *(AllocFn **)allocator;
    return vt[0](allocator, size);
}
