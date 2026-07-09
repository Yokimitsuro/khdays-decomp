extern void NNS_FndRemoveListObject(void *list, void *object);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void func_ov008_0206e0c0(void *context, void *object)
{
    NNS_FndRemoveListObject((char *)context + 0x1cc, object);
    NNSi_FndFreeFromDefaultHeap(*(void **)((char *)object + 0x14));
    NNSi_FndFreeFromDefaultHeap(object);
}
