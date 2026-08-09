/* NNS_FndInitAllocatorForExpHeap: binds the exp-heap allocator vtable and its two params. */

extern int data_02041924;

void NNS_FndInitAllocatorForExpHeap(int *allocator, int a, int b) {
    allocator[0] = (int)&data_02041924;
    allocator[1] = a;
    allocator[2] = b;
    allocator[3] = 0;
}
