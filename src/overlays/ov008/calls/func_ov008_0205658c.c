extern void func_ov008_02055c74(void *object);
extern void func_ov008_02056418(void *object);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void func_ov008_0205658c(void *object)
{
    func_ov008_02055c74(object);
    func_ov008_02056418(object);

    if (*(void **)((char *)object + 0x14) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)((char *)object + 0x14));
        *(int *)((char *)object + 0x14) = 0;
    }
}
