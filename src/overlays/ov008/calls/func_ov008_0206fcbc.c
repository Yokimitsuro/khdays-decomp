extern void NNSi_FndFreeFromDefaultHeap(void *block);

void func_ov008_0206fcbc(void *object)
{
    void *block = *(void **)((char *)object + 0x58);

    if (block != 0) {
        NNSi_FndFreeFromDefaultHeap(block);
        *(int *)((char *)object + 0x58) = 0;
    }
}
