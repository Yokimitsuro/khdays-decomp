extern void NNSi_FndFreeFromDefaultHeap();

void func_ov025_020a9a7c(int arg0) {
    int p = *(int *)(arg0 + 0x174);
    if (p == 0) {
        return;
    }
    NNSi_FndFreeFromDefaultHeap(p);
    *(int *)(arg0 + 0x174) = 0;
}
