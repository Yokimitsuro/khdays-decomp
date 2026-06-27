extern void NNSi_FndFreeFromDefaultHeap(void *);
extern int data_0204caac;

void func_0203d194(void *p) {
    if (p == 0) return;
    data_0204caac -= 1;
    NNSi_FndFreeFromDefaultHeap(p);
}
