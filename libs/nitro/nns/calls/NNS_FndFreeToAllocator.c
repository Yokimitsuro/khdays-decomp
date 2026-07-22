/* Calls the allocator's second vtable slot (free). */
typedef void (*FreeFn)(void *allocator, void *block);

void NNS_FndFreeToAllocator(void *allocator, void *block) {
    FreeFn *vt = *(FreeFn **)allocator;
    vt[1](allocator, block);
}
