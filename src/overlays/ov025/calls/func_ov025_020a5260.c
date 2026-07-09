extern void NNSi_FndFreeFromDefaultHeap();

void func_ov025_020a5260(int arg0) {
    int p = *(int *)(arg0 + 0x58);
    if (p == 0) {
        return;
    }
    NNSi_FndFreeFromDefaultHeap(p);
    *(int *)(arg0 + 0x58) = 0;
}
