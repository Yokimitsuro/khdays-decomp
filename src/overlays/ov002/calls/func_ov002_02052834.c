extern void NNSi_FndFreeFromDefaultHeap();

void func_ov002_02052834(int arg0) {
    int p = *(int *)arg0;
    if (p != 0) {
        NNSi_FndFreeFromDefaultHeap(p);
    }
}
