/* NNSi_FndGetCurrentRootHeap: returns the current thread's root heap handle. */

extern int data_0204c058;

int NNSi_FndGetCurrentRootHeap(void) {
    return *(int *)(*(int *)((int)&data_0204c058 + 4) + 0x20);
}
