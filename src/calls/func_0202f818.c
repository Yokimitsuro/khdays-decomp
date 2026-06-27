extern void NNSi_FndFreeFromDefaultHeap(void *);
extern int func_020109c8(void *, int);
extern void **data_0204c02c;

int func_0202f818(void *p) {
    NNSi_FndFreeFromDefaultHeap(*(void **)((char *)p + 8));
    return func_020109c8(*data_0204c02c, 4);
}
