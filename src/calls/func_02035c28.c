extern void *NNSi_FndAllocFromDefaultExpHeap(int size);
extern void *data_0204c4f0[];

void func_02035c28(void) {
    if (data_0204c4f0[2] != 0) return;
    data_0204c4f0[2] = NNSi_FndAllocFromDefaultExpHeap(0x7e);
}
