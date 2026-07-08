extern void *NNS_FndGetNextListObject(void *list, void *object);
extern void NNS_FndRemoveListObject(void *list, void *object);
extern void func_ov302_020cc0ac(void *object);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void func_ov302_020cc538(int this_) {
    void *object = NNS_FndGetNextListObject((void *)(this_ + 0x18), 0);
    void *next;

    if (object == 0) return;

    do {
        next = NNS_FndGetNextListObject((void *)(this_ + 0x18), object);
        func_ov302_020cc0ac(object);
        NNS_FndRemoveListObject((void *)(this_ + 0x18), object);
        if (object != 0) {
            NNSi_FndFreeFromDefaultHeap(object);
        }
        object = next;
    } while (next != 0);
}
