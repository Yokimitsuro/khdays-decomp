extern void NNSi_FndFreeFromDefaultHeap(void *);

void func_ov007_0204d364(void **p)
{
    if (*p) {
        NNSi_FndFreeFromDefaultHeap(*p);
    }
}
