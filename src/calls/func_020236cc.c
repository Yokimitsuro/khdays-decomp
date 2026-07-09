extern int NNS_FndAllocFromExpHeapEx();
extern int data_0204c028;

int func_020236cc(int size, int *heap) {
    if (heap == 0) heap = *(int **)&data_0204c028;
    return NNS_FndAllocFromExpHeapEx(*heap, size, 4);
}
