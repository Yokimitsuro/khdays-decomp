extern void *data_0204c028;

void *NNSi_FndGetAllocatorForDefaultHeap(void *p) {
    if (p == 0) p = data_0204c028;
    return (char *)p + 4;
}
