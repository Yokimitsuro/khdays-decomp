extern void NNSi_FndFreeFromDefaultHeap();

void func_ov025_02089884(int arg0) {
    int p = *(int *)arg0;
    if (p != 0) {
        NNSi_FndFreeFromDefaultHeap(p);
    }
}
