extern void NNSi_FndFreeFromDefaultHeap(void *);
void func_ov008_02055c74(void **slot)
{
    if (*slot != 0) {
        NNSi_FndFreeFromDefaultHeap(*slot);
    }
}
