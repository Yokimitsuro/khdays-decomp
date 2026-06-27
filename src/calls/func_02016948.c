extern unsigned func_02014a5c(int a, int b);
extern void *NNS_FndAllocFromAllocator(void *alloc, unsigned size);

void *func_02016948(void *alloc, int a, int b) {
    return NNS_FndAllocFromAllocator(alloc, func_02014a5c(a, b));
}
