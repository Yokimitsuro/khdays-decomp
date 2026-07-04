extern void *func_0201ef9c();
extern int func_02011a6c();
extern void NNSi_FndFreeFromDefaultHeap();

void *func_02024c1c(int this_, int arg1, int arg2) {
    void *r = func_0201ef9c(arg1, arg2);
    if (r == 0) goto ret0;
    if (func_02011a6c(r, this_) != 0) return r;
    NNSi_FndFreeFromDefaultHeap(r);
ret0:
    return 0;
}
