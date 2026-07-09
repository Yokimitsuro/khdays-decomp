extern void NNSi_FndFreeFromDefaultHeap();
extern int data_0204c4f0;

void func_02035c44(void) {
    if (*(int *)((char *)&data_0204c4f0 + 8) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)((char *)&data_0204c4f0 + 8));
        *(int *)((char *)&data_0204c4f0 + 8) = 0;
    }
}
