extern void *NNSi_FndAllocFromDefaultExpHeap(int size);
extern char *data_0204c208;

void func_0202c06c(int n) {
    *(void **)(data_0204c208 + 0x61c4) = NNSi_FndAllocFromDefaultExpHeap(n * 0x14);
    *(int   *)(data_0204c208 + 0x61c8) = n;
}
