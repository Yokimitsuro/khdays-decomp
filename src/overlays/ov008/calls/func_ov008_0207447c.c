extern void NNSi_FndFreeFromDefaultHeap(void *block);

void func_ov008_0207447c(void *object)
{
    void *block = *(void **)((char *)object + 0x174);

    if (block != 0) {
        NNSi_FndFreeFromDefaultHeap(block);
        *(int *)((char *)object + 0x174) = 0;
    }
}
