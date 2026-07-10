extern void NNSi_FndFreeFromDefaultHeap(int arg0);

void func_ov022_0209f0b8(int arg0) {
    int i;
    if (*(int *)(arg0 + 0x79c) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(arg0 + 0x79c));
        *(int *)(arg0 + 0x79c) = 0;
    }
    if (*(int *)(arg0 + 0x798) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(arg0 + 0x798));
        *(int *)(arg0 + 0x798) = 0;
    }
    i = 0;
    do {
        if (*(int *)(arg0 + 0x6c0) != 0) {
            NNSi_FndFreeFromDefaultHeap(*(int *)(*(int *)(arg0 + 0x6c0) + 4));
            NNSi_FndFreeFromDefaultHeap(*(int *)(arg0 + 0x6c0));
        }
        *(int *)(arg0 + 0x6c0) = 0;
        i = i + 1;
        arg0 = arg0 + 4;
    } while (i < 0x36);
}
