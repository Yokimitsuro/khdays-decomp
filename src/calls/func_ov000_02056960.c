extern void NNSi_FndFreeFromDefaultHeap();

void func_ov000_02056960(void **p)
{
    void *v = p[0];
    if (v) {
        NNSi_FndFreeFromDefaultHeap(v);
    }
}
