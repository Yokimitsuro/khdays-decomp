extern void NNSi_FndFreeFromDefaultHeap();

void func_ov002_02066790(int arg0) {
    int p = *(int *)(arg0 + 8);
    if (p != 0) {
        NNSi_FndFreeFromDefaultHeap(p);
    }
}
