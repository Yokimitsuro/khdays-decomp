extern int NNSi_FndGetAllocatorForDefaultHeap();
extern int NNS_FndFreeToAllocator();

void func_0202e1b0(void *ptr) {
    NNS_FndFreeToAllocator(NNSi_FndGetAllocatorForDefaultHeap(0), ptr);
}
